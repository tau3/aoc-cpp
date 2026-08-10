#ifndef INCLUDE_DAY_17_H
#define INCLUDE_DAY_17_H

#include <unordered_map>
#include <vector>

namespace Day17 {

using namespace std;

int how_many_ways(const vector<int> &containers,
                  const unordered_map<int, int> &cache, const int limit);
} // namespace Day17

#endif
