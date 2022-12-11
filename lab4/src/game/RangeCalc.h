/**
 * @file RangeCalc.h
 * Utility module for calculating ranges and paths in a level.
 */

#ifndef OOP_RANGECALC_H
#define OOP_RANGECALC_H

#include <iostream>
#include <queue>
#include <vector>

#include "Level.h"
#include "enum/Direction.h"

using namespace std;

namespace DungeonGame {

    /**
     * Range calculator based on cell map
     *
     * provides algorithms for range calculation and path-tracing.
     */
    class RangeCalc {
        vector<vector<Cell>>& field;
        vector<vector<uint>> range_table;
        queue<pair<uint, uint>> marked;

    public:
        explicit RangeCalc(vector<vector<Cell>>& map): field(map) {
            range_table.reserve(field.size());
            for (uint i = 0; i < field.size(); i++)
                range_table.emplace_back(field[0].size(), UINT32_MAX);
        }

        int range(pair<int, int> pos1,
                  pair<int, int> pos2,
                  bool directed = false,
                  Direction facing = Direction::DOWN);

        list<Direction> path(pair<int, int> pos1,
                             pair<int, int> pos2,
                             uint min_range,
                             uint max_range);

    private:
        void _resetRangeTable();
        bool _canGoToCell(int x, int y);
    };

}

#endif //OOP_RANGECALC_H
