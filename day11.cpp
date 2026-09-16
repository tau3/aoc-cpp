#include <array>
#include <cstddef>
#include <functional>
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
      for (const string &item : floor) {
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

  size_t hash() const {
    size_t result = 17;
    result = 31 * std::hash<array<vector<string>, 4>>()(floors);
    result = 31 * result + std::hash<size_t>()(elevator);
    return result;
  }
};

struct StateHash {
  size_t operator()(const State &state) const { return state.hash(); }
};

vector<State> generate_valid_states(const State &state) {}

int solve(const State &initial, const State &target) {
  queue<pair<State, int>> q;
  unordered_set<State, StateHash> visited;
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
      if (visited.insert(candidate).second) {
        q.push({candidate, next});
      }
    }
  }

  throw runtime_error("no solution");
};
