#include "functions.h"
#include "db.h"
#include "excercises.h"
#include <QJsonArray>

QByteArray ServerFunctions::selectCommand(const QJsonDocument &json) {
  const QJsonObject obj = json.object();
  if (!obj.contains("command") || !obj["command"].isString()) {
    return "Invalid command\n";
  }
  const QString command = obj["command"].toString();
  if (command == "register") {
    return registerUser(obj);
  } else if (command == "login") {
    return loginUser(obj);
  } else if (command == "getGrades") {
    return getGrades(obj);
  } else if (command == "checkExercise") {
    return checkExercise(obj);
  } else {
    return "Invalid command\n";
  }
}

QByteArray ServerFunctions::parse(const QString &message) {
  QJsonDocument json = QJsonDocument::fromJson(message.toUtf8());
  qDebug() << message;
  qDebug() << json;
  if (json.isNull() || !json.isObject()) {
    return "Invalid JSON string\n";
  }
  return selectCommand(json);
}

QByteArray ServerFunctions::registerUser(const QJsonObject &json) {
  const QString login = json.value("login").toString();
  const QString password = json.value("password").toString();

  if (login.isEmpty() || password.isEmpty()) {
    return "Missing 'login' or 'password' field in JSON\n";
  }

  const QMap<QString, QVariant> userdata{
      {"login", login},
      {"password", password},
      {"role_id", 1},
  };
  const QMap<QString, QMap<QString, QVariant>> inUserData{
      {"user", userdata},
  };

  if (DB::makeInsertQuery(inUserData)) {
  } else {
    return "Registration failed\n";
  }

  const QMap<QString, QVariant> studentdata{
      {"user_id", DB::getLastInsertId()},
      {"firstname", json.value("firstname").toString()},
      {"surname", json.value("surname").toString()},
      {"lastname", json.value("lastname").toString()},
      {"studygroup", json.value("studygroup").toString()},
  };

  const QMap<QString, QMap<QString, QVariant>> inStudentData{
      {"student", studentdata},
  };

  if (DB::makeInsertQuery(inStudentData)) {
    return "Registration successful\n";
  } else {
    return "Registration failed\n";
  }
}

QByteArray ServerFunctions::loginUser(const QJsonObject &json) {
  const QString login = json.value("login").toString();
  const QString password = json.value("password").toString();

  if (login.isEmpty() || password.isEmpty()) {
    return "Missing 'login' or 'password' field in JSON\n";
  }

  const QString query =
      QString("SELECT * FROM user WHERE login = '%1' AND password = '%2'")
          .arg(login, password);
  const QMap<QString, QVariant> result = DB::getData(query);
  if (result.isEmpty()) {
    return "Login failed\n";
  } else {
    const QJsonDocument resultJson = QJsonDocument::fromVariant(result);
    return resultJson.toJson(QJsonDocument::Compact) + "\n";
  }
}

