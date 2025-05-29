#include <iostream>
#include <string>
using namespace std;

class Question {
private:
    string text;
    string answer;
    int points;
public:
    // Конструкторы
    Question() : text("No text"), answer("No answer"), points(0) {
        cout << "Question: Default constructor\n";
    }

    Question(string text, string answer, int points) : text(text), answer(answer), points(points) {
        cout << "Question: Constructor with parameters\n";
    }

    Question(const Question& other) : text(other.text), answer(other.answer), points(other.points) {
        cout << "Question: Copy constructor\n";
    }

    // Деструктор
    ~Question() {
        cout << "Question: Destructor\n";
    }

    // Геттеры
    string getText() { return text; }
    string getAnswer() { return answer; }
    int getPoints() { return points; }

    // Сеттеры
    void setText(string text) { this->text = text; }
    void setAnswer(string answer) { this->answer = answer; }
    void setPoints(int points) { this->points = points; }

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
    Question questions[10];
public:
    // Конструкторы
    Test() : subject("No subject"), difficulty("No difficulty") {
        cout << "Test: Default constructor\n";
    }

    Test(string subject, string difficulty) : subject(subject), difficulty(difficulty) {
        cout << "Test: Constructor with parameters\n";
    }

    Test(const Test& other) : subject(other.subject), difficulty(other.difficulty) {
        for (int i = 0; i < 10; i++) questions[i] = other.questions[i];
        cout << "Test: Copy constructor\n";
    }

    // Деструктор
    ~Test() {
        cout << "Test: Destructor\n";
    }

    // Геттеры и сеттеры
    string getSubject() { return subject; }
    void setSubject(string subject) { this->subject = subject; }
    string getDifficulty() { return difficulty; }
    void setDifficulty(string difficulty) { this->difficulty = difficulty; }

    void setQuestion(Question question, int index) {
        if (index >= 0 && index < 10) questions[index] = question;
        else cout << "Invalid index!" << endl;
    }

    Question getQuestion(int index) {
        if (index >= 0 && index < 10) return questions[index];
        throw runtime_error("Invalid index!");
    }

    // Новый метод для добавления вопроса через конструктор с параметрами
    void addNewQuestion(string text, string answer, int points, int index) {
        Question question(text, answer, points);
        setQuestion(question, index);
    }

    // Новый метод для копирования вопроса
    void addCopiedQuestions(Question& question, int count) {
        for (int i = 0; i < count && i < 10; i++) {
            Question newQuestion(question); // Вызов конструктора копирования
            setQuestion(newQuestion, i);
        }
    }
};

int main() {
    // Демонстрация конструктора с параметрами
    Test test("Math", "Hard");
    cout << "Test created with parameters.\n\n";

    // Демонстрация добавления вопроса через конструктор с параметрами
    test.addNewQuestion("What is 2+2?", "4", 10, 0);

    // Демонстрация конструктора по умолчанию для вопроса
    Question question1;
    question1.setProperties(); // Ввод с консоли
    test.setQuestion(question1, 1);

    // Демонстрация конструктора копирования
    cout << "\nCopying question to multiple slots:\n";
    test.addCopiedQuestions(question1, 3); // Копируем вопрос в первые 3 слота

    // Демонстрация конструктора по умолчанию для теста
    Test test2;
    test2.setSubject("Physics");
    test2.setDifficulty("Medium");

    // Вывод данных
    cout << "\nTest 1 Details:\n";
    cout << "Subject: " << test.getSubject() << "\nDifficulty: " << test.getDifficulty() << "\nQuestions:\n";
    for (int i = 0; i < 10; i++) {
        try {
            Question question = test.getQuestion(i);
            cout << "Question " << i + 1 << ": Text: " << question.getText()
                 << ", Answer: " << question.getAnswer()
                 << ", Points: " << question.getPoints() << endl;
        } catch (...) {
            cout << "Question " << i + 1 << ": Empty slot\n";
        }
    }

    cout << "\nTest 2 Details:\n";
    cout << "Subject: " << test2.getSubject() << "\nDifficulty: " << test2.getDifficulty() << "\n";

    return 0;
}