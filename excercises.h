/**
 * @file excercises.h
 * @brief Заголовочный файл класса для проверки математических задач.
 */

#pragma once
#include <QString>

 /**
  * @class Excercises
  * @brief Класс для проверки решений математических задач.
  *
  * Содержит статические методы для проверки различных типов задач.
  */
class Excercises {
public:
  /**
   * @brief Проверяет решение задачи на вычисление предела.
   * @param answer Ответ пользователя в строковом формате.
   * @param exercise_data Данные задачи в формате "тип|параметры".
   * @return true если ответ верный, false если неверный.
   */
  static bool task1(QString answer, QString exercise_data);
};
