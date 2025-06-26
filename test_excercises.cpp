#include <QtTest/QtTest>
#include "excercises.h"

class TestExcercises : public QObject
{
    Q_OBJECT

private slots:
    void testConstLimit();
    void testPolyLimit();
    void testSinLimit();
    void testInfLimit();
    void testHoleLimit();
    void testInvalidInput();
};

void TestExcercises::testConstLimit()
{
    Excercises ex;

    // lim x->5 3 = 3
    QVERIFY(ex.task1("3", "const|3"));

    // lim x->10 (-2.5) = -2.5
    QVERIFY(ex.task1("-2.5", "const|-2.5"));

    // Неправильный ответ
    QVERIFY(!ex.task1("4", "const|3"));
}

void TestExcercises::testPolyLimit()
{
    Excercises ex;

    // lim x->2 (3x+1) = 7
    QVERIFY(ex.task1("7", "poly|2|3|1"));

    // lim x->-1 (-0.5x+2) = 2.5
    QVERIFY(ex.task1("2.5", "poly|-1|-0.5|2"));

    // Неправильный формат
}

void TestExcercises::testSinLimit()
{
    Excercises ex;

    // lim x->0 sin(4x)/x = 4
    QVERIFY(ex.task1("4", "sin|4"));

    // lim x->0 sin(-2x)/x = -2
    QVERIFY(ex.task1("-2", "sin|-2"));

    // Проверка округления
    QVERIFY(ex.task1("5", "sin|5.0001"));
}

void TestExcercises::testInfLimit()
{
    Excercises ex;

    // lim x->∞ (x²)/(x³) = 0 (степень числителя меньше)
    QVERIFY(ex.task1("0", "inf|2|3"));

    // lim x->∞ (3x²)/(2x²) = 1.5 (одинаковые степени)
    QVERIFY(ex.task1("1.5", "inf|2|2|1.5"));

    // lim x->∞ (x³)/(x²) = ∞ (степень числителя больше)
    QVERIFY(ex.task1("∞", "inf|3|2"));
}

void TestExcercises::testHoleLimit()
{
    Excercises ex;

    // lim x->3 (x²-9)/(x-3) = 6
    QVERIFY(ex.task1("6", "hole|3"));

    // lim x->5 (x²-25)/(x-5) = 10
    QVERIFY(ex.task1("10", "hole|5"));

    // Неправильный ответ
    QVERIFY(!ex.task1("12", "hole|6"));
}

void TestExcercises::testInvalidInput()
{
    Excercises ex;

    // Пустые входные данные
    QVERIFY(!ex.task1("", ""));

    // Неизвестный тип предела
    QVERIFY(!ex.task1("0", "unknown|1|2"));
}

QTEST_APPLESS_MAIN(TestExcercises)
#include "test_excercises.moc"
