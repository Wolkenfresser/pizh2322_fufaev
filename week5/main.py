# Программирование на языке высокого уровня (Python).
# Задание №5. Вариант 12
#
# Выполнил: Фуфаев Н. А.
# Группа: ПИЖ-б-о-23-2
# E-mail: fufaevnikita2015@gmail.com

from fraction import Fraction
from fraction_container import FractionCollection

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

    # Работа с контейнером дробей
    collection = FractionCollection()
    collection.add(Fraction(1, 3))
    collection.add(Fraction(2, 5))
    collection.add(Fraction(7, 8))

    print("\nИсходный контейнер:")
    print(collection)

    # Удаление дроби по индексу
    collection.remove(1)
    print("Контейнер после удаления элемента с индексом 1:")
    print(collection)

    # Сохранение в файл
    collection.save("fractions.json")
    print("Контейнер сохранён в файл.")

    # Загрузка из файла в новый контейнер
    new_collection = FractionCollection()
    new_collection.load("fractions.json")
    print("Загруженный контейнер:")
    print(new_collection)
