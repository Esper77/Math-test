#include <db.h>

DBDestroyer::DBDestroyer(DB *p_instance) { this->p_instance = p_instance; }

DBDestroyer::~DBDestroyer() { delete p_instance; }

void DB::open() {
  if (db.isOpen()) {
    return;
  }

  qDebug() << "Opening database\n";

  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("Test.db");

  if (!db.open()) {
    qDebug() << "Error opening database: " << db.lastError().text();
  }
}

DB &DB::getInstance() {
  static DB instance;
  return instance;
}

void DB::init() {
  getInstance();
  open();
  createTables();
}

void DB::close() {
  if (db.isOpen()) {
    db.close();
  }
}

bool DB::insertData(const QString &queryString) {
  open();
  QSqlQuery query(db);
  query.exec("PRAGMA foreign_keys = ON");

  if (!query.exec(queryString)) {
    qDebug() << "Error executing query:" << query.lastError().text();
    return false;
  }

  return true;
}

QMap<QString, QVariant> DB::getData(const QString &request) {
  QMap<QString, QVariant> resultMap;

  open();

  QSqlQuery query(db);
  if (!query.exec(request)) {
    qDebug() << "Error executing query:" << query.lastError().text();
    return resultMap;
  }

  while (query.next()) {
    QSqlRecord record = query.record();
    for (int i = 0; i < record.count(); i++) {
      resultMap[record.fieldName(i)] = query.value(i);
    }
  }

  db.close();

  return resultMap;
}
QSqlQuery DB::getQsqlData(const QString &request) {
  open();

  QSqlQuery query(db);
  if (!query.exec(request)) {
    qDebug() << "Error executing query:" << query.lastError().text();
  }

  return query;
}

bool DB::makeInsertQuery(const QMap<QString, QMap<QString, QVariant>> &data) {
  QString table = data.firstKey();
  QMap<QString, QVariant> columnData = data.value(table);

  QString query = QString("INSERT INTO %1 (").arg(table);

  QStringList columns;
  QList<QString> values;

  for (auto it = columnData.constBegin(); it != columnData.constEnd(); ++it) {
    if (it.key() != "command") {
      columns.append(it.key());
      values.append(it.value().toString());
    }
  }

  query += columns.join(", ");
  query += QString(") VALUES ('%1')").arg(values.join("', '"));

  if (insertData(query)) {
    qDebug() << "Query executed successfully";
    return true;
  } else {
    qDebug() << "Error executing query";
    return false;
  }
}

int DB::getLastInsertId() {
  QSqlQuery query;
  query.exec("SELECT last_insert_rowid();");
  if (query.next()) {
    return query.value(0).toInt();
  }
  return -1; // Возвращаем -1 в случае ошибки или отсутствия вставки
}

void DB::createTables() {
  QSqlQuery query(db);
  query.exec("PRAGMA foreign_keys = ON");

  insertData("CREATE TABLE IF NOT EXISTS user ("
             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
             "login TEXT UNIQUE,"
             "password TEXT,"
             "role_id INTEGER"
             ");");
  ;

  insertData("CREATE TABLE IF NOT EXISTS grade ("
             "student_id INTEGER,"
             "exercise INTEGER,"
             "grade INTEGER"
             ");");

  insertData("CREATE TABLE IF NOT EXISTS student ("
             "user_id INTEGER,"
             "firstname TEXT,"
             "surname TEXT,"
             "lastname TEXT,"
             "studygroup TEXT,"
             "FOREIGN KEY(user_id) REFERENCES user(id)"
             ");");
  // Администратор
  insertData("INSERT INTO user (login, password, role_id) VALUES "
             "('admin', 'admin', 0);");
}

void DB::dropTables() {
  insertData("DROP TABLE IF EXISTS grade;");
  insertData("DROP TABLE IF EXISTS user;");
  insertData("DROP TABLE IF EXISTS role;");
  insertData("DROP TABLE IF EXISTS student;");
}

QSqlDatabase DB::db;
