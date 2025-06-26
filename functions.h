/**
 * @file functions.h
 * @brief Заголовочный файл класса для обработки команд сервера.
 */

#pragma once
#include <QJsonDocument>
#include <QJsonObject>

/**
 * @class ServerFunctions.
 * @brief Обработчик команд сервера.
 *
 * Преобразует сообщения в команды и возвращает ответы в JSON формате.
 */
class ServerFunctions {
public:
  /**
   * @brief Парсит входящее JSON-сообщение и перенаправляет на обработчик.
   * @param message Строка с JSON-сообщением.
   * @return Ответ сервера в формате QByteArray.
   * @retval "Invalid JSON string\n" при ошибке парсинга.
   * @see selectCommand().
   */
  static QByteArray parse(const QString &message);

  /**
   * @brief Выбирает и выполняет команду из JSON.
   * @param json Разобранный JSON документ.
   * @return Результат выполнения команды.
   * @retval "Invalid command\n" при неизвестной команде.
   */
  static QByteArray selectCommand(const QJsonDocument &json);

  /**
   * @brief Регистрирует нового пользователя.
   * @param json JSON с полями: login, password, firstname, surname, studygroup.
   * @return Статус регистрации.
   * @retval "Registration successful\n" при успехе.
   * @retval "Registration failed\n" при ошибке.
   */
  static QByteArray registerUser(const QJsonObject &json);

  /**
   * @brief Аутентифицирует пользователя.
   * @param json JSON с полями: login, password.
   * @return Данные пользователя или сообщение об ошибке.
   * @retval JSON с user_data при успехе.
   * @retval "Login failed\n" при ошибке.
   */
  static QByteArray loginUser(const QJsonObject &json);
  
  /**
   * @brief Возвращает оценки с возможностью сортировки.
   * @param json JSON с параметрами фильтрации.
   * @return Список оценок в JSON или сообщение об ошибке.
   */
  static QByteArray getGrades(const QJsonObject &json);

  /**
   * @brief Проверяет решение задачи.
   * @param json JSON с полями: student_id, exercise, answer, exercise_data.
   * @return Результат проверки.
   * @retval "Correct answer\n" при верном решении.
   * @retval "Incorrect answer\n" при ошибке.
   * @see Excercises.
   */
  static QByteArray checkExercise(const QJsonObject &json);
};
