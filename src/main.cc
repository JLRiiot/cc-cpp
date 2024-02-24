#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <zlib.h>

#include "cc-md5.h"

#ifdef _WIN32
#include <libbase64.h>
#endif

int main(void)
{
  MD5 hasher = {};
  auto message = "Amo-A0-Mi1-Familia2";
  std::vector<uint8_t> messageBytes(message, message + strlen(message));

  hasher.preprocess(messageBytes);

  return EXIT_SUCCESS;
}