#include "excercises.h"
#include <QCoreApplication>
#include <QDebug>
#include <QMap>
#include <QQueue>
#include <QStack>
#include <QString>
#include <QVector>
#include <iostream>
#include <limits>
#include <iterator>
#include <qdebug.h>
#include <qstringliteral.h>

bool Excercises::task1(QString answer, QString exercise_data) {
    // Простые пределы с базовой проверкой
    // Формат exercise_data: "тип|параметры"

    QStringList params = exercise_data.split('|');
    if (params.size() < 2) return false;

    QString taskType = params[0];
    QString correctAnswer;

    if (taskType == "const") {
        // Проверка предела константы (lim x->a C)
        correctAnswer = params[1]; // Ответ - сама константа
    }
    else if (taskType == "poly") {
        // Проверка предела полинома первой степени (lim x->a (kx + b))
        double a = params[1].toDouble();
        double k = params[2].toDouble();
        double b = params[3].toDouble();
        correctAnswer = QString::number(k * a + b);
    }
    else if (taskType == "sin") {
        // Проверка замечательного предела (lim x->0 sin(kx)/x=k)
        double k = params[1].toDouble();
        correctAnswer = QString::number(k);
    }
    else if (taskType == "inf") {
        // Проверка предела на бесконечность (lim x->∞ P(x)/Q(x))
        int p_degree = params[1].toInt();
        int q_degree = params[2].toInt();

        if (p_degree < q_degree) correctAnswer = "0";
        else if (p_degree == q_degree) correctAnswer = params[3]; // коэффициент
        else correctAnswer = "∞";
    }
    else if (taskType == "hole") {
        // lim x->a (x²-a²)/(x-a)=2a
        double a = params[1].toDouble();
        correctAnswer = QString::number(2 * a);
    }
    else {
        return false;
    }

    return answer.trimmed() == correctAnswer;
}
