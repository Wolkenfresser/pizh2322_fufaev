class Food:
    """
    A class to represent a food item.

    Attributes
    ----------
    name : str
        The name of the food item.
    dough : str
        The type of dough used in the food item.
    sauce : str
        The type of sauce used in the food item.
    topping : str
        The type of topping used in the food item.

    Methods
    -------
    prepare():
        Prints a message indicating the food item is being prepared.
    bake():
        Prints a message indicating the food item is being baked.
    cut():
        Prints a message indicating the food item is being cut.
    pack():
        Prints a message indicating the food item is being packed.
    """

    def __init__(self, name, dough, sauce, topping):
        """
        Constructs all the necessary attributes for the food item object.

        Parameters
        ----------
        name : str
            The name of the food item.
        dough : str
            The type of dough used in the food item.
        sauce : str
            The type of sauce used in the food item.
        topping : str
            The type of topping used in the food item.
        """
        self.name = name
        self.dough = dough
        self.sauce = sauce
        self.topping = topping

    def prepare(self):
        """
        Prints a message indicating the food item is being prepared.
        """
        print(f"Preparing {self.name}: Kneading {self.dough} dough, adding {self.sauce} sauce, and {self.topping} topping.")

    def bake(self):
        """
        Prints a message indicating the food item is being baked.
        """
        print(f"Baking {self.name}.")

    def cut(self):
        """
        Prints a message indicating the food item is being cut.
        """
        print(f"Cutting {self.name}.")

    def pack(self):
        """
        Prints a message indicating the food item is being packed.
        """
        print(f"Packing {self.name}.")


class Pepperoni(Food):
    """
    A class to represent a Pepperoni food item.

    Attributes
    ----------
    name : str
        The name of the food item.
    dough : str
        The type of dough used in the food item.
    sauce : str
        The type of sauce used in the food item.
    topping : str
        The type of topping used in the food item.

    Methods
    -------
    prepare():
        Prints a message indicating the food item is being prepared.
    bake():
        Prints a message indicating the food item is being baked.
    cut():
        Prints a message indicating the food item is being cut.
    pack():
        Prints a message indicating the food item is being packed.
    """

    def __init__(self):
        """
        Constructs all the necessary attributes for the Pepperoni food item object.
        """
        super().__init__("Pepperoni", "thin crust", "tomato", "pepperoni")


class BBQ(Food):
    """
    A class to represent a BBQ food item.

    Attributes
    ----------
    name : str
        The name of the food item.
    dough : str
        The type of dough used in the food item.
    sauce : str
        The type of sauce used in the food item.
    topping : str
        The type of topping used in the food item.

    Methods
    -------
    prepare():
        Prints a message indicating the food item is being prepared.
    bake():
        Prints a message indicating the food item is being baked.
    cut():
        Prints a message indicating the food item is being cut.
    pack():
        Prints a message indicating the food item is being packed.
    """

    def __init__(self):
        """
        Constructs all the necessary attributes for the BBQ food item object.
        """
        super().__init__("BBQ", "thick crust", "barbecue", "chicken")


class Seafood(Food):
    """
    A class to represent a Seafood food item.

    Attributes
    ----------
    name : str
        The name of the food item.
    dough : str
        The type of dough used in the food item.
    sauce : str
        The type of sauce used in the food item.
    topping : str
        The type of topping used in the food item.

    Methods
    -------
    prepare():
        Prints a message indicating the food item is being prepared.
    bake():
        Prints a message indicating the food item is being baked.
    cut():
        Prints a message indicating the food item is being cut.
    pack():
        Prints a message indicating the food item is being packed.
    """

    def __init__(self):
        """
        Constructs all the necessary attributes for the Seafood food item object.
        """
        super().__init__("Seafood", "thin crust", "alfredo", "seafood mix")


class Order:
    """
    A class to represent an order.

    Attributes
    ----------
    items : list
        A list of food items in the order.

    Methods
    -------
    add_item(food):
        Adds a food item to the order.
    calculate_total():
        Calculates the total cost of the order.
    display_order():
        Displays the order and the total cost.
    """

    def __init__(self):
        """
        Constructs all the necessary attributes for the order object.
        """
        self.items = []

    def add_item(self, food):
        """
        Adds a food item to the order.

        Parameters
        ----------
        food : Food
            The food item to be added to the order.
        """
        self.items.append(food)

    def calculate_total(self):
        """
        Calculates the total cost of the order.

        Returns
        -------
        int
            The total cost of the order.
        """
        return len(self.items) * 10  # Assuming each food item costs $10

    def display_order(self):
        """
        Displays the order and the total cost.
        """
        print("Your order:")
        for item in self.items:
            print(f"- {item.name}")
        print(f"Total: ${self.calculate_total()}")


class Terminal:
    """
    A class to represent a terminal.

    Attributes
    ----------
    menu : dict
        A dictionary of food items available in the menu.

    Methods
    -------
    display_menu():
        Displays the menu.
    take_order():
        Takes an order from the user.
    process_payment(amount):
        Processes the payment for the order.
    complete_order(order):
        Completes the order.
    """

    def __init__(self):
        """
        Constructs all the necessary attributes for the terminal object.
        """
        self.menu = {
            1: Pepperoni(),
            2: BBQ(),
            3: Seafood()
        }

    def display_menu(self):
        """
        Displays the menu.
        """
        print("Menu:")
        for key, value in self.menu.items():
            print(f"{key}. {value.name}")

    def take_order(self):
        """
        Takes an order from the user.

        Returns
        -------
        Order
            The order taken from the user.
        """
        order = Order()
        while True:
            self.display_menu()
            choice = input("Enter the number of the food you want to order (or 'done' to finish): ")
            if choice == 'done':
                break
            try:
                choice = int(choice)
                if choice in self.menu:
                    order.add_item(self.menu[choice])
                    print(f"{self.menu[choice].name} added to your order.")
                else:
                    print("Invalid choice. Please try again.")
            except ValueError:
                print("Invalid input. Please enter a number.")
        return order

    def process_payment(self, amount):
        """
        Processes the payment for the order.

        Parameters
        ----------
        amount : int
            The total cost of the order.
        """
        print(f"Processing payment of ${amount}...")
        print("Payment successful.")

    def complete_order(self, order):
        """
        Completes the order.

        Parameters
        ----------
        order : Order
            The order to be completed.
        """
        for item in order.items:
            item.prepare()
            item.bake()
            item.cut()
            item.pack()
        print("Order is ready. Thank you!")


def main():
    """
    The main function of the program.
    """
    terminal = Terminal()
    print("Welcome to the Pizzeria!")
    order = terminal.take_order()
    order.display_order()
    terminal.process_payment(order.calculate_total())
    terminal.complete_order(order)


if __name__ == "__main__":
    main()

