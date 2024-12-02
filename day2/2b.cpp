/* https://adventofcode.com/2024/day/1#part1 */

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
using namespace std;

/* Splits a string based on delimiter into a list of ints */
vector<int> split(string s, string delim) {

    size_t pos_start = 0, pos_curr = 0;
    string s_curr;
    int i_curr;

    vector<int> result;

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

bool check_validity(vector<int> sequence) {

    size_t i = 0;
    int last_level = 0;
    bool increasing = false;
    bool safe = true;

    int curr_level;

    auto it = sequence.begin();
    while (it != sequence.end()) {

        curr_level = *it;

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
        return true;
    }
    return false;
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

        vector<int> parsed_list = split(s, delimiter);
        
        /* Normal validity */
        if (check_validity(parsed_list)) {
            ++nr_safe;
        }
        /* Check validity if one of the elements is removed */
        else {
            for (int i = 0; i < parsed_list.size(); i++) {
                
                /* Remove one element */
                int removed_value = parsed_list[i];
                parsed_list.erase(parsed_list.begin() + i);

                /* Check validity of remaining list */
                if (check_validity(parsed_list)) {
                    ++nr_safe;
                    break;
                }

                /* Plug the value back in */
                parsed_list.insert(parsed_list.begin() + i, removed_value);
            }
        }
    }

    cout << "Answer: " << nr_safe << endl;

}
