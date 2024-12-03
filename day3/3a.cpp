/* https://adventofcode.com/2024/day/3#part1 */

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <regex>
using namespace std;

int main() {

    ifstream f("input.txt");

    if (!f.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    string s;
    string memory;
    while (getline(f, s)) {
        memory = memory + s;
    }

    int answer = 0;

    /* Regex to extract all 'mul(*,*)' parts */
    regex pattern ("mul\\((\\d*),(\\d*\\))");
    for (auto it = sregex_iterator(memory.begin(), memory.end(), pattern); it != sregex_iterator(); ++it) {
        smatch match = *it;
        
        int n1 = stoi(match[1].str());
        int n2 = stoi(match[2].str());

        answer += (n1 * n2);
    }

    cout << "Answer: " << answer << endl;

    return 0;
}