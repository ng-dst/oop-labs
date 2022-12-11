#include "RangeCalc.h"

namespace DungeonGame {

    void RangeCalc::_resetRangeTable() {
        for (auto& i: range_table)
            fill(i.begin(), i.end(), INT32_MAX);
        while (!marked.empty()) marked.pop();
    }

    bool RangeCalc::_canGoToCell(int x, int y) {
        return x >= 0 && x < field.size() && y >= 0 && y < field[0].size() &&
               range_table[x][y] == INT32_MAX && (field[x][y] == FLOOR || field[x][y] == DOOR_OPEN || field[x][y] == Cell::ESSENCE);
    }

    int RangeCalc::range(pair<int, int> pos1, pair<int, int> pos2, bool directed, Direction facing) {
        uint startx = pos1.first, starty = pos1.second;
        uint endx = pos2.first, endy = pos2.second;
        _resetRangeTable();
        marked.push(pos1);
        range_table[startx][starty] = 0;
        while (range_table[endx][endy] == INT32_MAX && !marked.empty()) {
            pair<int, int> cell = marked.front();
            marked.pop();
            uint cur_range = range_table[cell.first][cell.second];
            // going UP
            if (_canGoToCell(cell.first-1, cell.second) && (!directed || facing != DOWN))
            {
                range_table[cell.first-1][cell.second] = cur_range + 1;
                marked.push(make_pair(cell.first-1, cell.second));
            }
            // going DOWN
            if (_canGoToCell(cell.first+1, cell.second) && (!directed || facing != UP))
            {
                range_table[cell.first+1][cell.second] = cur_range + 1;
                marked.push(make_pair(cell.first+1, cell.second));
            }
            // going LEFT
            if (_canGoToCell(cell.first, cell.second-1) && (!directed || facing != RIGHT))
            {
                range_table[cell.first][cell.second-1] = cur_range + 1;
                marked.push(make_pair(cell.first, cell.second-1));
            }
            // going RIGHT
            if (_canGoToCell(cell.first, cell.second+1) && (!directed || facing != LEFT))
            {
                range_table[cell.first][cell.second+1] = cur_range + 1;
                marked.push(make_pair(cell.first, cell.second+1));
            }
        }
        if (range_table[endx][endy] == INT32_MAX) return -1;
        return range_table[endx][endy];
    }

    list<Direction> RangeCalc::path(pair<int, int> pos1, pair<int, int> pos2,
                                    uint min_range, uint max_range) {
        int r = range(pos1, pos2);
        if (r < min_range || r > max_range) return list<Direction>();
        int x = pos2.first, y = pos2.second;
        list<Direction> list_path;

        // assuming there definitely exists a path
        while (x != pos1.first || y != pos1.second) {
            uint cur_range = range_table[x][y];
            if (x > 0 && range_table[x-1][y] < cur_range) {
                x -= 1;
                list_path.push_front(DOWN);
            }
            else if (x < field.size() - 1 && range_table[x+1][y] < cur_range) {
                x += 1;
                list_path.push_front(UP);
            }
            else if (y > 0 && range_table[x][y-1] < cur_range) {
                y -= 1;
                list_path.push_front(RIGHT);
            }
            else if (y < field[0].size() - 1 && range_table[x][y+1] < cur_range) {
                y += 1;
                list_path.push_front(LEFT);
            }
        }
        return list_path;
    }

}