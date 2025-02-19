class GoodIfrit:
    def __init__(self, height, name, goodness):
        """Конструктор класса GoodIfrit.

        Инициализирует объект с заданной высотой, именем и добротой.
        """
        self._height = height  # Инкапсуляция: защищенный атрибут для высоты
        self._name = name  # Инкапсуляция: защищенный атрибут для имени
        self._goodness = goodness  # Инкапсуляция: защищенный атрибут для доброты

    def change_goodness(self, value):
        """Изменяет доброту ифрита.

        Значение доброты не может быть отрицательным.
        """
        self._goodness = max(0, value)  # Инкапсуляция: доступ к защищенному атрибуту

    def __add__(self, number):
        """Перегрузка оператора + для создания нового ифрита с увеличенной высотой.

        Создает новый объект GoodIfrit с высотой, увеличенной на заданное число.
        Остальные атрибуты остаются без изменений.
        """
        if not isinstance(number, (int, float)):
            raise TypeError("Можно прибавлять только числа")
        return GoodIfrit(self._height + number, self._name, self._goodness)

    def __call__(self, argument):
        """Перегрузка оператора вызова () для вычисления произведения аргумента на доброту и высоту.

        Возвращает произведение аргумента на доброту и высоту ифрита.
        """
        return argument * self._goodness // self._height

    def __str__(self):
        """Перегрузка метода str для получения строкового представления объекта.

        Возвращает строку вида "Good Ifrit <имя>, height <высота>, goodness <доброта>".
        """
        return f"Good Ifrit {self._name}, height {self._height}, goodness {self._goodness}"

    def __lt__(self, other):
        """Перегрузка оператора < для сравнения двух ифритов.

        Сначала сравниваются по доброте, затем по высоте, затем по имени.
        """
        if not isinstance(other, GoodIfrit):
            raise TypeError("Можно сравнивать только с GoodIfrit")
        if self._goodness != other._goodness:
            return self._goodness < other._goodness
        if self._height != other._height:
            return self._height < other._height
        return self._name < other._name

    def __le__(self, other):
        """Перегрузка оператора <= для сравнения двух ифритов."""
        return self < other or self == other

    def __eq__(self, other):
        """Перегрузка оператора == для сравнения двух ифритов."""
        if not isinstance(other, GoodIfrit):
            return False
        return self._goodness == other._goodness and self._height == other._height and self._name == other._name

    def __ne__(self, other):
        """Перегрузка оператора != для сравнения двух ифритов."""
        return not self == other

    def __gt__(self, other):
        """Перегрузка оператора > для сравнения двух ифритов."""
        return other < self

    def __ge__(self, other):
        """Перегрузка оператора >= для сравнения двух ифритов."""
        return other < self or self == other

# Пример использования
gi = GoodIfrit(80, "Hazrul", 3)
gi.change_goodness(4)
gil = gi + 15

print(gi)
print(gil)
print(gi(31))

gi = GoodIfrit(80, "Hazrul", 3)
gil = GoodIfrit(80, "Dalziel", 1)

print(gi < gil)
gil.change_goodness(2)
print(gi > gil)
print(gi, gil, sep='\n')