QByteArray ServerFunctions::getGrades(const QJsonObject &json) {
  qDebug() << json;
  const QString filter = json.value("filter").toString();
  bool filterDirection;
  if (json.contains("filter_direction")) {
    filterDirection = json.value("filter_direction").toBool();
  }

  QString query;
  if (filter == "default") {
    query = QString(
        "SELECT student.firstname, student.surname, student.lastname, "
        "student.studygroup, grade.exercise, ROUND(AVG(grade.grade) * 100, 2) "
        "AS "
        "grade FROM student, grade WHERE student.user_id = "
        "grade.student_id GROUP BY student.firstname, student.surname, "
        "student.lastname, student.studygroup, grade.exercise;");
  } else if (filter == "surname") {
    if (filterDirection) {
      query = QString(
          "SELECT student.firstname, student.surname, student.lastname, "
          "student.studygroup, grade.exercise, ROUND(AVG(grade.grade) * 100, "
          "2) AS "
          "grade FROM student, grade WHERE student.user_id = "
          "grade.student_id GROUP BY student.firstname, student.surname, "
          "student.lastname, student.studygroup, grade.exercise ORDER BY "
          "student.surname;");
    } else {
      query = QString(
          "SELECT student.firstname, student.surname, student.lastname, "
          "student.studygroup, grade.exercise, ROUND(AVG(grade.grade) * 100, "
          "2) AS "
          "grade FROM student, grade WHERE student.user_id = "
          "grade.student_id GROUP BY student.firstname, student.surname, "
          "student.lastname, student.studygroup, grade.exercise ORDER BY "
          "student.surname "
          "DESC;");
    }
  } else if (filter == "grades") {
    if (filterDirection) {
      query = QString(
          "SELECT student.firstname, student.surname, student.lastname, "
          "student.studygroup, grade.exercise, ROUND(AVG(grade.grade) * 100, "
          "2) AS "
          "grade FROM student, grade WHERE student.user_id = "
          "grade.student_id GROUP BY student.firstname, student.surname, "
          "student.lastname, student.studygroup, grade.exercise ORDER BY "
          "grade;");
    } else {
      query = QString(
          "SELECT student.firstname, student.surname, student.lastname, "
          "student.studygroup, grade.exercise, ROUND(AVG(grade.grade) * 100, "
          "2) AS "
          "grade FROM student, grade WHERE student.user_id = "
          "grade.student_id GROUP BY student.firstname, student.surname, "
          "student.lastname, student.studygroup, grade.exercise ORDER BY "
          "grade "
          "DESC;");
    }
  } else if (filter == "studygroup") {
    if (filterDirection) {
      query = QString(
          "SELECT student.firstname, student.surname, student.lastname, "
          "student.studygroup, grade.exercise, ROUND(AVG(grade.grade) * 100, "
          "2) AS "
          "grade FROM student, grade WHERE student.user_id = "
          "grade.student_id GROUP BY student.firstname, student.surname, "
          "student.lastname, student.studygroup, grade.exercise ORDER BY "
          "student.studygroup;");
    } else {
      query = QString(
          "SELECT student.firstname, student.surname, student.lastname, "
          "student.studygroup, grade.exercise, ROUND(AVG(grade.grade) * 100, "
          "2) AS "
          "grade FROM student, grade WHERE student.user_id = "
          "grade.student_id GROUP BY student.firstname, student.surname, "
          "student.lastname, student.studygroup, grade.exercise ORDER BY "
          "student.studygroup DESC;");
    }
  } else if (filter == "exercise") {
    if (filterDirection) {
      query = QString(
          "SELECT student.firstname, student.surname, student.lastname, "
          "student.studygroup, grade.exercise, ROUND(AVG(grade.grade) * 100, "
          "2) AS "
          "grade FROM student, grade WHERE student.user_id = "
          "grade.student_id GROUP BY student.firstname, student.surname, "
          "student.lastname, student.studygroup, grade.exercise ORDER BY "
          "grade.exercise;");
    } else {
      query = QString(
          "SELECT student.firstname, student.surname, student.lastname, "
          "student.studygroup, grade.exercise, ROUND(AVG(grade.grade) * 100, "
          "2) AS "
          "grade FROM student, grade WHERE student.user_id = "
          "grade.student_id GROUP BY student.firstname, student.surname, "
          "student.lastname, student.studygroup, grade.exercise ORDER BY "
          "grade.exercise "
          "DESC;");
    }
  } else {
    return "Invalid filter\n";
  }
  QSqlQuery result = DB::getQsqlData(query);
  QJsonArray jsonArray;
  while (result.next()) {
    QJsonObject jsonObject;
    jsonObject["firstname"] = result.value("firstname").toString();
    jsonObject["surname"] = result.value("surname").toString();
    jsonObject["lastname"] = result.value("lastname").toString();
    jsonObject["studygroup"] = result.value("studygroup").toString();
    jsonObject["exercise"] = result.value("exercise").toString();
    jsonObject["grade"] = result.value("grade").toString();
    jsonArray.append(jsonObject);
  }
  // qDebug() << jsonArray;
  if (jsonArray.isEmpty()) {
    return "No grades\n";
  } else {
    QJsonDocument resultJson(jsonArray);
    return resultJson.toJson(QJsonDocument::Compact) + "\n";
  }
}

QByteArray ServerFunctions::checkExercise(const QJsonObject &json) {
  if (!json.contains("student_id") || !json.contains("exercise") ||
      !json.contains("answer")) {
    return "Missing field in JSON\n";
  }
  qDebug() << json;
  const int student_id = json.value("student_id").toInt();
  const int excercise = json.value("exercise").toInt();
  const QString answer = json.value("answer").toString();
  const QString exercise_data = json.value("exercise_data").toString();
  bool result = false;
  switch (excercise) {
  case 1:
    result = Excercises::task1(answer, exercise_data);
    break;
  }

  const QMap<QString, QVariant> userdata{
      {"student_id", static_cast<int>(student_id)},
      {"exercise", excercise},
      {"grade", static_cast<int>(result)},
  };
  const QMap<QString, QMap<QString, QVariant>> inUserData{{"grade", userdata}};
  DB::makeInsertQuery(inUserData);
  if (result) {
    return "Correct answer\n";
  } else {
    return "Incorrect answer\n";
  }
}
