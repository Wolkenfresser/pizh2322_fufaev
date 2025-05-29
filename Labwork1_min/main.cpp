#include <iostream>
#include <string>
using namespace std;

class Question {
private:
    string text;
    string answer;
    int points;
public:
    // Геттеры
    string getText() { return text; }
    string getAnswer() { return answer; }
    int getPoints() { return points; }

    // Сеттеры
    void setText(string text) { this->text = text; }
    void setAnswer(string answer) { this->answer = answer; }
    void setPoints(int points) { this->points = points; }

    // Перегруженные методы для установки свойств
    void setProperties() {
        string input;
        cout << "Enter question text: ";
        getline(cin, input);
        setText(input);
        cout << "Enter answer: ";
        getline(cin, input);
        setAnswer(input);
        cout << "Enter points: ";
        cin >> points;
        cin.ignore(); // Очистка буфера
    }

    void setProperties(string text, string answer, int points) {
        setText(text);
        setAnswer(answer);
        setPoints(points);
    }
};

class Test {
private:
    string subject;
    string difficulty;
    Question questions[10]; // Массив объектов Question
public:
    // Геттеры и сеттеры
    string getSubject() { return subject; }
    void setSubject(string subject) { this->subject = subject; }
    string getDifficulty() { return difficulty; }
    void setDifficulty(string difficulty) { this->difficulty = difficulty; }

    // Методы для работы с массивом
    void setQuestion(Question question, int index) {
        if (index >= 0 && index < 10) questions[index] = question;
        else cout << "Invalid index!" << endl;
    }
    Question getQuestion(int index) {
        if (index >= 0 && index < 10) return questions[index];
        throw runtime_error("Invalid index!");
    }
};

int main() {
    Test test;
    string input;

    // Установка данных теста
    cout << "Enter subject: ";
    getline(cin, input);
    test.setSubject(input);
    cout << "Enter difficulty: ";
    getline(cin, input);
    test.setDifficulty(input);

    // Заполнение массива вопросов (первые 5 с помощью метода без параметров)
    for (int i = 0; i < 5; i++) {
        cout << "Question " << i + 1 << ":\n";
        Question question;
        question.setProperties();
        test.setQuestion(question, i);
    }

    // Заполнение оставшихся 5 с помощью перегруженного метода
    for (int i = 5; i < 10; i++) {
        cout << "Question " << i + 1 << ":\n";
        Question question;
        string text, answer;
        int points;
        cout << "Enter question text: ";
        getline(cin, text);
        cout << "Enter answer: ";
        getline(cin, answer);
        cout << "Enter points: ";
        cin >> points;
        cin.ignore(); // Очистка буфера
        question.setProperties(text, answer, points);
        test.setQuestion(question, i);
    }

    // Вывод данных
    cout << "\nTest Details:\n";
    cout << "Subject: " << test.getSubject() << "\nDifficulty: " << test.getDifficulty() << "\nQuestions:\n";
    for (int i = 0; i < 10; i++) {
        Question question = test.getQuestion(i);
        cout << "Question " << i + 1 << ": Text: " << question.getText()
             << ", Answer: " << question.getAnswer()
             << ", Points: " << question.getPoints() << endl;
    }

    return 0;
}