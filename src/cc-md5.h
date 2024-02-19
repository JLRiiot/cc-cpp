#include <cstdint>
#include <cmath>
#include <array>

#ifndef CC_MD5_H
#define CC_MD5_H

class MD5
{
public:
  MD5();

private:
  static constexpr uint32_t initialA0 = 0x67452301;
  static constexpr uint32_t initialB0 = 0xefcdab89;
  static constexpr uint32_t initialC0 = 0x98badcfe;
  static constexpr uint32_t initialD0 = 0x10325476;

  static constexpr std::array<uint32_t, 64> s = {
      // round 1
      7, 12, 17, 22,
      7, 12, 17, 22,
      7, 12, 17, 22,
      7, 12, 17, 22,

      // round 2
      5, 9, 14, 20,
      5, 9, 14, 20,
      5, 9, 14, 20,
      5, 9, 14, 20,

      // round 3
      4, 11, 16, 23,
      4, 11, 16, 23,
      4, 11, 16, 23,
      4, 11, 16, 23,

      // round 3
      6, 10, 15, 21,
      6, 10, 15, 21,
      6, 10, 15, 21,
      6, 10, 15, 21};

  std::array<uint32_t, 64> K; // Declare an array of uint32_t named K with 64 elements

  void initializeK();
};

#endif