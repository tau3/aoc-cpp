#include "day9.hpp"
#include "util.hpp"
#include <iostream>
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

  // cout << "before: " << individual_blocks;

  const auto temp = individual_blocks[from];
  individual_blocks[from] = individual_blocks[to];
  individual_blocks[to] = temp;

  // cout << "after: " << individual_blocks << endl;
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
      // cout << "gap in " << individual_blocks << " at " << i << endl;
      return true;
    }
  }
  return false;
}

void move_blocks(vector<int> &invidual_blocks) {
  while (has_gaps(invidual_blocks)) {
    // cout << "has gaps: " << invidual_blocks << endl;
    move_block(invidual_blocks);
  }
}

int checksum(const vector<int> &individual_blocks) {
  int result = 0;
  for (size_t i = 0; individual_blocks[i] != FREE_BLOCK; ++i) {
    result += i * individual_blocks[i];
  }
  return result;
}

int solve_pt1(const string &disk_map) {
  vector<int> individual_blocks = build_ivdividual_blocks(disk_map);
  print(individual_blocks);
  move_blocks(individual_blocks);
  cout << "MOVING" << endl; 
  return checksum(individual_blocks);
}

} // namespace Day9
