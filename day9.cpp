#include <cstddef>
#include <string>
#include <type_traits>

using namespace std;

string build_ivdividual_blocks(const string &disk_map) {
  string individual_blocks;
  int id = 0;
  for (size_t i = 0; i < disk_map.size(); ++i) {
    const int length = disk_map[i];
    const bool is_file = (i % 2) == 0;
    if (is_file) {
      const string suffix(length, id);
      individual_blocks += suffix;
      ++id;
    } else {
      const string suffix(length, '.');
      individual_blocks += suffix;
    }
  }
  return individual_blocks;
}

void move_block(string &individual_blocks) {
  // TODO sanity check?
  size_t from, to;
  for (size_t i = 0; i < individual_blocks.size(); ++i) {
    if (individual_blocks[i] == '.') {
      to = i;
      break;
    }
  }

  for (int i = individual_blocks.size() - 1; i >= 0; --i) {
    if (individual_blocks[i] != '.') {
      from = i;
      break;
    }
  }

  const auto temp = individual_blocks[from];
  individual_blocks[from] = individual_blocks[to];
  individual_blocks[to] = temp;
}

bool has_gaps(const string &individual_blocks) {
  bool found_digit = false;
  for (int i = individual_blocks.size(); i >= 0; --i) {
    char current = individual_blocks[i];
    if (current != '.') {
      found_digit = true;
      continue;
    }
    if (found_digit && (current == '.')) {
      return true;
    }
  }
  return false;
}

void move_blocks(string &invidual_blocks) {
  while (has_gaps(invidual_blocks)) {
    move_block(invidual_blocks);
  }
}

int checksum(const string &individual_blocks) {
  int result = 0;
  for (size_t i = 0; individual_blocks[i] != '.'; ++i) {
    result += i * individual_blocks[i];
  }
  return result;
}

int solve(const string &disk_map) {
  string individual_blocks = build_ivdividual_blocks(disk_map);
  move_blocks(individual_blocks);
  return checksum(individual_blocks);
}
