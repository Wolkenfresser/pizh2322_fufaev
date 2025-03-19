
class Player:
    """Базовый класс плеера."""

    def __init__(self, name: str):
        self.name = name  # Публичное поле
        self._position = 0  # Защищенное поле (позиция воспроизведения)
        self.__volume = 50  # Приватное поле (громкость)
        self.is_playing = False  # Публичное поле (состояние)

    def запустить(self):
        """Запуск плеера."""
        if self.is_playing:
            print(f"{self.name}: Уже играет с позиции {self._position} сек.")
        else:
            self.is_playing = True
            print(f"{self.name}: Воспроизведение начато с позиции {self._position} сек.")
        self.__log_action("запущен")

    def остановить(self):
        """Остановка плеера (сохраняем позицию)."""
        if self.is_playing:
            self.is_playing = False
            print(f"{self.name}: Остановлено на {self._position} сек.")
        else:
            print(f"{self.name}: Уже остановлен.")
        self.__log_action("остановлен")

    def перемотать(self, секунды: int):
        """Перемотка вперед/назад."""
        self._position = max(0, self._position + секунды)
        print(f"{self.name}: Перемотано, текущая позиция {self._position} сек.")

    def установить_громкость(self, уровень: int):
        """Установка громкости (0-100)."""
        self.__volume = max(0, min(100, уровень))
        print(f"{self.name}: Громкость установлена на {self.__volume}%.")

    def __log_action(self, действие: str):
        """Приватный метод логирования действий."""
        print(f"[LOG] {self.name}: {действие} (позиция: {self._position}, громкость: {self.__volume}%)")

class AudioPlayer(Player):
    """Аудиоплеер."""
    def __init__(self, name: str = "Аудиоплеер"):
        super().__init__(name)
        self.track = None  # Текущий трек

    def выбрать_трек(self, track: str):
        """Выбор трека для воспроизведения."""
        self.track = track
        self.position = 0  # Начинаем воспроизведение сначала
        print(f"{self.name}: Выбран трек '{self.track}'.")

class VideoPlayer(Player):
    """Видеоплеер."""
    def __init__(self, name: str = "Видеоплеер"):
        super().__init__(name)
        self.video_file = None  # Текущий видеофайл

    def выбрать_файл(self, file_name: str):
        """Выбор видеофайла для воспроизведения."""
        self.video_file = file_name
        self.position = 0
        print(f"{self.name}: Выбран видеофайл '{self.video_file}'.")

class DvdPlayer(Player):
    """DVD-плеер."""
    def __init__(self, dvd_disk: str, name: str = "DVD-плеер"):
        super().__init__(name)
        self.dvd_disk = dvd_disk  # Название DVD-диска
        self.is_disk_inserted = True  # Диск вставлен

    def запустить(self):
        """Запуск DVD-плеера с диском."""
        if not self.is_disk_inserted:
            print(f"{self.name}: Нет вставленного DVD-диска!")
        else:
            super().запустить()

    def остановить(self):
        """Остановка DVD-плеера с сохранением позиции."""
        if self.is_playing:
            self.position += 10  # Пример сохранения позиции
        super().остановить()

    def извлечь_диск(self):
        """Извлечение DVD-диска."""
        if self.is_disk_inserted:
            self.is_disk_inserted = False
            self.position = 0
            print(f"{self.name}: Диск '{self.dvd_disk}' извлечен.")
        else:
            print(f"{self.name}: Нет вставленного диска.")

    def вставить_диск(self, dvd_disk: str):
        """Вставка нового DVD-диска."""
        self.dvd_disk = dvd_disk
        self.is_disk_inserted = True
        self.position = 0
        print(f"{self.name}: Диск '{self.dvd_disk}' вставлен.")

    def статус(self):
        """Вывод текущего состояния плеера."""
        диск = f"Диск '{self.dvd_disk}'" if self.is_disk_inserted else "Нет диска"
        статус = "воспроизводится" if self.is_playing else "остановлено"
        print(f"{self.name}: {диск}, {статус}, позиция {self.position} сек., громкость {self.volume}%.")