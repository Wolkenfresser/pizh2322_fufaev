# Программирование на языке высокого уровня (Python).
# Задание №3. Вариант 12
#
# Выполнил: Фуфаев Н. А.
# Группа: ПИЖ-б-о-23-2
# E-mail: fufaevnikita2015@gmail.com

class TimeDeposit:
    """Абстрактный класс - срочный вклад."""

    def __init__(self, name, interest_rate, period_limit, sum_limit):
        """Инициализировать атрибуты класса."""
        self.name = name
        self._interest_rate = interest_rate
        self._period_limit = period_limit
        self._sum_limit = sum_limit
        self._check_self()

    def __str__(self):
        """Вернуть строковое представление депозита."""
        return (f"Наименование:       {self.name}\n"
                f"Валюта:             {self.currency}\n"
                f"Процентная ставка:  {self._interest_rate}\n"
                f"Срок (мес.):        [{self._period_limit[0]}; {self._period_limit[1]})\n"
                f"Сумма:              [{self._sum_limit[0]:,.0f}; {self._sum_limit[1]:,.0f})")

    @property
    def currency(self):
        return "руб."  # Не изменяется

    def _check_self(self):
        """Проверить, что данные депозита являются допустимыми."""
        assert 0 < self._interest_rate <= 100, "Неверно указан процент по вкладу!"
        assert 1 <= self._period_limit[0] < self._period_limit[1], "Неверно указаны ограничения по сроку вклада!"
        assert 0 < self._sum_limit[0] <= self._sum_limit[1], "Неверно указаны ограничения по сумме вклада!"

    def _check_user_params(self, initial_sum, period):
        """Проверить, что данные депозита соответствуют его ограничениям."""
        is_sum_ok = self._sum_limit[0] <= initial_sum < self._sum_limit[1]
        is_period_ok = self._period_limit[0] <= period < self._period_limit[1]
        assert is_sum_ok and is_period_ok, "Условия вклада не соблюдены!"

    def get_profit(self, initial_sum, period):
        """Вернуть прибыль по вкладу вклада клиента."""
        self._check_user_params(initial_sum, period)
        return initial_sum * self._interest_rate / 100 * period / 12

    def get_sum(self, initial_sum, period):
        """Вернуть сумму вклада клиента после начисления прибыли."""
        return initial_sum + self.get_profit(initial_sum, period)


class BonusTimeDeposit(TimeDeposit):
    """Cрочный вклад c получением бонуса к концу срока вклада."""

    def __init__(self, name, interest_rate, period_limit, sum_limit, bonus):
        """Инициализировать атрибуты класса."""
        self._bonus = bonus
        super().__init__(name, interest_rate, period_limit, sum_limit)

    def __str__(self):
        """Вернуть строковое представление депозита."""
        return (super().__str__() + "\n"
                f"Бонус (%):          {self._bonus['percent']}\n"
                f"Бонус (мин. сумма): {self._bonus['sum']:,.0f}")

    def _check_self(self):
        """Проверить, что данные депозита являются допустимыми."""
        super()._check_self()
        assert 0 < self._bonus['percent'] <= 100, "Неверно указан бонусный процент!"
        assert 0 < self._bonus['sum'], "Неверно указана минимальная сумма для бонуса!"

    def get_profit(self, initial_sum, period):
        """Вернуть прибыль по вкладу вклада клиента."""
        profit = super().get_profit(initial_sum, period)
        if initial_sum >= self._bonus['sum']:
            profit += profit * self._bonus['percent'] / 100
        return profit


class CompoundTimeDeposit(TimeDeposit):
    """Cрочный вклад c ежемесячной капитализацией процентов."""

    def __str__(self):
        """Вернуть строковое представление депозита."""
        return (super().__str__() + "\n"
                f"Капитализация %:    Да")

    def get_profit(self, initial_sum, period):
        """Вернуть прибыль по вкладу вклада клиента."""
        self._check_user_params(initial_sum, period)
        return initial_sum * (1 + self._interest_rate / 100 / 12) ** period - initial_sum


# Список имеющихся депозитов
deposits_data = dict(interest_rate=5, period_limit=(6, 18), sum_limit=(1000, 100000))

deposits = (
    TimeDeposit("Сохраняй", interest_rate=5, period_limit=(6, 18), sum_limit=(1000, 100000)),
    BonusTimeDeposit("Бонусный 2", **deposits_data, bonus=dict(percent=5, sum=2000)),
    CompoundTimeDeposit("С капитализацией", **deposits_data),
    TimeDeposit("Накопительный", interest_rate=4.5, period_limit=(12, 24), sum_limit=(5000, 50000)),
    BonusTimeDeposit("Бонусный 3", interest_rate=6, period_limit=(6, 12), sum_limit=(10000, 200000), bonus=dict(percent=10, sum=5000)),
    CompoundTimeDeposit("Капитализация Плюс", interest_rate=5.5, period_limit=(12, 36), sum_limit=(2000, 150000))
)