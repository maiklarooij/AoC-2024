/* https://adventofcode.com/2024/day/5#part1 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
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

int main() {

    ifstream f("input.txt");

    if (!f.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    map<int, vector<int>> rules;
    vector<vector<int>> updates;
    string s;
    bool parse_rules = true;
    while (getline(f, s)) {

        if (s.length() == 0) {
            parse_rules = false;
            continue;
        }

        /* Parse rules into {4: [2, 3, 5]}*/
        if (parse_rules) {
            vector<int> splitted_string = split(s, "|");

            vector<int> int_list;
            if (rules.contains(splitted_string[0])) {
                int_list = rules[splitted_string[0]];
            }

            int_list.push_back(splitted_string[1]);
            rules[splitted_string[0]] = int_list;
        }
        /* Parse updates into list of updates (list) */
        else {
            vector<int> splitted_string = split(s, ",");
            updates.push_back(splitted_string);
        }
    }

    int answer = 0;

    /* For every update */
    for (auto it = updates.begin(); it != updates.end(); ++it) {

        vector<int> update_list = *it;
        set<int> seen_update_ints;
        bool valid = true;

        /* For every page number in update */
        for (auto it2 = update_list.begin(); it2 != update_list.end(); ++it2) {
            int update_int = *it2;

            /* For every rule corresponding to page number */
            for (auto it3 = rules[update_int].begin(); it3 != rules[update_int].end(); ++it3) {
                int not_before = *it3;

                /* Update is invalid if there is a rule that a value needs to come after this value,
                 * but it is before!
                 */
                if (seen_update_ints.contains(not_before)) {
                    valid = false;
                    break;
                }
                seen_update_ints.insert(update_int);
            }

            if (!valid) {
                break;
            }
        }
        
        /* Sum the middle page numbers of valid updates */
        if (valid) {
            answer += update_list[update_list.size() / 2];
        }

    }

    cout << "Answer: " << answer << endl;
}
    