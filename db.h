/**
 * @file db.h
 * @brief Заголовочный файл класса для работы с базой данных SQLite.
 */

#pragma once
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

/**
 * @class DB
 * @brief Класс для работы с базой данных SQLite.
 *
 * Реализует паттерн Singleton и предоставляет CRUD-операции.
 * Поддерживает автоматическое создание таблиц при инициализации.
 */
class DB {
public:
  /**
   * @brief Получает единственный экземпляр класса (реализация Singleton).
   * @warning Не использовать конструктор/деструктор напрямую.
   * @return Ссылка на единственный экземпляр DB.
   */
  static DB &getInstance();

  // Переменная для хранения базы данных.
  static QSqlDatabase db;

  /**
   * @brief Инициализирует базу данных, открывает соединение и создает таблицы.
   */
  static void init();

  /**
   * @brief Закрывает соединение с базой данных.
   * @note Автоматически вызывается в деструкторе.
   */
  static void close();

  /**
   * @brief Выполняет SQL-запрос на вставку данных в таблицу.
   * @param queryString Строка с SQL-запросом для вставки данных.
   * @return true, если запрос выполнен успешно, иначе QSqlError.
   */
  static bool insertData(const QString &queryString);

  /**
   * @brief Выполняет запрос и возвращает результаты в виде QMap.
   * @param request Строка с SQL-запросом для получения данных.
   * @return Результат запроса (пустой QMap при ошибке).
   */
  static QMap<QString, QVariant> getData(const QString &request);

  /**
   * @brief Выполняет запрос и возвращает QSqlQuery.
   * @param request SQL-запрос.
   * @return Объект QSqlQuery с результатами.
   * @note Требует последующего вызова close().
   */
  static QSqlQuery getQsqlData(const QString &request);

  /**
   * @brief Генерирует и выполняет INSERT запрос из структуры данных.
   * @param data Данные в формате: {"таблица": {"колонка":"значение"}}.
   * @return true если запрос выполнен успешно.
   */
  static bool
  makeInsertQuery(const QMap<QString, QMap<QString, QVariant>> &data);

  /**
   * @brief Получает ID последней вставленной записи.
   * @return ID записи или -1 при ошибке.
   */
  static int getLastInsertId();

  /**
   * @brief Создает системные таблицы (users, grades, students).
   * @note Вызывается автоматически в init().
   */
  static void createTables();

  /**
   * @brief Удаляет все системные таблицы.
   * @warning Использовать только для тестирования!
   */
  static void dropTables();

protected:
  // DB();
  //~DB();

private:
  friend class DBDestroyer;

  /**
   * @brief Открывает соединение с базой данных, если оно еще не открыто.
   */
  static void open();
};

/**
 * @class DBDestroyer
 * @brief Вспомогательный класс для корректного удаления экземпляра DB.
 */
class DBDestroyer {
public:
  /**
   * @brief Конструктор с указателем на экземпляр DB.
   * @param p_instance Указатель на экземпляр DB.
   */
  DBDestroyer(DB *p_instance);

  /**
   * @brief Деструктор класса DBDestroyer. Удаляет экземпляр класса DB.
   */
  ~DBDestroyer();

private:
  DB *p_instance;
};
