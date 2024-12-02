/* https://adventofcode.com/2024/day/1#part1 */

#include <iostream>
#include <fstream>
#include <list>
#include <string>
using namespace std;

/* Splits a string based on delimiter into a list of ints */
list<int> split(string s, string delim) {

    size_t pos_start = 0, pos_curr = 0;
    string s_curr;
    int i_curr;

    list<int> result;

    while ((pos_curr = s.find(delim, pos_start)) != string::npos) {
        s_curr = s.substr(pos_start, pos_curr);
        i_curr = stoi(s_curr);

        result.push_back(i_curr);

        pos_start = pos_curr + delim.length();
    }
    s_curr = s.substr(pos_start);
    i_curr = stoi(s_curr);
    result.push_back(i_curr);

    return result;
}

int main() {

    ifstream f("input.txt");

    if (!f.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    string s;
    string delimiter = " ";
    int nr_safe = 0;
    while (getline(f, s)) {

        size_t i = 0;
        int last_level = 0;

        /* Keep track of whether it is in/decreasing, and if the reports are safe */
        bool increasing = false;
        bool safe = true;

        int curr_level;

        list<int> parsed_list = split(s, delimiter);
        auto it = parsed_list.begin();
        while (it != parsed_list.end()) {

            curr_level = *it;
            cout << curr_level << endl;

            /* First value, just store it */
            if (i == 0) {
                last_level = curr_level;
            }
            /* Second value, check if valid and for decrease/increase */
            else if (i == 1) {
                
                if (abs(curr_level - last_level) > 3 || abs(curr_level - last_level) < 1) {
                    safe = false;
                    break;
                }

                if (curr_level > last_level) {
                    increasing = true;
                }
            }
            else {

                /* "Any two adjacent levels differ by at least one and at most three." */
                if (abs(curr_level - last_level) > 3 || abs(curr_level - last_level) < 1) {
                    safe = false;
                    break;
                }

                /* "The levels are either all increasing or all decreasing." */
                if ((increasing && (last_level - curr_level) >= 0)) {
                    safe = false;
                    break;
                }
                else if (!increasing && (curr_level - last_level) >= 0) {
                    safe = false;
                    break;
                }
            }

            ++i;
            ++it;
            last_level = curr_level;
        }
        
        if (safe) {
            ++nr_safe;
        }

    }

    cout << "Answer: " << nr_safe << endl;

}
