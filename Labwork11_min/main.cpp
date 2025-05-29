#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
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
};

class Test {
    string subject, difficulty;
    TestItem* items[10];
public:
    Test(string s = "No subject", string d = "No difficulty") : subject(s), difficulty(d) { for (int i = 0; i < 10; i++) items[i] = nullptr; }
    ~Test() { for (int i = 0; i < 10; i++) delete items[i]; }
    void setItem(TestItem* item, int i) { if (i >= 0 && i < 10) { delete items[i]; items[i] = item; } }
    void addQuestion(string t, string a, int p, int i) { try { setItem(new Question(t, a, p), i); } catch (const invalid_argument& e) { cout << "Error: " << e.what() << endl; } }
    void addMCQ(string t, vector<string> opts, int ci, int p, int i) { try { setItem(new MultipleChoiceQuestion(t, opts, ci, p), i); } catch (const exception& e) { cout << "Error: " << e.what() << endl; } }
    void saveToFile(const string& filename) {
        ofstream file(filename);
        file << subject << "\n" << difficulty << "\n";
        for (int i = 0; i < 10; i++) (items[i] ? items[i]->saveToFile(file) : file << "E\n");
        file.close();
    }
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        getline(file, subject);
        getline(file, difficulty);
        for (int i = 0; i < 10; i++) {
            string type;
            getline(file, type);
            if (type == "Q") setItem(new Question("", "", 0), i), items[i]->loadFromFile(file);
            else if (type == "MCQ") setItem(new MultipleChoiceQuestion("", {}, 0, 0), i), items[i]->loadFromFile(file);
            else setItem(nullptr, i);
        }
        file.close();
    }
};

int main() {
    Test test("Math", "Hard");
    test.addQuestion("What is 2+2?", "4", 10, 0);
    test.addMCQ("What is 2+2?", { "A) 1", "B) 2", "C) 3", "D) 4" }, 3, 15, 1);
    test.saveToFile("test.txt");
    Test test2;
    test2.loadFromFile("test.txt");
    return 0;
}
