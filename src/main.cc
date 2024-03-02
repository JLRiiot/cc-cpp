#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <boost/log/trivial.hpp>

#include "cc-md5.h"

#ifdef _WIN32
#include <libbase64.h>
#endif

int main(void)
{
  MD5 hasher = {};
  std::string message = "a";

  std::string result = hasher.hash(message);
  BOOST_LOG_TRIVIAL(debug) << "Hash of " << message << " is " << result;

  return EXIT_SUCCESS;
}