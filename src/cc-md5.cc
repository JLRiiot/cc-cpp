// https://codingchallenges.fyi/challenges/challenge-password-cracker/
#include <cstdint>
#include <cmath>
#include <array>

#include "cc-md5.h"

MD5::MD5()
{
  initializeK();
}

void MD5::initializeK()
{
  for (size_t i = 0; i < 64; ++i)
  { // For loop to iterate 64 times
    // Calculate K[i] as the floor of 2^32 times the absolute value of sin(i+1)
    // Cast the result of sin to double, and the final result to uint32_t
    K[i] = static_cast<uint32_t>(std::floor(std::abs(std::sin(static_cast<double>(i) + 1)) * std::pow(2, 32)));
  }
}