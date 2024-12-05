/* https://adventofcode.com/2024/day/4#part1 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {

    ifstream f("input.txt");

    if (!f.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    /* Parse input into 2D grid */
    vector<vector<char>> grid;
    string s;
    while (getline(f, s)) {

        vector<char> current_line;
        for (auto it = s.begin(); it != s.end(); ++it) {
            char current_char = *it;
            current_line.push_back(current_char);
        }
        grid.push_back(current_line);
    }

    int xmas_count = 0;

    /* Go through grid */
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            
            /* X is starting point */
            if (grid[y][x] == 'X') {
                
                /* Check all cells around 'X' */
                for (signed i = -1; i <= 1; ++i) {
                    for (signed j = -1; j <= 1; ++j) {

                        signed curr_x = x;
                        signed curr_y = y;
                        string found_string = "";

                        /* From the start, move diagonal, horizontal or vertical based on i and j */
                        for (size_t _ = 0; _ < 4; ++_) {
                            
                            /* Out of bounds */
                            if (curr_x < 0 || curr_y < 0 || curr_y >= grid.size() || curr_x >= grid[y].size()) {
                                break;
                            }

                            /* Create string */
                            found_string = found_string + grid[curr_y][curr_x];
                            curr_x += i;
                            curr_y += j;
                        }

                        /* If the word found is XMAS */
                        if (found_string == "XMAS") {
                            ++xmas_count;
                        }
                    }
                }
            }
        }
    }

    cout << "Answer: " << xmas_count << endl;
}