#ifndef INCLUDE_DAY_19_H
#define INCLUDE_DAY_19_H

#include <string>
#include <vector>

namespace Day19 {

using namespace std;

using Replacements = vector<pair<string, string>>;
size_t solve(const Replacements &replacements, const string &line);
size_t solve_day_19_pt1(const vector<string> &input);

} // namespace Day19

#endif
