#include "util.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <functional>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Day11 {

using namespace std;

using Floors = array<vector<string>, 4>;

class State {
private:
  Floors floors;
  size_t elevator;

  State() = delete;

  State move_elevator(const bool up, vector<string> &items) const {
    const size_t size = floors.size();
    if (up) {
      assert(elevator < (size - 1));
    } else {
      assert(elevator > 0);
    }

    vector<string> floor = floors[elevator];
    for (const string &item : items) {
      assert(find(floor.begin(), floor.end(), item) != floor.end());
    }

    Floors new_floors;
    const size_t new_elevator = up ? (elevator + 1) : (elevator - 1);
    for (size_t i = 0; i < size; i++) {
      new_floors[i] = floors[i];
      if (i == new_elevator) {
        util::add_all(new_floors[i], items);
      } else {
        util::remove_all(new_floors[i], items);
      }
    }

    return State(new_floors, new_elevator);
  }

public:
  State(const Floors &floors, const size_t elevator)
      : floors(floors), elevator(elevator) {
    assert(elevator < floors.size());
  };

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

  vector<State> adjacent() const {
    vector<State> result;

    const vector<string> floor = floors[elevator];
    const size_t items_on_floor = floor.size();
    const size_t max_flag = pow(2, items_on_floor);
    for (size_t i = 1; i <= max_flag; i++) {
      vector<string> moved;
      for (size_t j = 0; j < items_on_floor; j++) {
        if (i && (1 << j) != 0) {
          moved.push_back(floor[j]);
        }
      }

      if (elevator != 0) {
        result.push_back(move_elevator(false, moved));
      }
      if (elevator != floor.size() - 1) {
        result.push_back(move_elevator(true, moved));
      }
    }

    return result;
  }

  bool operator==(const State &other) const {
    return floors == other.floors && elevator == other.elevator;
  }

  size_t hash() const {
    size_t result = 17;
    std::function<size_t(const vector<string> &)> floors_hash =
        [](const vector<string> &floor) {
          std::function<size_t(const string &)> vec_hash = std::hash<string>();
          return util::hash_code(floor, vec_hash);
        };
    result = 31 * util::hash_code(floors, floors_hash);
    result = 31 * result + std::hash<size_t>()(elevator);
    return result;
  }
};

struct StateHash {
  size_t operator()(const State &state) const { return state.hash(); }
};

vector<State> generate_valid_states(const State &state) {
  vector<State> adjacent = state.adjacent();
  vector<State> result;
  for (const State &state : adjacent) {
    if (state.is_valid()) {
      result.push_back(state);
    }
  }
  return result;
}

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

int solve_pt1_example() {
  Floors initial_floors{{
      {"HM", "LM"},
      {"HG"},
      {"LG"},
      {},
  }};
  State initial(initial_floors, 0);

  Floors target_floors{{
      {},
      {},
      {},
      {"HG", "HM", "LG", "LM"},
  }};
  State target(target_floors, 3);

  return solve(initial, target);
}

} // namespace Day11
