#include "day9.hpp"
#include <cassert>
#include <optional>
#include <vector>
#include <iostream>

namespace Day9 {

const int FREE_BLOCK = -1;

int char_to_int(char val) { return val - 48; }

vector<int> build_ivdividual_blocks(const string &disk_map) {
  vector<int> individual_blocks;
  int id = 0;
  for (size_t i = 0; i < disk_map.size(); ++i) {
    const int length = char_to_int(disk_map[i]);
    const bool is_file = (i % 2) == 0;
    if (is_file) {
      individual_blocks.insert(individual_blocks.end(), length, id);
      ++id;
    } else {
      individual_blocks.insert(individual_blocks.end(), length, FREE_BLOCK);
    }
  }
  return individual_blocks;
}

void move_block(vector<int> &individual_blocks) {
  // TODO sanity check?
  size_t from, to;
  for (size_t i = 0; i < individual_blocks.size(); ++i) {
    if (individual_blocks[i] == FREE_BLOCK) {
      to = i;
      break;
    }
  }

  for (int i = individual_blocks.size() - 1; i >= 0; --i) {
    if (individual_blocks[i] != FREE_BLOCK) {
      from = i;
      break;
    }
  }

  const auto temp = individual_blocks[from];
  individual_blocks[from] = individual_blocks[to];
  individual_blocks[to] = temp;
}

bool has_gaps(const vector<int> &individual_blocks) {
  bool found_digit = false;
  for (int i = individual_blocks.size() - 1; i >= 0; --i) {
    char current = individual_blocks[i];
    if (current != FREE_BLOCK) {
      found_digit = true;
      continue;
    }
    if (found_digit && (current == FREE_BLOCK)) {
      return true;
    }
  }
  return false;
}

pair<size_t, size_t> find_swap_pair(const vector<int> &individual_blocks,
                                    const size_t start, const size_t end) {
  int left = -1;
  int right = -1;
  for (size_t i = start; i < end; ++i) {
    if (individual_blocks[i] == FREE_BLOCK) {
      if (left == -1) {
        left = i;
      }
    } else {
      right = i;
    }
  }
  return {left, right};
}

void move_blocks(vector<int> &individual_blocks) {
  auto [left, right] =
      find_swap_pair(individual_blocks, 0, individual_blocks.size());

  int swaps_count = 0;
  for (size_t i = 0; i < right; ++i) {
    if (individual_blocks[i] == FREE_BLOCK) {
      ++swaps_count;
    }
  }

  for (int i = 0; i < swaps_count; ++i) {
    int temp = individual_blocks[left];
    if (left > right) {
      break;
    }
    individual_blocks[left] = individual_blocks[right];
    individual_blocks[right] = temp;

    auto current = find_swap_pair(individual_blocks, left, right);
    left = current.first;
    right = current.second;
  }
}

long checksum(const vector<int> &individual_blocks) {
  long result = 0;
  for (size_t i = 0; i < individual_blocks.size(); ++i) {
    const int id = individual_blocks[i];
    if (id != FREE_BLOCK) {
      result += i * individual_blocks[i];
    }
  }
  return result;
}

long solve_day9_pt1(const string &disk_map) {
  vector<int> individual_blocks = build_ivdividual_blocks(disk_map);
  move_blocks(individual_blocks);
  return checksum(individual_blocks);
}

int find_free_space(vector<int> &individual_blocks, size_t size, size_t end) {
  if(end < size){
    return -1;
  }

  size_t current = 0;
  for (size_t i = 0; i < end - size; ++i) {
    if (individual_blocks[i] == FREE_BLOCK) {
      ++current;
      if (current == size) {
        return i - size + 1;
      }
    } else {
      current = 0;
    }
  }
  return -1;
}

void move_space(vector<int> &individual_blocks, size_t from, size_t to,
                size_t size) {
  cout << "from=" << from << " to=" << to << " size=" << size << endl;
  assert(from > to);
  assert(from < individual_blocks.size());

  for (size_t i = 0; i < size; ++i) {
    individual_blocks[to + i] = individual_blocks[from + i];
    individual_blocks[from + i] = FREE_BLOCK;
  }
}

void move_full_blocks(vector<int> &invdividual_blocks) {
  int current = invdividual_blocks[invdividual_blocks.size() - 1];
  int size = 1;
  for (int i = invdividual_blocks.size() - 2; i >= 0; --i) {
    if (invdividual_blocks[i] == current) {
      ++size;
    } else {
      if (current != FREE_BLOCK) {
        int free_space = find_free_space(invdividual_blocks, size, i + 1);
        if (free_space == -1) {
        } else {
          move_space(invdividual_blocks, i + 1, free_space, size);
        }
      }
      current = invdividual_blocks[i];
      size = 1;
    }
  }
}

long solve_day9_pt2(const string &disk_map) {
  vector<int> individual_blocks = build_ivdividual_blocks(disk_map);
  move_full_blocks(individual_blocks);
  return checksum(individual_blocks);
}

} // namespace Day9
