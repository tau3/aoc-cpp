#include <cstddef>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

using Point = pair<size_t, size_t>;

vector<Point> antinodes(const Point &lhs, const Point &rhs,
                        const Point &bound) {
  vector<Point> result = {{lhs.first, rhs.second}, {lhs.second, lhs.first} };
  
  
}

void solve(const vector<string> &input) {
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

  for(const auto& kv : antennas){
    const vector<Point> points = kv.second;
    for(size_t i =0; i< points.size(); ++i){
      for(size_t j=i+1; j< points.size(); ++j){
	const Point& lhs = points[i];
	const Point& rhs = points[j];
      }
    }
  }
}
