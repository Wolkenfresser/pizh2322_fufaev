#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <thread>
#include <fstream>
using namespace std;

class TestItem {
protected:
    string text;
public:
    TestItem() : text("No text") {}
    TestItem(string text) : text(text) {}
    TestItem(const TestItem& other) : text(other.text) {}
    virtual ~TestItem() {}
    virtual string getText() { return text; }
    void setText(string text) { this->text = text; }
    virtual void display() = 0;
    virtual int calculateScore() = 0;
    virtual void saveToFile(ofstream& file) = 0;
    virtual void loadFromFile(ifstream& file) = 0;
};

class Question : public TestItem {
private:
    string answer;
    int points;
public:
    Question() : TestItem(), answer("No answer"), points(0) {}
    Question(string text, string answer, int points) : TestItem(text), answer(answer), points(points) {}
    Question(const Question& other) : TestItem(other), answer(other.answer), points(other.points) {}
    ~Question() {}
    string getAnswer() { return answer; }
    int getPoints() { return points; }
    void setAnswer(string answer) { this->answer = answer; }
    void setPoints(int points) { if (points < 0) throw invalid_argument("Points cannot be negative"); this->points = points; }
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
        cin.ignore();
    }
    void setProperties(string text, string answer, int points) {
        setText(text);
        setAnswer(answer);
        if (points < 0) throw invalid_argument("Points cannot be negative");
        setPoints(points);
    }
    void display() override {
        cout << "Question - Text: " << text << ", Answer: " << answer << ", Points: " << points << endl;
    }
    int calculateScore() override {
        string userAnswer;
        cout << "Enter your answer for '" << text << "': ";
        getline(cin, userAnswer);
        return (userAnswer == answer) ? points : 0;
    }
    void saveToFile(ofstream& file) override {
        file << "Question\n" << text << "\n" << answer << "\n" << points << "\n";
    }
    void loadFromFile(ifstream& file) override {
        string type;
        getline(file, type);
        if (type != "Question") throw runtime_error("Invalid file format");
        getline(file, text);
        getline(file, answer);
        file >> points;
        file.ignore();
    }
};

class MultipleChoiceQuestion : public TestItem {
private:
    vector<string> options;
    int correctOptionIndex;
    int points;
public:
    MultipleChoiceQuestion() : TestItem(), correctOptionIndex(0), points(0) {}
    MultipleChoiceQuestion(string text, vector<string> options, int correctOptionIndex, int points) 
        : TestItem(text), options(options), correctOptionIndex(correctOptionIndex), points(points) {}
    MultipleChoiceQuestion(const MultipleChoiceQuestion& other) 
        : TestItem(other), options(other.options), correctOptionIndex(other.correctOptionIndex), points(other.points) {}
    ~MultipleChoiceQuestion() {}
    vector<string> getOptions() { return options; }
    int getCorrectOptionIndex() { return correctOptionIndex; }
    int getPoints() { return points; }
    void setOptions(vector<string> options) { this->options = options; }
    void setCorrectOptionIndex(int index) { if (index < 0 || index >= static_cast<int>(options.size())) throw out_of_range("Invalid option index"); correctOptionIndex = index; }
    void setPoints(int points) { if (points < 0) throw invalid_argument("Points cannot be negative"); this->points = points; }
    void setProperties() {
        string input;
        cout << "Enter question text: ";
        getline(cin, input);
        setText(input);
        cout << "Enter number of options: ";
        int numOptions;
        cin >> numOptions;
        cin.ignore();
        if (numOptions <= 0) throw invalid_argument("Number of options must be positive");
        vector<string> opts(numOptions);
        for (int i = 0; i < numOptions; i++) {
            cout << "Enter option " << i + 1 << ": ";
            getline(cin, opts[i]);
        }
        setOptions(opts);
        cout << "Enter correct option index (0-based): ";
        cin >> correctOptionIndex;
        cin.ignore();
        cout << "Enter points: ";
        cin >> points;
        cin.ignore();
    }
    void display() override {
        cout << "Multiple Choice Question - Text: " << text << ", Options: ";
        for (size_t i = 0; i < options.size(); i++) {
            cout << (i == correctOptionIndex ? "*" : "") << options[i] << " ";
        }
        cout << ", Points: " << points << endl;
    }
    int calculateScore() override {
        display();
        int userChoice;
        cout << "Enter your choice (0-based index): ";
        cin >> userChoice;
        cin.ignore();
        if (userChoice < 0 || userChoice >= static_cast<int>(options.size())) throw out_of_range("Invalid choice index");
        return (userChoice == correctOptionIndex) ? points : 0;
    }
    void saveToFile(ofstream& file) override {
        file << "MultipleChoiceQuestion\n" << text << "\n" << options.size() << "\n";
        for (const auto& opt : options) {
            file << opt << "\n";
        }
        file << correctOptionIndex << "\n" << points << "\n";
    }
    void loadFromFile(ifstream& file) override {
        string type;
        getline(file, type);
        if (type != "MultipleChoiceQuestion") throw runtime_error("Invalid file format");
        getline(file, text);
        int numOptions;
        file >> numOptions;
        file.ignore();
        vector<string> opts(numOptions);
        for (int i = 0; i < numOptions; i++) {
            getline(file, opts[i]);
        }
        setOptions(opts);
        file >> correctOptionIndex;
        file.ignore();
        file >> points;
        file.ignore();
    }
};

