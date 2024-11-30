#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <format>
using namespace std;

int main() {

    ifstream f("input.txt");

    if (!f.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    string s;
    string digits;
    int sum = 0;
    int curr_num = 0;
    while (getline(f, s)) {
        
        list<char> l;

        for (int i = 0; i < s.size(); i++) {
            if (isdigit(s[i])) {
                l.push_back(s[i]);
            }
        }

        cout << "l.front() = " << l.front() << endl;
        cout << "l.back() = " << l.back() << endl;
        digits = format("{0}{1}", l.front(), l.back());
        cout << digits << endl;
        curr_num = stoi(digits);
        sum += curr_num;
    }

    cout << sum << endl;

    f.close();
    return 0;
}