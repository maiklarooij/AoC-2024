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
    for (signed y = 0; y < grid.size(); ++y) {
        for (signed x = 0; x < grid[y].size(); ++x) {
            
            /* A is starting point */
            if (grid[y][x] == 'A') {
                
                /* Out of bounds */
                if ((y + 1) >= grid.size() || (y - 1) < 0 || (x + 1) >= grid[y].size() || (x - 1) < 0) {
                    continue;
                }
                else {
                    
                    /* Check for X-MAS */
                    if (((grid[y + 1][x + 1] == 'M' && grid[y - 1][x - 1] == 'S') || (grid[y + 1][x + 1] == 'S' && grid[y - 1][x - 1] == 'M')) &&
                        ((grid[y - 1][x + 1] == 'M' && grid[y + 1][x - 1] == 'S') || (grid[y - 1][x + 1] == 'S' && grid[y + 1][x - 1] == 'M'))
                        ) {
                            ++xmas_count;
                    }
                }
            }
        }
    }

    cout << "Answer: " << xmas_count << endl;
}