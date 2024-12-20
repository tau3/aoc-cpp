#include <cstddef>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

using Point = pair<size_t, size_t>;

size_t distance(const Point &lhs, const Point &rhs) {
  const size_t h =
      lhs.first > rhs.first ? lhs.first - rhs.first : rhs.first - lhs.first;
  const size_t w = lhs.second > rhs.second ? lhs.second - rhs.second
                                           : rhs.second - lhs.second;
  return h + w;
};

bool is_valid_antinode(const Point &antinode, const Point &lhs,
                       const Point &rhs) {
  const size_t lhs_distance = distance(antinode, lhs);
  const size_t rhs_distnace = distance(antinode, rhs);
  return (rhs_distnace / 2 == lhs_distance) ||
         (lhs_distance / 2 == rhs_distnace);
}

vector<Point> find_antinodes(const Point &lhs, const Point &rhs,
                        const Point &bound) {
  vector<Point> result;
  Point candidate = {lhs.first, rhs.second};
  if (is_valid_antinode(candidate, lhs, rhs)) {
    result.push_back(candidate);
  }
  candidate = {lhs.second, rhs.first};
  if (is_valid_antinode(candidate, lhs, rhs)) {
    result.push_back(candidate);
  }
  return result;
}

int solve(const vector<string> &input) {
  const size_t w = input[0].size();
  const size_t h = input.size();

  unordered_map<char, vector<Point>> antennas;
  for (size_t r = 0; r < h; ++r) {
    for (size_t c = 0; c < w; ++c) {
      const char frequency = input[r][c];
      if (frequency == '.') {
        continue;
      }

      if (auto entry = antennas.find(frequency); entry != antennas.end()) {
        vector<Point> points = entry->second;
        points.push_back({r, c});
      } else {
        const vector<Point> points = {{r, c}};
        antennas[frequency] = points;
      }
    }
  }

  unordered_set<Point> result;
  const Point bound = {h, w};
  for (const auto &kv : antennas) {
    const vector<Point> points = kv.second;
    for (size_t i = 0; i < points.size(); ++i) {
      for (size_t j = i + 1; j < points.size(); ++j) {
        const Point &lhs = points[i];
        const Point &rhs = points[j];
        const vector<Point> antinodes = find_antinodes(lhs, rhs, bound);
        for (const Point &antinode : antinodes) {
          result.insert(antinode);
        }
      }
    }
  }
  return result.size();
}
