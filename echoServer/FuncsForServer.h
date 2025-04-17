#ifndef FUNCSFORSERVER_H
#define FUNCSFORSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QString>
#include <QByteArray>
#include <QDebug>

class FuncsForServer : public QObject
{
    Q_OBJECT
public:
    explicit FuncsForServer(QObject *parent = nullptr);
    ~FuncsForServer();
    QByteArray parsing(QString);
    QByteArray auth(QString);
    QByteArray reg(QString);
    QByteArray lookMyStat(QString);
    QByteArray lookAllStat(QString);
    QByteArray changeNickname(QString);
    QByteArray viewLeaderboard(QString);
    QByteArray logOut(QString);
};
#endif
