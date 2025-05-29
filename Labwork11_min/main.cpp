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
    Result(T score, string studentName) : score