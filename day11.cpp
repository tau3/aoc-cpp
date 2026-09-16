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

  bool contains(const string &item) const {
    return find(floor.begin(), floor.end(), item) != floor.end();
  }

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
    return true;
  }

  size_t size() const { return floor.size(); }

  const string &operator[](size_t index) const { return floor[index]; }

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
    if (up) {
      assert(elevator < (size - 1));
    } else {
      assert(elevator > 0);
    }

    // TODO contains all
    Floor floor = floors[elevator];
    for (const string &item : items) {
      assert(floor.contains(item));
    }

    Floors new_floors;
    const size_t new_elevator = up ? (elevator + 1) : (elevator - 1);
    for (size_t i = 0; i < size; i++) {
      new_floors[i] = floors[i];
      if (i == new_elevator) {
        new_floors[i].add_all(items);
      } else {
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

  void display() const {
    for (int i = floors.size() - 1; i >= 0; i--) {
      cout << "F" << (i + 1) << " ";
      if (elevator == i) {
        cout << "E ";
      }

      cout << floors[i].to_string();
      cout << endl;
    }
    cout << endl;
  }

  bool is_valid() const {
    for (const Floor &floor : floors) {
      if (!floor.is_valid()) {
        return false;
      }
    }
    return true;
  };

  vector<State> adjacent() const {
    vector<State> result;

    vector<vector<string>> perms;
    const Floor floor = floors[elevator];
    for (size_t i = 0; i < floor.size(); i++) {
      perms.push_back({floor[i]});
      for (size_t j = i + 1; j < floor.size(); j++) {
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
    return floors == other.floors && elevator == other.elevator;
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

      //   if (visited.size() % 100000 == 0) {
      //     cout << visited.size() << endl;
      //   }
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

} // namespace Day11