template <typename T>
class Result {
private:
    T score;
    string studentName;
public:
    Result() : score(0), studentName("No name") {}
    Result(T score, string studentName) : score(score), studentName(studentName) {}
    T getScore() { return score; }
    string getStudentName() { return studentName; }
    void setScore(T score) { this->score = score; }
    void setStudentName(string studentName) { this->studentName = studentName; }
    void display() {
        cout << "Student: " << studentName << ", Score: " << score << endl;
    }
    Result<T> operator+(const Result<T>& other) {
        return Result<T>(this->score + other.score, this->studentName + " & " + other.studentName);
    }
    friend ostream& operator<<(ostream& os, const Result<T>& result) {
        os << "Student: " << result.studentName << ", Score: " << result.score;
        return os;
    }
    void saveToFile(ofstream& file) {
        file << "Result\n" << score << "\n" << studentName << "\n";
    }
    void loadFromFile(ifstream& file) {
        string type;
        getline(file, type);
        if (type != "Result") throw runtime_error("Invalid file format");
        file >> score;
        file.ignore();
        getline(file, studentName);
    }
};

class Test {
private:
    string subject;
    string difficulty;
    TestItem* items[10];
public:
    Test() : subject("No subject"), difficulty("No difficulty") {
        for (int i = 0; i < 10; i++) items[i] = nullptr;
    }
    Test(string subject, string difficulty) : subject(subject), difficulty(difficulty) {
        for (int i = 0; i < 10; i++) items[i] = nullptr;
    }
    Test(const Test& other) : subject(other.subject), difficulty(other.difficulty) {
        for (int i = 0; i < 10; i++) {
            if (dynamic_cast<Question*>(other.items[i])) {
                items[i] = new Question(*dynamic_cast<Question*>(other.items[i]));
            } else if (dynamic_cast<MultipleChoiceQuestion*>(other.items[i])) {
                items[i] = new MultipleChoiceQuestion(*dynamic_cast<MultipleChoiceQuestion*>(other.items[i]));
            } else {
                items[i] = nullptr;
            }
        }
    }
    ~Test() {
        for (int i = 0; i < 10; i++) {
            delete items[i];
        }
    }
    string getSubject() { return subject; }
    void setSubject(string subject) { this->subject = subject; }
    string getDifficulty() { return difficulty; }
    void setDifficulty(string difficulty) { this->difficulty = difficulty; }
    void setItem(TestItem* item, int index) {
        if (index >= 0 && index < 10) {
            delete items[index];
            items[index] = item;
        } else {
            cout << "Invalid index!" << endl;
        }
    }
    TestItem* getItem(int index) {
        if (index >= 0 && index < 10) return items[index];
        throw runtime_error("Invalid index!");
    }
    void addNewQuestion(string text, string answer, int points, int index) {
        try {
            setItem(new Question(text, answer, points), index);
        } catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    void addNewMultipleChoiceQuestion(string text, vector<string> options, int correctIndex, int points, int index) {
        try {
            setItem(new MultipleChoiceQuestion(text, options, correctIndex, points), index);
        } catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        } catch (const out_of_range& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    int calculateTotalScore() {
        int total = 0;
        for (int i = 0; i < 10; i++) {
            if (items[i]) {
                try {
                    total += items[i]->calculateScore();
                } catch (const out_of_range& e) {
                    cout << "Error in item " << i + 1 << ": " << e.what() << endl;
                }
            }
        }
        return total;
    }
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) throw runtime_error("Cannot open file for writing");
        file << subject << "\n" << difficulty << "\n";
        for (int i = 0; i < 10; i++) {
            if (items[i]) {
                items[i]->saveToFile(file);
            } else {
                file << "Empty\n";
            }
        }
        file.close();
    }
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) throw runtime_error("Cannot open file for reading");
        getline(file, subject);
        getline(file, difficulty);
        for (int i = 0; i < 10; i++) {
            string type;
            getline(file, type);
            if (type == "Question") {
                Question* q = new Question();
                q->loadFromFile(file);
                setItem(q, i);
            } else if (type == "MultipleChoiceQuestion") {
                MultipleChoiceQuestion* mcq = new MultipleChoiceQuestion();
                mcq->loadFromFile(file);
                setItem(mcq, i);
            } else {
                setItem(nullptr, i);
            }
        }
        file.close();
    }
};

int main() {
    Test test("Math", "Hard");

    try {
        test.addNewQuestion("What is 2+2?", "4", 10, 0);
        vector<string> options = { "A) 1", "B) 2", "C) 3", "D) 4" };
        test.addNewMultipleChoiceQuestion("What is 2+2?", options, 3, 15, 1);
    } catch (const exception& e) {
        cout << "Setup error: " << e.what() << endl;
    }

    try {
        test.saveToFile("test.txt");
        cout << "Test saved to file.\n";
    } catch (const exception& e) {
        cout << "Save error: " << e.what() << endl;
    }

    Test test2;
    try {
        test2.loadFromFile("test.txt");
        cout << "Test loaded from file.\n";
    } catch (const exception& e) {
        cout << "Load error: " << e.what() << endl;
    }

    cout << "\nLoaded Test Details:\n";
    cout << "Subject: " << test2.getSubject() << "\nDifficulty: " << test2.getDifficulty() << "\nItems:\n";
    for (int i = 0; i < 10; i++) {
        TestItem* item = test2.getItem(i);
        if (item) {
            cout << "Item " << i + 1 << ": ";
            item->display();
        } else {
            cout << "Item " << i + 1 << ": Empty slot\n";
        }
    }

    return 0;
}