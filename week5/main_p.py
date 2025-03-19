# main.py
from player import AudioPlayer, VideoPlayer, DvdPlayer

if __name__ == "__main__":
    # Создаем объекты
    audio = AudioPlayer()
    video = VideoPlayer()
    dvd = DvdPlayer("Фильм 'Интерстеллар'")

    print("\n--- Тестирование Аудиоплеера ---")
    audio.выбрать_трек("Imagine Dragons - Believer")
    audio.запустить()
    audio.перемотать(30)
    audio.остановить()
    audio.установить_громкость(75)

    print("\n--- Тестирование Видеоплеера ---")
    video.выбрать_файл("video.mp4")
    video.запустить()
    video.перемотать(120)
    video.остановить()

    print("\n--- Тестирование DVD-плеера ---")
    dvd.запустить()
    dvd.перемотать(300)
    dvd.остановить()
    dvd.статус()
    dvd.извлечь_диск()
    dvd.статус()
    dvd.вставить_диск("Фильм 'Гарри Поттер'")
    dvd.статус()
    dvd.запустить()
