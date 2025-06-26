/**
 * @file tcpserver.h
 * @brief Заголовочный файл TCP-сервера для обработки математических задач.
 */

#pragma once
#include <QTcpServer>
#include <QTcpSocket>

/**
 * @class MyTcpServer.
 * @brief TCP-сервер для обработки клиентских подключений.
 *
 * Работает на порту 33333, принимает JSON-сообщения и возвращает результаты.
 * Использует ServerFunctions для обработки команд.
 */
class MyTcpServer : public QTcpServer {
public:
  /**
   * @brief Конструктор сервера.
   * @param parent Родительский QObject.
   * @throws std::runtime_error если не удалось запустить сервер.
   */
  explicit MyTcpServer(QObject *parent = nullptr);

  /**
   * @brief Деструктор класса (закрывает все соединения).
   */
  ~MyTcpServer() override;

  /**
   * @brief Возвращает текущий статус сервера.
   * @return true если сервер работает.
   */
  bool getServerStatus() const { return server_status; }

public slots:
  /**
   * @brief Слот, вызываемый при новом соединении клиента с сервером.
   * 
   * Метод устанавливает соединение и добавляет указатель на объект QTcpSocket в вектор tcpSockets.
   */
  void slotNewConnection();

  /**
   * @brief Слот для отключения клиента, вызываемый при его отключении от сервера.
   * 
   * Метод удаляет указатель на объект QTcpSocket из вектора tcpSockets.
   */
  void slotClientDisconnected();

  /**
   * @brief Читает и обрабатывает входящие данные.
   * @note Ожидает сообщения в формате JSON с переводом строки в конце.
   * @see ServerFunctions::parse().
   */
  void slotServerRead();

private:
  QTcpServer *tcpServer; /// Указатель на объект QTcpServer.
  QVector<QTcpSocket *> tcpSockets; /// Вектор указателей на объекты QTcpSocket для хранения подключенных клиентов.
  bool server_status; /// Статус сервера.
};
