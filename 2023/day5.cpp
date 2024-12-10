#include <algorithm>
#include <array>
#include <functional>
#include <string>
#include <vector>

#include "util.hpp"

using namespace std;

class Probe {
public:
  explicit Probe(const vector<string> &raw) {
    vector<array<int, 3>> intervals;
    for (const string &line : raw) {
      const vector<string> tokens = split(line, " ");
      int left_key = stoi(tokens[0]);
      int left_value = stoi(tokens[1]);
      int width = stoi(tokens[2]);
      array<int, 3> entry = {left_key, left_value, width};
      intervals.push_back(entry);
    }

    this->intervals = intervals;
  }

  int get(int val) const {
    for (const auto &interval : intervals) {
      int left_key = interval[0];
      int left_value = interval[1];
      int width = interval[2];
      int right_key = left_key + width - 1;

      if (left_key >= val && val <= right_key) {
        int result = val - left_key + left_value;
        return result;
      }
    }
    return val;
  }

private:
  vector<array<int, 3>> intervals;
};

int solve(const vector<int> &seeds, const vector<Probe> &probes) {
  vector<int> vals;
  for (int seed : seeds) {
    int val = seed;
    for (const Probe &probe : probes) {
      val = probe.get(val);
    }
    vals.push_back(val);
  }
  return *min_element(vals.begin(), vals.end());
}
