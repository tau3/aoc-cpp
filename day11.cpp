#include "util.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

// #define DEBUG 1

namespace Day11 {

using namespace std;

class Floor {
private:
  vector<string> floor;

public:
  Floor(const initializer_list<string> &init) : floor(init) {
    sort(floor.begin(), floor.end());
  };

  Floor() {};

#ifdef DEBUG
  bool contains(const string &item) const {
    return find(floor.begin(), floor.end(), item) != floor.end();
  }
#endif

  void add_all(const vector<string> &items) {
    util::add_all(floor, items);
    sort(floor.begin(), floor.end());
  }

  void remove_all(const vector<string> &items) {
    util::remove_all(floor, items);
  }

  string to_string() const {
    string result = "";
    for (const string &item : floor) {
      result += item;
      result += ' ';
    }
    return result;
  }

  bool is_valid() const {
    for (const string &item : floor) {
      if (item[1] == 'M') {
        bool has_own_generator = false;
        bool has_another_generator = false;
        for (size_t j = 0; j < floor.size(); j++) {
          const string &current = floor[j];
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
    return true;
  }

  size_t size() const { return floor.size(); }

  const string &operator[](const size_t index) const { return floor[index]; }

  bool operator==(const Floor &other) const { return floor == other.floor; }

  size_t hash_code() const {
    const function<size_t(const string &)> h = hash<string>();
    return util::hash_code(floor, h);
  }
};

using Floors = array<Floor, 4>;

class State {
private:
  Floors floors;
  size_t elevator;

  State() = delete;

  State move_elevator(const bool up, const vector<string> &items) const {
    const size_t size = floors.size();

#ifdef DEBUG
    if (up) {
      assert(elevator < (size - 1));
    } else {
      assert(elevator > 0);
    }

    const Floor &floor = floors[elevator];
    for (const string &item : items) {
      assert(floor.contains(item));
    }
#endif

    // TODO avoid constructor?
    Floors new_floors;
    const size_t new_elevator = up ? (elevator + 1) : (elevator - 1);
    for (size_t i = 0; i < size; i++) {
      new_floors[i] = floors[i];
      if (i == new_elevator) {
        new_floors[i].add_all(items);
      } else if (i == elevator) {
        new_floors[i].remove_all(items);
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
    for (const auto &floor : floors) {
      if (!floor.is_valid()) {
        return false;
      }
    }
    return true;
  };

  vector<State> adjacent() const {
    vector<State> result;

    vector<vector<string>> perms;
    const Floor &floor = floors[elevator];
    const size_t size = floor.size();
    for (size_t i = 0; i < size; i++) {
      perms.push_back({floor[i]});
      for (size_t j = i + 1; j < size; j++) {
        perms.push_back({floor[i], floor[j]});
      }
    }

    for (const vector<string> &perm : perms) {
      if (elevator != 0) {
        result.push_back(move_elevator(false, perm));
      }
      if (elevator != floors.size() - 1) {
        result.push_back(move_elevator(true, perm));
      }
    }

    return result;
  }

  bool operator==(const State &other) const {
    return elevator == other.elevator && floors == other.floors;
  }

  size_t hash() const {
    size_t result = 17;
    std::function<size_t(const Floor &)> floors_hash = [](const Floor &floor) {
      return floor.hash_code();
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
  vector<State> result = state.adjacent();
  result.erase(
      std::remove_if(result.begin(), result.end(),
                     [](const State &current) { return !current.is_valid(); }),
      result.end());
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

// TODO "target" function?
int solve_day11_pt1() {
  State initial({{{"PG", "TG", "TM", "pG", "RG", "RM", "CG", "CM"},
                  {"PM", "pM"},
                  {},
                  {}}},
                0);
  State target({{{},
                 {},
                 {},
                 {"PG", "TG", "TM", "pG", "RG", "RM", "CG", "CM", "PM", "pM"}}},
               3);
  return solve(initial, target);
}

int solve_day11_pt2() {
  State initial({{{"PG", "TG", "TM", "pG", "RG", "RM", "CG", "CM", "EG", "EM",
                   "DG", "DM"},
                  {"PM", "pM"},
                  {},
                  {}}},
                0);
  State target({{{},
                 {},
                 {},
                 {"PG", "TG", "TM", "pG", "RG", "RM", "CG", "CM", "PM", "pM",
                  "EG", "EM", "DG", "DM"}}},
               3);
  return solve(initial, target);
}

} // namespace Day11
