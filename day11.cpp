#include "util.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
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
  Floor(initializer_list<string> floor) : floor(floor) {};

  Floor() {};

  bool contains(const string &item) const {
    return find(floor.begin(), floor.end(), item) != floor.end();
  }

  void add_all(const vector<string> &items) { util::add_all(floor, items); }

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

  bool operator==(const Floor &other) const {
    return unordered_set(floor.begin(), floor.end()) ==
           unordered_set(other.floor.begin(), other.floor.end());
  }

  size_t hash_code() const {
    const unordered_set<string> distict(floor.begin(), floor.end());
    const function<size_t(const string &)> h = hash<string>();
    return util::hash_code(distict, h);
  }
};

using Floors = array<Floor, 4>;

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

  bool test_bit(const size_t num, const size_t i) const {
    return (num & (1 << i)) != 0;
  }

  int count_bits(const size_t num) const {
    // cout << endl;
    cout << num << " " << std::format("{:b}", num) << endl;
    int result = 0;
    const size_t count = sizeof(size_t) * 8;
    for (size_t i = 0; i < count; i++) {
      const size_t mask = std::size_t{1} << i;
      if ((mask & num) != 0) {
        cout << "num=" << num << " mask " << i << endl;
        result++;
      }
    };
    return result;
  }

  vector<State> adjacent() const {
    vector<State> result;

    const Floor floor = floors[elevator];
    const size_t items_on_floor = floor.size();
    const size_t max_flag = pow(2, items_on_floor) - 1;
    for (size_t i = 1; i <= max_flag; i++) {
      // cout << i << ", count=" << count_bits(i) << endl;
      if (count_bits(i) > 2) {
        continue;
      }

      vector<string> moved;
      for (size_t j = 0; j < items_on_floor; j++) {
        if (test_bit(i, j)) {
          moved.push_back(floor[j]);
        }
      }

      assert(!moved.empty() && (moved.size() <= 2));
      if (elevator != 0) {
        result.push_back(move_elevator(false, moved));
      }
      if (elevator != floors.size() - 1) {
        result.push_back(move_elevator(true, moved));
      }
    }

    cout << "adjacent from---------------" << endl;
    display();
    cout << "to" << endl;
    for (auto x : result) {
      x.display();
    }
    cout << "-------------" << endl;

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
        candidate.display();
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

void debug() {
  Floors initial_floors{{
      {},
      {},
      {"HM", "LM"},
      {"HG", "LG"},
  }};
  State initial(initial_floors, 2);
  const auto adjacent = initial.adjacent();
}

} // namespace Day11
