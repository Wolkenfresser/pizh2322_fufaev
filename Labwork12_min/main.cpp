#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <algorithm>
using namespace std;

class TestItem {
protected:
    string text;
public:
    TestItem(string t = "No text") : text(t) {}
    virtual ~TestItem() {}
    virtual void display() = 0;
    virtual int calculateScore() = 0;
    virtual void saveToFile(ofstream& file) = 0;
    virtual void loadFromFile(ifstream& file) = 0;
    virtual int getPoints() const = 0;
    string getText() { return text; }
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
    void saveToFile(ofstream& file) override { file << "Q\n" << text << "\n" << answer << "\n" << points << "\n"; }
    void loadFromFile(ifstream& file) override {
        getline(file, text);
        getline(file, answer);
        file >> points;
        file.ignore();
    }
    int getPoints() const override { return points; }
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
    void saveToFile(ofstream& file) override {
        file << "MCQ\n" << text << "\n" << options.size() << "\n";
        for (const auto& opt : options) file << opt << "\n";
        file << correctIndex << "\n" << points << "\n";
    }
    void loadFromFile(ifstream& file) override {
        getline(file, text);
        int n;
        file >> n;
        file.ignore();
        options.resize(n);
        for (int i = 0; i < n; i++) getline(file, options[i]);
        file >> correctIndex >> points;
        file.ignore();
    }
    int getPoints() const override { return points; }
};

class Test {
    string subject, difficulty;
    vector<TestItem*> items;
public:
    Test(string s = "No subject", string d = "No difficulty") : subject(s), difficulty(d) { items.resize(10, nullptr); }
    ~Test() { for (auto item : items) delete item; }
    void setItem(TestItem* item, size_t i) { if (i < items.size()) { delete items[i]; items[i] = item; } }
    void addQuestion(string t, string a, int p, size_t i) { try { setItem(new Question(t, a, p), i); } catch (const invalid_argument& e) { cout << "Error: " << e.what() << endl; } }
    void addMCQ(string t, vector<string> opts, int ci, int p, size_t i) { try { setItem(new MultipleChoiceQuestion(t, opts, ci, p), i); } catch (const exception& e) { cout << "Error: " << e.what() << endl; } }
    void sortByPoints() { sort(items.begin(), items.end(), [](TestItem* a, TestItem* b) { return a && b ? a->getPoints() > b->getPoints() : (a ? true : false); }); }
    TestItem* findByText(const string& t) { auto it = find_if(items.begin(), items.end(), [&t](TestItem* item) { return item && item->getText() == t; }); return it != items.end() ? *it : nullptr; }
};

int main() {
    Test test("Math", "Hard");
    test.addQuestion("What is 2+2?", "4", 10, 0);
    test.addMCQ("What is 3+3?", { "A) 1", "B) 2", "C) 3", "D) 4" }, 3, 15, 1);
    test.addQuestion("What is 5+5?", "10", 5, 2);
    test.sortByPoints();
    auto found = test.findByText("What is 2+2?");
    if (found) found->display();
    return 0;
}
