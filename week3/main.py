class Roman:
    """
    A class to represent a Roman numeral.

    Attributes
    ----------
    value : int
        The integer value of the Roman numeral.

    Methods
    -------
    to_arabic(roman):
        Converts a Roman numeral to an integer.
    to_roman(number):
        Converts an integer to a Roman numeral.
    __str__():
        Returns the Roman numeral as a string.
    __add__(other):
        Adds two Roman numerals.
    __sub__(other):
        Subtracts two Roman numerals.
    __mul__(other):
        Multiplies two Roman numerals.
    __truediv__(other):
        Divides two Roman numerals.
    """

    def __init__(self, value):
        """
        Constructs all the necessary attributes for the Roman object.

        Parameters
        ----------
        value : str or int
            The Roman numeral or integer value.
        """
        if isinstance(value, str):
            self.value = self.to_arabic(value)
        elif isinstance(value, int):
            if not 1 <= value <= 3999:
                raise ValueError("Number must be between 1 and 3999.")
            self.value = value
        else:
            raise TypeError("Value must be a string or an integer.")

    @staticmethod
    def to_arabic(roman):
        """
        Converts a Roman numeral to an integer.

        Parameters
        ----------
        roman : str
            The Roman numeral.

        Returns
        -------
        int
            The integer value of the Roman numeral.
        """
        roman_values = {'I': 1, 'V': 5, 'X': 10, 'L': 50,
                        'C': 100, 'D': 500, 'M': 1000}
        total = 0
        prev_value = 0

        for char in reversed(roman):
            if char not in roman_values:
                raise ValueError(f"Invalid Roman numeral character: {char}")
            current_value = roman_values[char]
            if current_value < prev_value:
                total -= current_value
            else:
                total += current_value
            prev_value = current_value

        return total

    @staticmethod
    def to_roman(number):
        """
        Converts an integer to a Roman numeral.

        Parameters
        ----------
        number : int
            The integer value.

        Returns
        -------
        str
            The Roman numeral.
        """
        if not 1 <= number <= 3999:
            raise ValueError("Number must be between 1 and 3999.")

        thousands = ["", "M", "MM", "MMM"]
        hundreds = ["", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"]
        tens = ["", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"]
        ones = ["", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"]

        return (thousands[number // 1000] +
                hundreds[(number % 1000) // 100] +
                tens[(number % 100) // 10] +
                ones[number % 10])

    def __str__(self):
        """
        Returns the Roman numeral as a string.

        Returns
        -------
        str
            The Roman numeral.
        """
        return self.to_roman(self.value)

    def __add__(self, other):
        """
        Adds two Roman numerals.

        Parameters
        ----------
        other : Roman
            The other Roman numeral.

        Returns
        -------
        Roman
            The sum of the two Roman numerals.
        """
        if not isinstance(other, Roman):
            return NotImplemented
        return Roman(self.value + other.value)

    def __sub__(self, other):
        """
        Subtracts two Roman numerals.

        Parameters
        ----------
        other : Roman
            The other Roman numeral.

        Returns
        -------
        Roman
            The difference of the two Roman numerals.
        """
        if not isinstance(other, Roman):
            return NotImplemented
        result = self.value - other.value
        if result < 1:
            raise ValueError("Result cannot be less than 1.")
        return Roman(result)

    def __mul__(self, other):
        """
        Multiplies two Roman numerals.

        Parameters
        ----------
        other : Roman
            The other Roman numeral.

        Returns
        -------
        Roman
            The product of the two Roman numerals.
        """
        if not isinstance(other, Roman):
            return NotImplemented
        return Roman(self.value * other.value)

    def __truediv__(self, other):
        """
        Divides two Roman numerals.

        Parameters
        ----------
        other : Roman
            The other Roman numeral.

        Returns
        -------
        Roman
            The quotient of the two Roman numerals.
        """
        if not isinstance(other, Roman):
            return NotImplemented
        if other.value == 0:
            raise ZeroDivisionError("Division by zero.")
        result = self.value // other.value
        if result < 1:
            raise ValueError("Result of division is less than 1.")
        return Roman(result)

a = Roman("XIV")  # 14
b = Roman(7)      # 7

print(a + b)  # XXI (21)
print(a - b)  # VII (7)
print(a * b)  # XCVIII (98)
print(a / b)  # II (2)