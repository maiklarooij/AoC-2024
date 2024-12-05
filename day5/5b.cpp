/* https://adventofcode.com/2024/day/5#part2 */

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

int get_index(vector<int> l, int i) {

    for (size_t index = 0; index < l.size(); ++index) {
        if (l[index] == i) {
            return index;
        }
    }

    return -1;   
}

bool is_before(vector<int> l, int index, int i) {

    for (size_t ix = 0; ix < index; ++ix) {
        if (l[ix] == i) {
            return true;
        }
    }

    return false;
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
        for (int index = 0; index < update_list.size(); ) {
            int update_int = update_list[index];

            bool reordered = false;
            /* For every rule corresponding to page number */
            for (auto it3 = rules[update_int].begin(); it3 != rules[update_int].end(); ++it3) {
                int not_before = *it3;

                /* Update is invalid if there is a rule that a value needs to come after this value,
                 * but it is before!
                 */
                if (is_before(update_list, index, not_before)) {
                    valid = false;
                    int index_of_invalid = get_index(update_list, not_before);

                    /* Swap the offending value to the next index, so it is conform the rule */
                    update_list.insert(update_list.begin() + index+1, not_before);
                    update_list.erase(update_list.begin() + index_of_invalid);
                    --index;
                    reordered = true;
                }
            }
            ++index;
        }
        
        /* Sum the middle page numbers of updates that were reordered */
        if (!valid) {
            answer += update_list[update_list.size() / 2];
        }
    }

    cout << "Answer: " << answer << endl;
}
    