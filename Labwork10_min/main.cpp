#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <thread>
using namespace std;

class TestItem {
protected:
    string text;
public:
    TestItem(string t = "No text") : text(t) {}
    virtual ~TestItem() {}
    virtual void display() = 0;
    virtual int calculateScore() = 0;
};

class Question : public TestItem {
    string answer;
    int points;
public:
    Question(string t, string a, int p) : TestItem(t), answer(a), points(p) { if (p < 0) throw invalid_argument("Negative points"); }
    void display() override { cout << "Q: " << text << ", Ans: " << answer << ", Pts: " << points << endl; }
    int calculateScore() override {
        string userAns;
        cout << "Answer '" << text << "': ";
        getline(cin, userAns);
        return userAns == answer ? points : 0;
    }
};

class MultipleChoiceQuestion : public TestItem {
    vector<string> options;
    int correctIndex, points;
public:
    MultipleChoiceQuestion(string t, vector<string> opts, int ci, int p) : TestItem(t), options(opts), correctIndex(ci), points(p) {
        if (p < 0) throw invalid_argument("Negative points");
        if (ci < 0 || ci >= (int)opts.size()) throw out_of_range("Invalid index");
    }
    void display() override {
        cout << "MCQ: " << text << ", Options: ";
        for (size_t i = 0; i < options.size(); i++) cout << options[i] << (i == correctIndex ? "*" : "") << " ";
        cout << ", Pts: " << points << endl;
    }
    int calculateScore() override {
        display();
        int choice;
        cout << "Choose (0-based): ";
        cin >> choice;
        cin.ignore();
        if (choice < 0 || choice >= (int)options.size()) throw out_of_range("Invalid choice");
        return choice == correctIndex ? points : 0;
    }
};

template <typename T>
class Result {
    T score;
    string name;
public:
    Result(T s, string n) : score(s), name(n) {}
    friend ostream& operator<<(ostream& os, const Result& r) { return os << r.name << ": " << r.score; }
};

class Test {
    string subject, difficulty;
    TestItem* items[10];
public:
    Test(string s, string d) : subject(s), difficulty(d) { for (int i = 0; i < 10; i++) items[i] = nullptr; }
    ~Test() { for (int i = 0; i < 10; i++) delete items[i]; }
    void setItem(TestItem* item, int i) { if (i >= 0 && i < 10) { delete items[i]; items[i] = item; } }
    void addQuestion(string t, string a, int p, int i) { try { setItem(new Question(t, a, p), i); } catch (const invalid_argument& e) { cout << "Error: " << e.what() << endl; } }
    void addMCQ(string t, vector<string> opts, int ci, int p, int i) { try { setItem(new MultipleChoiceQuestion(t, opts, ci, p), i); } catch (const exception& e) { cout << "Error: " << e.what() << endl; } }
    int calculateTotalScore() {
        int total = 0;
        for (int i = 0; i < 10; i++) if (items[i]) try { total += items[i]->calculateScore(); } catch (const out_of_range& e) { cout << "Error: " << e.what() << endl; }
        return total;
    }
    void processAnswers() {
        vector<thread> threads;
        for (int i = 0; i < 10; i++) if (items[i]) threads.emplace_back([this, i]() { items[i]->calculateScore(); });
        for (auto& t : threads) t.join();
    }
};

int main() {
    Test test("Math", "Hard");
    test.addQuestion("What is 2+2?", "4", 10, 0);
    test.addMCQ("What is 2+2?", { "A) 1", "B) 2", "C) 3", "D) 4" }, 3, 15, 1);
    test.processAnswers();
    Result<int> result(test.calculateTotalScore(), "John");
    cout << result << endl;
    return 0;
}
