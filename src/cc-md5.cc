// https://codingchallenges.fyi/challenges/challenge-password-cracker/
#include <cstdint>
#include <cmath>
#include <array>
#include <boost/log/trivial.hpp>
#include <bitset>
#include <string>
#include <vector>

#include "cc-md5.h"

MD5::MD5()
{

  BOOST_LOG_TRIVIAL(debug) << "Constructor called for MD5 class";
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

void MD5::preprocess(std::vector<uint8_t> &message)
{
  uint64_t byteSize = message.size();
  uint64_t bitSize = message.size() * 8;

  message.push_back(0x80); // Append 0x80 to the message

  BOOST_LOG_TRIVIAL(debug) << "Message after appending 0x80: " << message.data();

  while ((message.size() * 8) % 512 != 448)
  {
    message.push_back(0x00);
  }

  // for (size_t i = 0; i < 8; ++i)
  // {
  //   auto byte = static_cast<uint8_t>((bitSize >> (i * 8)));
  //   std::bitset<8> bits(byte);
  //   std::string bitString = bits.to_string();
  //   BOOST_LOG_TRIVIAL(debug) << "Byte " << i << " of bitSize: " << bitString;

  //   message.push_back(byte);
  // }
}

uint32_t MD5::leftRotate(uint32_t x, uint32_t c)
{
  auto leftShift = x << c;
  auto rightShift = x >> (32 - c);
  std::bitset<32> leftShiftBits(leftShift);
  std::bitset<32> rightShiftBits(rightShift);

  return leftShift | rightShift;
}

std::string MD5::finalize()
{
  // Convert the hash components to a single string
  return toHexString(initialA0) + toHexString(initialB0) +
         toHexString(initialC0) + toHexString(initialD0);
}

std::string MD5::toHexString(uint32_t num)
{
  constexpr char hexDigits[] = "0123456789abcdef";
  std::string hexStr;
  for (int i = 28; i >= 0; i -= 4)
  { // Process each hex digit
    hexStr += hexDigits[(num >> i) & 0xF];
  }
  return hexStr;
}

std::string MD5::hash(const std::string &m)
{
  const std::vector<uint8_t> input(m.begin(), m.end());

  // Reset the MD5 object to its initial state if needed
  // initializeHashValues(); // This is an assumed method to reset A, B, C, D

  // Start with the input message
  std::vector<uint8_t> message = input;

  // Preprocess the message (padding and length appending)
  preprocess(message);

  // Process each 512-bit chunk
  for (size_t i = 0; i < message.size(); i += 64)
  {
    auto chunk = std::vector<uint8_t>(message.begin() + i, message.begin() + i + 64);
    processChunk(chunk);
  }

  // Finalize and return the hash value
  return finalize();
}

void MD5::processChunk(std::vector<uint8_t> &chunk)
{
  // BOOST_LOG_TRIVIAL(debug) << "processChunk Called";
  // Initialize the hash components for this chunk
  uint32_t A = initialA0;
  uint32_t B = initialB0;
  uint32_t C = initialC0;
  uint32_t D = initialD0;

  // Process the chunk in 16-word blocks
  for (size_t i = 0; i < 64; ++i)
  {
    uint32_t F, g;
    if (i < 16)
    {
      F = (B & C) | ((~B) & D);
      g = i;
    }
    else if (i < 32)
    {
      F = (D & B) | ((~D) & C);
      g = (5 * i + 1) % 16;
    }
    else if (i < 48)
    {
      F = B ^ C ^ D;
      g = (3 * i + 5) % 16;
    }
    else
    {
      F = C ^ (B | (~D));
      g = (7 * i) % 16;
    }

    F = F + A + K[i] + chunk[g];
    A = D;
    D = C;
    C = B;
    B = B + leftRotate(F, s[i]);
  }

  // Update the hash components
  initialA0 += A;
  initialB0 += B;
  initialC0 += C;
  initialD0 += D;
}

// void MD5::initializeHashValues()
// {
//   // Reset the hash components to their initial values as per MD5 specification
//   initialA0 = 0x67452301;
//   initialB0 = 0xefcdab89;
//   initialC0 = 0x98badcfe;
//   initialD0 = 0x10325476;
// }
