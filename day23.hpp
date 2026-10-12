#ifndef INCLUDE_DAY_23_H
#define INCLUDE_DAY_23_H

#include "day12.hpp"
#include <string>
#include <vector>

namespace Day23 {

using namespace std;

void tgl(const Day12::Machine &machine, vector<string> &program, size_t &rip);

int solve(const vector<string> &input);

} // namespace Day23

#endif
