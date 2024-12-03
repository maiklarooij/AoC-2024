/* https://adventofcode.com/2024/day/3#part2 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
using namespace std;

int find_closest(int n, vector<int> l) {

    int last = 0;
    for (auto it = l.begin(); it != l.end(); ++it) {
        int current = *it;

        if (current > n) {
            break;
        }

        last = current;
    }

    return last;
}

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

    /* Collect all indexes of do() */
    vector<int> dos;
    regex pattern_do ("do\\(\\)");
    for (auto it = sregex_iterator(memory.begin(), memory.end(), pattern_do); it != sregex_iterator(); ++it) {
        smatch match = *it;
        dos.push_back(match.position());
    }

    /* Collect all indexes of don't() */
    vector<int> donts;
    regex pattern_dont ("don't\\(\\)");
    for (auto it = sregex_iterator(memory.begin(), memory.end(), pattern_dont); it != sregex_iterator(); ++it) {
        smatch match = *it;
        donts.push_back(match.position());
    }

    int answer = 0;

    /* Regex to extract all 'mul(*,*)' parts */
    regex pattern ("mul\\((\\d*),(\\d*\\))");
    for (auto it = sregex_iterator(memory.begin(), memory.end(), pattern); it != sregex_iterator(); ++it) {
        smatch match = *it;

        int closest_do = find_closest(match.position(), dos);
        int closest_dont = find_closest(match.position(), donts);

        /* Only add if there is a do() closer than a don't() */
        if ((closest_do > closest_dont) || closest_dont == 0) {
            int n1 = stoi(match[1].str());
            int n2 = stoi(match[2].str());
            answer += (n1 * n2);
        }
    }

    cout << "Answer: " << answer << endl;

    return 0;
}
