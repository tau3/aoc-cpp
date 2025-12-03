#include "day2.hpp"
#include "util.hpp"
#include <cstddef>

namespace Day2 {

using namespace std;

long solve_day2_pt1(const vector<string> &input) {
  const string &line = input[0];
  long result = 0;
  for (const string &range : split(line, ",")) {
    const vector<string> tokens = split(range, "-");
    const long start = stol(tokens[0]);
    const long end = stol(tokens[1]);
    for (long i = start; i <= end; i++) {
      const string str_rep = to_string(i);
      const size_t length = str_rep.length();
      if ((length % 2) != 0) {
        continue;
      }
      const size_t half = length / 2;
      bool is_invalid = true;
      for (size_t j = 0; j < half; j++) {
        if (str_rep[j] != str_rep[j + half]) {
          is_invalid = false;
          break;
        }
      }
      if (is_invalid) {
        result += i;
        cout << "invalid " << i << endl;
      }
    }
  }
  return result;
}

} // namespace Day2
