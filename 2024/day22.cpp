#include "day22.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <unordered_map>
#include <unordered_set>

namespace Day22 {

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

struct ArrayHash {
  size_t operator()(const array<int, 4> &arr) const {
    return 31 * arr[0] + 17 * arr[1] + 11 * arr[2] + 19 * arr[3];
  }
};

using Cache = unordered_map<array<int, 4>, int, ArrayHash>;

Cache build_changes_cache(const num_t secret) {
  const size_t length = 2000;
  vector<num_t> secrets;
  secrets.reserve(length + 1);
  secrets.push_back(secret);
  for (size_t i = 1; i < length + 1; ++i) {
    secrets.push_back(next(secrets[i - 1]));
  }
  assert(secrets.size() == length + 1);

  vector<int> prices;
  prices.reserve(secrets.size());
  for (size_t i = 0; i < secrets.size(); i++) {
    const int price = secrets[i] % 10;
    prices.push_back(price);
  }

  vector<int> changes;
  changes.reserve(prices.size() - 1);
  for (size_t i = 1; i < prices.size(); ++i) {
    const int change = prices[i] - prices[i - 1];
    changes.push_back(change);
  }
  assert(changes.size() == length);

  Cache cache;
  for (size_t i = 3; i < changes.size(); ++i) {
    const int t0 = changes[i - 3];
    const int t1 = changes[i - 2];
    const int t2 = changes[i - 1];
    const int t3 = changes[i];

    const array<int, 4> key = {t0, t1, t2, t3};
    if (cache.find(key) != cache.end()) {
      continue;
    }
    cache[key] = prices[i + 1];
  }
  return cache;
}

int solve_day22_pt2(const vector<string> &input) {
  vector<Cache> caches;
  caches.reserve(input.size());
  for (const string &line : input) {
    const Cache cache = build_changes_cache(stol(line));
    caches.push_back(cache);
  }

  unordered_set<array<int, 4>, ArrayHash> all_keys;
  for (const Cache &cache : caches) {
    for (const auto &[key, _] : cache) {
      all_keys.insert(key);
    }
  }

  Cache prices;
  for (const array<int, 4> &key : all_keys) {
    prices[key] = 0;
    for (const Cache &cache : caches) {
      int price = 0;
      if (cache.find(key) != cache.end()) {
        price = cache.at(key);
      }
      prices[key] += price;
    }
  }

  int result = 0;
  for (const auto [_, price] : prices) {
    if (result < price) {
      result = price;
    }
  }
  return result;
}

} // namespace Day22
