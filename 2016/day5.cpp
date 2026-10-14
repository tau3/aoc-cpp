#include "day5.hpp"
#include "util.hpp"
#include <cstddef>
#include <cstring>
#include <format>
#include <openssl/evp.h>
#include <string>

namespace Day5 {

// https://ladydebug.com/blog/2022/11/29/calculate-md5-programmatically/
string md5(const string &str) {

  char md5hex[EVP_MAX_MD_SIZE * 2 + 1];
  EVP_MD_CTX *pEvpContext;
  pEvpContext = EVP_MD_CTX_create();

  unsigned char unMdValue[EVP_MAX_MD_SIZE];
  unsigned int uiMdLength;

  // Initialization
  EVP_MD_CTX_init(pEvpContext);
  EVP_DigestInit_ex(pEvpContext, EVP_md5(), NULL);

  // Calculate MD5 for given string
  EVP_DigestUpdate(pEvpContext, str.c_str(), str.size());

  // Save MD5 into temp variable
  EVP_DigestFinal_ex(pEvpContext, unMdValue, &uiMdLength);

  EVP_MD_CTX_destroy(pEvpContext);

  // Copy the digest from the temp variable into the return value
  unsigned int md5hexSize = sizeof(md5hex);
  memset(md5hex, '\0', md5hexSize);

  // if the size is bigger than the return buffer size, just exit
  if (2 * uiMdLength > md5hexSize) {
    throw runtime_error(format("failed to calc md5 for {}", str));
  }

  for (unsigned int i = 0; i < uiMdLength; i++) {
    sprintf(&md5hex[i * 2], "%02x", unMdValue[i]);
  }

  return md5hex;
}

string solve_day5_pt1(const string &doorId) {
  uint64_t i = 0;
  int j = 0;

  string result = "";
  while (j < 8) {
    const string current = doorId + to_string(i);
    const string md5_hash = md5(current);
    if (util::starts_with(md5_hash, "00000")) {
      result += md5_hash[5];
      j++;
    };
    i++;
  }
  return result;
}

string solve_day5_pt2(const string &doorId) {
  const size_t result_size = 8;
  string result = "";
  for (size_t i = 0; i < result_size; i++) {
    result += ' ';
  }

  uint64_t i = 0;
  size_t j = 0;

  while (j < result_size) {
    const string current = doorId + to_string(i);
    const string md5_hash = md5(current);
    if (util::starts_with(md5_hash, "00000")) {
      const size_t index = (md5_hash[5] - '0');
      if (index < result_size) {
        if (result[index] == ' ') {
          result[index] = md5_hash[6];
          j++;
        }
      }
    }
    i++;
  }
  return result;
}

} // namespace Day5
