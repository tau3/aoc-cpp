#include "day9.hpp"
#include "util.hpp"
#include <cstddef>
#include <string>
#include <vector>

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

struct Block {
  int id;
  size_t size;
};

vector<Block> group(const vector<int> &individual_blocks) {
  int current = individual_blocks[0];
  size_t size = 1;
  vector<Block> result;
  for (size_t i = 1; i < individual_blocks.size(); ++i) {
    if (individual_blocks[i] == current) {
      ++size;
    } else {
      const Block block = {current, size};
      result.push_back(block);
      current = individual_blocks[i];
      size = 1;
    }
  }
  return result;
}

void move_blocks(vector<Block> &grouped_blocks) {
  for (int i = grouped_blocks.size() - 1; i >= 0; --i) {
    const Block &current = grouped_blocks[i];
    if (current.id == FREE_BLOCK) {
      continue;
    }

    for (size_t j = 0; j < i; ++j) {
      const Block &free_block = grouped_blocks[j];
      if (free_block.id != FREE_BLOCK) {
        continue;
      }
      if (free_block.size < current.size) {
        continue;
      }

      const Block temp = grouped_blocks[i];
      grouped_blocks[i] = grouped_blocks[j];
      grouped_blocks[j] = temp;
      break;
    }
  }
}

long checksum(const vector<Block> &grouped_blocks) {
  int i = 0;
  long result = 0;
  for (const Block &block : grouped_blocks) {
    for (size_t j = 0; j < block.size; ++i) {
      result += block.id * (j + i);
    }
    i += block.size;
  }
  return result;
}

long solve_day9_pt1(const string &disk_map) {
  vector<int> individual_blocks = build_ivdividual_blocks(disk_map);
  move_blocks(individual_blocks);
  return checksum(individual_blocks);
}

long solve_day9_pt2(const string &disk_map) {
  const vector<int> individual_blocks = build_ivdividual_blocks(disk_map);
  vector<Block> grouped_blocks = group(individual_blocks);
  move_blocks(grouped_blocks);
  return checksum(grouped_blocks);
}

} // namespace Day9
