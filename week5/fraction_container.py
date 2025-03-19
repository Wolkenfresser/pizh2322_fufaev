# Программирование на языке высокого уровня (Python).
# Задание №5. Вариант 12
#
# Выполнил: Фуфаев Н. А.
# Группа: ПИЖ-б-о-23-2
# E-mail: fufaevnikita2015@gmail.com
import json
from typing import List
from fraction import Fraction


class FractionCollection:
    """Класс-контейнер для хранения и работы с набором дробей."""

    def __init__(self) -> None:
        """Инициализация контейнера."""
        self._data: List[Fraction] = []

    def __str__(self) -> str:
        """Строковое представление контейнера."""
        return f"FractionCollection({', '.join(map(str, self._data))})"

    def __getitem__(self, index: int) -> Fraction:
        """Получение элемента по индексу."""
        return self._data[index]

    def add(self, fraction: Fraction) -> None:
        """Добавление дроби в контейнер."""
        self._data.append(fraction)

    def remove(self, index: int) -> None:
        """Удаление дроби по индексу."""
        if 0 <= index < len(self._data):
            del self._data[index]

    def save(self, filename: str) -> None:
        """Сохранение контейнера в JSON-файл."""
        with open(filename, 'w') as file:
            json.dump([{'numerator': f.numerator, 'denominator': f.denominator} for f in self._data], file)

    def load(self, filename: str) -> None:
        """Загрузка контейнера из JSON-файла."""
        with open(filename, 'r') as file:
            data = json.load(file)
            self._data = [Fraction(item['numerator'], item['denominator']) for item in data]


# Пример использования
if __name__ == "__main__":
    collection = FractionCollection()
    collection.add(Fraction(1, 2))
    collection.add(Fraction(3, 4))
    print(collection)

    collection.save("fractions.json")
    new_collection = FractionCollection()
    new_collection.load("fractions.json")
    print(new_collection)
