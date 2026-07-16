
#include <cstddef>
#include <optional>
#include <string>
#include <utility>
namespace Day11 {

bool is_valid_password(const std::string &password) {
  bool has_incr = false;
  bool has_two_pairs = false;
  std::pair<std::optional<char>, std::optional<char>> pairs;
  for (std::size_t i = 0; i < password.length(); i++) {
    const char current = password[i];
    if (current == 'i' || current == 'o' || current == 'l') {
      return false;
    }

    if (!has_incr && i >= 2) {
      const char middle = password[i - 1];
      const char left = password[i - 2];
      has_incr = (left == (middle - 1)) && (middle == (current - 1));
    }

    if (i >= 1) {
      const char prev = password[i - 1];
      if (prev == current) {
        if (!pairs.first.has_value()) {
          pairs.first = current;
        } else if (!pairs.second.has_value() &&
                   pairs.first != std::optional<char>(current)) {
          pairs.second = current;
          has_two_pairs = true;
        }
      }
    }
  }
  return has_incr && has_two_pairs;
}

std::string increment(const std::string &password) {
  std::string result = password;
  for (long i = password.length() - 1; i >= 0; i--) {
    const char current = password[i];
    if (current != 'z') {
      result[i] = current + 1;
      return result;
    } else {
      result[i] = 'a';
    }
  }
  throw "unreachable";
}

std::string solve_day11_pt1(const std::string &password) {
  std::string result = password;
  do {
    result = increment(result);
  } while (!is_valid_password(result));
  return result;
}

}; // namespace Day11
