#include <array>
#include <string>
#include <unordered_map>
#include <unordered_set>
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

using Cache = unordered_map<array<int, 4>, int>;

Cache foo(const num_t secret) {
  vector<int> prices;
  prices.reserve(2000 + 1);
  prices[0] = secret;

  for (int i = 1; i < 2000; ++i) {
    prices[i] = generate(prices[i - 1]);
    prices[i] = prices[i] % 10;
  }

  Cache cache;
  for (size_t i = 3; i < prices.size(); ++i) {
    const int t0 = prices[i - 3];
    const int t1 = prices[i - 2];
    const int t2 = prices[i - 1];
    const int t3 = prices[i];

    const array<int, 4> key = {t0, t1, t2, t3};
    cache[key] = max(prices[i], cache[key]);
  }
  return cache;
}

int solve_day22_pt2(const vector<string> &input) {
  vector<Cache> caches;
  caches.reserve(input.size());
  for (const string &line : input) {
    const Cache cache = foo(stol(line));
    caches.push_back(cache);
  }

  unordered_set<array<int, 4>> all_keys;
  for (const Cache &cache : caches) {
    for (const auto &[k, v] : cache) {
      all_keys.insert(k);
    }
  }

  unordered_map<array<int, 4>, int> result;
  for (const array<int, 4> &key : all_keys) {
    for (const Cache &cache : caches) {
      int price = 0;
      if (cache.find(key) != cache.end()) {
        price = cache.at(key);
      }
      result[key] += price;
    }
  }

  int x = 0;
  for (const auto &[k, v] : result) {
    if (x < v) {
      x = v;
    }
  }
  return x;
}

} // namespace Day22
