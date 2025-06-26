#include "tcpserver.h"
#include "functions.h"

MyTcpServer::~MyTcpServer() {
  this->close();
  server_status = false;
}

MyTcpServer::MyTcpServer(QObject *parent) : QTcpServer(parent) {
  connect(this, &QTcpServer::newConnection, this,
          &MyTcpServer::slotNewConnection);

  if (!this->listen(QHostAddress::Any, 33333)) {
    qDebug() << "server is not started";
  } else {
    server_status = true;
    qDebug() << "server is started";
  }
}

void MyTcpServer::slotNewConnection() {
  if (server_status == 1) {
    QTcpSocket *currTcpSocket;
    currTcpSocket = this->nextPendingConnection();
    currTcpSocket->write("Hello, World!!! I am echo server!\r\n");
    connect(currTcpSocket, &QTcpSocket::readyRead, this,
            &MyTcpServer::slotServerRead);
    connect(currTcpSocket, &QTcpSocket::disconnected, this,
            &MyTcpServer::slotClientDisconnected);
    tcpSockets.push_back(currTcpSocket);
  }
}

void MyTcpServer::slotServerRead() {
  QByteArray array;
  QTcpSocket *currTcpSocket = (QTcpSocket *)sender();
  while (currTcpSocket->bytesAvailable() > 0) {
    array.append(currTcpSocket->readAll());
  }
  if (array.right(1) == "\n") {
    currTcpSocket->write(ServerFunctions::parse(array));
  }
}

void MyTcpServer::slotClientDisconnected() {
  QTcpSocket *currTcpSocket = (QTcpSocket *)sender();
  currTcpSocket->close();
}
