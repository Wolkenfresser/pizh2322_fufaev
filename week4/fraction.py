# Программирование на языке высокого уровня (Python).
# Задание №4. Вариант 12
#
# Выполнил: Фуфаев Н. А.
# Группа: ПИЖ-б-о-23-2
# E-mail: fufaevnikita2015@gmail.com

import json
from math import gcd
from typing import Dict, Tuple, Any

class Fraction:
    """Класс для работы с обыкновенными дробями."""

    def __init__(self, numerator: int, denominator: int = 1) -> None:
        """
        Инициализация дроби.

        :param numerator: числитель дроби
        :param denominator: знаменатель дроби
        """
        if denominator == 0:
            raise ValueError("Знаменатель не может быть равен нулю.")
        common_divisor: int = gcd(numerator, denominator)
        self.numerator: int = numerator // common_divisor
        self.denominator: int = denominator // common_divisor
        if self.denominator < 0:
            self.numerator *= -1
            self.denominator *= -1

    def __str__(self) -> str:
        """
        Строковое представление дроби.

        :return: строковое представление дроби
        """
        return f"{self.numerator}/{self.denominator}"

    def __add__(self, other: 'Fraction') -> 'Fraction':
        """
        Сложение двух дробей.

        :param other: другая дробь
        :return: результат сложения
        """
        new_numerator: int = self.numerator * other.denominator + other.numerator * self.denominator
        new_denominator: int = self.denominator * other.denominator
        return Fraction(new_numerator, new_denominator)

    def __sub__(self, other: 'Fraction') -> 'Fraction':
        """
        Вычитание двух дробей.

        :param other: другая дробь
        :return: результат вычитания
        """
        new_numerator: int = self.numerator * other.denominator - other.numerator * self.denominator
        new_denominator: int = self.denominator * other.denominator
        return Fraction(new_numerator, new_denominator)

    def __mul__(self, other: 'Fraction') -> 'Fraction':
        """
        Умножение двух дробей.

        :param other: другая дробь
        :return: результат умножения
        """
        new_numerator: int = self.numerator * other.numerator
        new_denominator: int = self.denominator * other.denominator
        return Fraction(new_numerator, new_denominator)

    def __truediv__(self, other: 'Fraction') -> 'Fraction':
        """
        Деление двух дробей.

        :param other: другая дробь
        :return: результат деления
        """
        if other.numerator == 0:
            raise ZeroDivisionError("Нельзя делить на ноль.")
        new_numerator: int = self.numerator * other.denominator
        new_denominator: int = self.denominator * other.numerator
        return Fraction(new_numerator, new_denominator)

    def __eq__(self, other: 'Fraction') -> bool:
        """
        Проверка на равенство двух дробей.

        :param other: другая дробь
        :return: True, если дроби равны, False в противном случае
        """
        return self.numerator == other.numerator and self.denominator == other.denominator

    def to_float(self) -> float:
        """
        Преобразование дроби в число с плавающей точкой.

        :return: число с плавающей точкой
        """
        return self.numerator / self.denominator

    @classmethod
    def from_string(cls, str_value: str) -> 'Fraction':
        """
        Создание дроби из строки.

        :param str_value: строка в формате 'числитель/знаменатель'
        :return: дробь
        """
        parts: list[str] = str_value.split('/')
        if len(parts) != 2:
            raise ValueError("Строка должна быть в формате 'числитель/знаменатель'.")
        numerator: int = int(parts[0])
        denominator: int = int(parts[1])
        return cls(numerator, denominator)

    def save(self, filename: str) -> None:
        """
        Сохранение дроби в JSON файл.

        :param filename: имя файла
        """
        with open(filename, 'w') as file:
            json.dump({'numerator': self.numerator, 'denominator': self.denominator}, file)

    @classmethod
    def load(cls, filename: str) -> 'Fraction':
        """
        Загрузка дроби из JSON файла.

        :param filename: имя файла
        :return: дробь
        """
        with open(filename, 'r') as file:
            data: Dict[str, int] = json.load(file)
        return cls(data['numerator'], data['denominator'])

# Пример использования
if __name__ == "__main__":
    f1: Fraction = Fraction(3, 4)
    f2: Fraction = Fraction.from_string("5/6")

    print(f"f1: {f1}")
    print(f"f2: {f2}")

    print(f"f1 + f2: {f1 + f2}")
    print(f"f1 - f2: {f1 - f2}")
    print(f"f1 * f2: {f1 * f2}")
    print(f"f1 / f2: {f1 / f2}")

    f1.save("fraction.json")
    f3: Fraction = Fraction.load("fraction.json")
    print(f"Загруженная дробь: {f3}")