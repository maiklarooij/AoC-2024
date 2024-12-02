/* https://adventofcode.com/2024/day/1#part1 */

#include <iostream>
#include <fstream>
#include <list>
#include <string>
using namespace std;

int main() {

    ifstream f("input.txt");

    if (!f.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    /* Parse puzzle input into two lists */
    list<int> l1;
    list<int> l2;
    string s;
    string delimiter = "   ";
    while (getline(f, s)) {

        string n1 = s.substr(0, s.find(delimiter));
        string n2 = s.substr(s.find(delimiter) + delimiter.length());
        
        l1.push_back(stoi(n1));
        l2.push_back(stoi(n2));

    }

    /* Sort both lists from small to big */
    l1.sort();
    l2.sort();

    /* Iterate through the two lists, calculating the distance and adding to answer */
    int answer = 0;
    auto it1 = l1.begin();
    auto it2 = l2.begin();
    while (it1 != l1.end() && it2 != l2.end()) {
        cout << *it1 << " " << *it2 << endl;

        answer = answer + abs(*it1 - *it2);

        ++it1;
        ++it2;
    }

    cout << "Answer: " << answer << endl;
}
