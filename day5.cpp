#include "day5.hpp"
#include <cstring>
#include <iomanip>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <string>

namespace Day5 {

void print_MD5(unsigned char *md, long size = MD5_DIGEST_LENGTH) {
  for (int i = 0; i < size; i++) {
    cout << hex << setw(2) << setfill('0') << (int)md[i];
  }
  cout << endl;
}

void computeMD5FromString(const string &str) {
  unsigned char result[MD5_DIGEST_LENGTH];
  MD5((unsigned char *)str.c_str(), str.length(), result);

  cout << "MD5 of '" << str << "' : ";
  print_MD5(result);
}

int foo(const string &s) {

  char md5hex[EVP_MAX_MD_SIZE * 2 + 1];
  EVP_MD_CTX *pEvpContext;
  pEvpContext = EVP_MD_CTX_create();

  unsigned char unMdValue[EVP_MAX_MD_SIZE];
  unsigned int uiMdLength;

  // Initialization
  EVP_MD_CTX_init(pEvpContext);
  EVP_DigestInit_ex(pEvpContext, EVP_md5(), NULL);

  // Calculate MD5 for given string
  EVP_DigestUpdate(pEvpContext, s.c_str(), s.size());

  // Save MD5 into temp variable
  EVP_DigestFinal_ex(pEvpContext, unMdValue, &uiMdLength);

  EVP_MD_CTX_destroy(pEvpContext);

  // Copy the digest from the temp variable into the return value
  unsigned int md5hexSize = sizeof(md5hex);
  memset(md5hex, '\0', md5hexSize);

  // if the size is bigger than the return buffer size, just exit
  if (2 * uiMdLength > md5hexSize) {
    return false;
  }

  for (unsigned int i = 0; i < uiMdLength; i++) {
    sprintf(&md5hex[i * 2], "%02x", unMdValue[i]);
  }
  printf("Line: %s\nIts MD5: %s\n", s.c_str(), md5hex);
  return 0;
}

} // namespace Day5
