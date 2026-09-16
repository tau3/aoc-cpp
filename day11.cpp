#include <array>
#include <cstddef>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class State {
private:
  array<vector<string>, 4> floors;
  size_t elevator;

public:
  bool is_valid() const {
    for (const vector<string> &floor : floors) {
      // TODO for each
      for (size_t i = 0; i < floor.size(); i++) {
        const string item = floor[i];
        if (item[1] == 'M') {
          bool has_own_generator = false;
          bool has_another_generator = false;
          for (size_t j = 0; j < floor.size(); j++) {
            const string current = floor[j];
            if (current[1] == 'G') {
              if (current[0] == item[0]) {
                has_own_generator = true;
              } else {
                has_another_generator = true;
              }
            }
          }
          if (has_another_generator && !has_own_generator) {
            return false;
          }
        }
      }
    }
    return true;
  };

  bool operator==(const State &other) const {
    return floors == other.floors && elevator == other.elevator;
  }
};

vector<State> generate_valid_states(const State &state) {}

int solve(const State &initial, const State &target) {
  queue<pair<State, int>> q;
  unordered_set<State> visited;
  q.push({initial, 0});
  while (!q.empty()) {
    const auto [state, depth] = q.front();
    q.pop();

    if (state == target) {
      return depth;
    }
    vector<State> states = generate_valid_states(state);
    const int next = depth + 1;
    for (const State &candidate : states) {
      if (visited.add(candidate)) {
        q.push({candidate, next});
      }
    }
  }

  throw runtime_error("no solution");
};
