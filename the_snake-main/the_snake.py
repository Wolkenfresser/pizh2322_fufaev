from random import choice, randint
import pygame

# Константы для размеров поля и сетки
SCREEN_WIDTH, SCREEN_HEIGHT = 640, 480
GRID_SIZE = 20
GRID_WIDTH = SCREEN_WIDTH // GRID_SIZE
GRID_HEIGHT = SCREEN_HEIGHT // GRID_SIZE

# Все возможные ячейки поля
ALL_CELLS = set((x * GRID_SIZE, y * GRID_SIZE) for x in range(GRID_WIDTH) for y in range(GRID_HEIGHT))

# Направления движения
UP = (0, -1)
DOWN = (0, 1)
LEFT = (-1, 0)
RIGHT = (1, 0)

# Цвета
BOARD_BACKGROUND_COLOR = (0, 0, 0)
BORDER_COLOR = (93, 216, 228)
APPLE_COLOR = (255, 0, 0)
SNAKE_COLOR = (0, 255, 0)

# Скорость движения змейки
SPEED = 10

# Настройка игрового окна
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT), 0, 32)
pygame.display.set_caption('Змейка')
clock = pygame.time.Clock()


class GameObject:
    """Базовый класс для объектов игры."""
    def __init__(self, position=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2), body_color=(255, 255, 255)):
        self.position = position
        self.body_color = body_color

    def draw(self, surface):
        """Абстрактный метод для отрисовки объекта."""
        pass


class Apple(GameObject):
    """Класс для яблока."""
    def __init__(self, snake_positions=None):
        super().__init__(body_color=APPLE_COLOR)
        # Если snake_positions не передан, используем начальную позицию по умолчанию
        if snake_positions is None:
            snake_positions = [(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)]
        self.randomize_position(snake_positions)

    def randomize_position(self, snake_positions):
        """Устанавливает случайную позицию яблока, исключая позиции змейки."""
        available_cells = list(ALL_CELLS - set(snake_positions))
        self.position = choice(available_cells) if available_cells else (0, 0)

    def draw(self, surface):
        """Отрисовывает яблоко на экране."""
        rect = pygame.Rect(self.position, (GRID_SIZE, GRID_SIZE))
        pygame.draw.rect(surface, self.body_color, rect)
        pygame.draw.rect(surface, BORDER_COLOR, rect, 1)


class Snake(GameObject):
    """Класс для змейки."""
    def __init__(self):
        super().__init__(position=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2), body_color=SNAKE_COLOR)
        self.length = 1
        self.positions = [self.position]
        self.direction = RIGHT
        self.next_direction = None
        self.last = None

    def update_direction(self):
        """Обновляет направление движения."""
        if self.next_direction:
            self.direction = self.next_direction
            self.next_direction = None

    def move(self):
        """Обновляет позицию змейки."""
        head_x, head_y = self.get_head_position()
        dx, dy = self.direction
        new_head = ((head_x + dx * GRID_SIZE) % SCREEN_WIDTH, (head_y + dy * GRID_SIZE) % SCREEN_HEIGHT)
        self.positions.insert(0, new_head)
        if len(self.positions) > self.length:
            self.last = self.positions.pop()
        else:
            self.last = None

    def get_head_position(self):
        """Возвращает позицию головы змейки."""
        return self.positions[0]

    def reset(self):
        """Сбрасывает змейку в начальное состояние."""
        self.length = 1
        self.positions = [(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)]
        self.direction = RIGHT
        self.next_direction = None
        self.last = None

    def draw(self, surface):
        """Отрисовывает змейку на экране."""
        for position in self.positions[:-1]:
            rect = pygame.Rect(position, (GRID_SIZE, GRID_SIZE))
            pygame.draw.rect(surface, self.body_color, rect)
            pygame.draw.rect(surface, BORDER_COLOR, rect, 1)

        # Отрисовка головы змейки
        head_rect = pygame.Rect(self.positions[0], (GRID_SIZE, GRID_SIZE))
        pygame.draw.rect(surface, self.body_color, head_rect)
        pygame.draw.rect(surface, BORDER_COLOR, head_rect, 1)

        # Затирание последнего сегмента
        if self.last:
            last_rect = pygame.Rect(self.last, (GRID_SIZE, GRID_SIZE))
            pygame.draw.rect(surface, BOARD_BACKGROUND_COLOR, last_rect)


def handle_keys(game_object):
    """Обрабатывает нажатия клавиш."""
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            raise SystemExit
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                pygame.quit()
                raise SystemExit
            elif event.key == pygame.K_UP and game_object.direction != DOWN:
                game_object.next_direction = UP
            elif event.key == pygame.K_DOWN and game_object.direction != UP:
                game_object.next_direction = DOWN
            elif event.key == pygame.K_LEFT and game_object.direction != RIGHT:
                game_object.next_direction = LEFT
            elif event.key == pygame.K_RIGHT and game_object.direction != LEFT:
                game_object.next_direction = RIGHT


def main():
    """Основной игровой цикл."""
    pygame.init()
    snake = Snake()
    apple = Apple(snake.positions)
    max_length = 1  # Рекордный размер змейки

    while True:
        clock.tick(SPEED)
        handle_keys(snake)
        snake.update_direction()
        snake.move()

        # Проверка на съедение яблока
        if snake.get_head_position() == apple.position:
            snake.length += 1
            max_length = max(max_length, snake.length)
            apple.randomize_position(snake.positions)

        # Проверка на самопересечение (если длина > 1)
        if snake.length > 1 and snake.get_head_position() in snake.positions[1:]:
            snake.reset()
            apple.randomize_position(snake.positions)

        # Отрисовка
        screen.fill(BOARD_BACKGROUND_COLOR)
        snake.draw(screen)
        apple.draw(screen)
        pygame.display.set_caption(f'Змейка | Рекорд: {max_length}')
        pygame.display.update()


if __name__ == '__main__':
    main()