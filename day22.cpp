#include <string>
#include <vector>

namespace Day22 {

using namespace std;

using num_t = long;

num_t mix(const num_t val, const num_t secret) { return val ^ secret; }

num_t prune(const num_t val) { return val % 16777216; }

num_t next(num_t secret) {
  num_t mul64 = 64 * secret;
  secret = mix(mul64, secret);
  secret = prune(secret);
  num_t div32 = secret / 32;
  secret = mix(div32, secret);
  secret = prune(secret);
  num_t mul2048 = secret * 2048;
  secret = mix(mul2048, secret);
  return prune(secret);
}

num_t generate(num_t secret) {
  for (int i = 0; i < 2000; ++i) {
    secret = next(secret);
  }
  return secret;
}

num_t solve_day22_pt1(const vector<string> &input) {
  num_t result = 0;
  for (const string &line : input) {
    const num_t secret = stol(line);
    result += generate(secret);
  }
  return result;
}

} // namespace Day22
