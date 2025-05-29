#include <iostream>
#include <string>
using namespace std;

class TestItem {
protected:
    string text;
public:
    TestItem() : text("No text") {
        cout << "TestItem: Default constructor\n";
    }

    TestItem(string text) : text(text) {
        cout << "TestItem: Constructor with parameters\n";
    }

    TestItem(const TestItem& other) : text(other.text) {
        cout << "TestItem: Copy constructor\n";
    }

    virtual ~TestItem() {
        cout << "TestItem: Destructor\n";
    }

    virtual string getText() { return text; }
    void setText(string text) { this->text = text; }

    virtual void display() {
        cout << "Text: " << text << endl;
    }
};

class Question : public TestItem {
private:
    string answer;
    int points;
public:
    Question() : TestItem(), answer("No answer"), points(0) {
        cout << "Question: Default constructor\n";
    }

    Question(string text, string answer, int points) : TestItem(text), answer(answer), points(points) {
        cout << "Question: Constructor with parameters\n";
    }

    Question(const Question& other) : TestItem(other), answer(other.answer), points(other.points) {
        cout << "Question: Copy constructor\n";
    }

    ~Question() override {
        cout << "Question: Destructor\n";
    }

    string getAnswer() { return answer; }
    int getPoints() { return points; }

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

    void display() override {
        cout << "Question - Text: " << text << ", Answer: " << answer << ", Points: " << points << endl;
    }
};

class Test {
private:
    string subject;
    string difficulty;
    TestItem* questions[10]; // Массив указателей на TestItem
public:
    Test() : subject("No subject"), difficulty("No difficulty") {
        for (int i = 0; i < 10; i++) questions[i] = nullptr;
        cout << "Test: Default constructor\n";
    }

    Test(string subject, string difficulty) : subject(subject), difficulty(difficulty) {
        for (int i = 0; i < 10; i++) questions[i] = nullptr;
        cout << "Test: Constructor with parameters\n";
    }

    Test(const Test& other) : subject(other.subject), difficulty(other.difficulty) {
        for (int i = 0; i < 10; i++) {
            if (other.questions[i]) questions[i] = new Question(*dynamic_cast<Question*>(other.questions[i]));
            else questions[i] = nullptr;
        }
        cout << "Test: Copy constructor\n";
    }

    ~Test() {
        for (int i = 0; i < 10; i++) {
            delete questions[i];
        }
        cout << "Test: Destructor\n";
    }

    string getSubject() { return subject; }
    void setSubject(string subject) { this->subject = subject; }
    string getDifficulty() { return difficulty; }
    void setDifficulty(string difficulty) { this->difficulty = difficulty; }

    void setQuestion(TestItem* question, int index) {
        if (index >= 0 && index < 10) {
            delete questions[index];
            questions[index] = question;
        } else {
            cout << "Invalid index!" << endl;
        }
    }

    TestItem* getQuestion(int index) {
        if (index >= 0 && index < 10) return questions[index];
        throw runtime_error("Invalid index!");
    }

    void addNewQuestion(string text, string answer, int points, int index) {
        setQuestion(new Question(text, answer, points), index);
    }

    void addCopiedQuestions(Question& question, int count) {
        for (int i = 0; i < count && i < 10; i++) {
            setQuestion(new Question(question), i);
        }
    }
};

int main() {
    Test test("Math", "Hard");

    test.addNewQuestion("What is 2+2?", "4", 10, 0);

    Question question1;
    question1.setProperties();
    test.setQuestion(new Question(question1), 1);

    cout << "\nCopying question to multiple slots:\n";
    test.addCopiedQuestions(question1, 3);

    cout << "\nTest Details:\n";
    cout << "Subject: " << test.getSubject() << "\nDifficulty: " << test.getDifficulty() << "\nQuestions:\n";
    for (int i = 0; i < 10; i++) {
        TestItem* question = test.getQuestion(i);
        if (question) {
            cout << "Question " << i + 1 << ": ";
            question->display();
        } else {
            cout << "Question " << i + 1 << ": Empty slot\n";
        }
    }

    return 0;
}