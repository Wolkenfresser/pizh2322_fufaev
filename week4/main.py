# Программирование на языке высокого уровня (Python).
# Задание №4. Вариант 12
#
# Выполнил: Фуфаев Н. А.
# Группа: ПИЖ-б-о-23-2
# E-mail: fufaevnikita2015@gmail.com
from fraction import Fraction

if __name__ == "__main__":
    f1 = Fraction(1, 2)
    f2 = Fraction(3, 4)

    print(f"f1: {f1}")
    print(f"f2: {f2}")
    print(f"Сумма: {f1 + f2}")
    print(f"Разность: {f1 - f2}")
    print(f"Произведение: {f1 * f2}")
    print(f"Частное: {f1 / f2}")

    f1.save("fraction.json")
    f3 = Fraction.load("fraction.json")
    print(f"Загруженная дробь: {f3}")