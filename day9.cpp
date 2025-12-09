#include "day9.hpp"
#include "util.hpp"
#include <cstddef>
#include <string>
#include <vector>

namespace Day9 {

using Point = util::Point<long>;

long solve_day9_pt1(const vector<string> &input) {
  vector<Point> points;
  for (const string &line : input) {
    const vector<string> tokens = util::split(line, ",");
    Point point(stol(tokens[0]), stol(tokens[1]));
    points.push_back(point);
  }

  long result = 0;
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = i + 1; j < points.size(); j++) {
      const Point &left = points[i];
      const Point &right = points[j];
      if ((left.col == right.col) || (left.row == right.row)) {
        continue;
      }
      long area = abs(left.col - right.col + 1) * abs(left.row - right.row + 1);
      if (area > result) {
        cout << left.col << "," << left.row << " " << right.col << ","
             << right.row << endl;
        result = area;
      }
    }
  }
  return result;
}

} // namespace Day9
