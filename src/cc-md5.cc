// https://codingchallenges.fyi/challenges/challenge-password-cracker/
#include <cstdint>
#include <cmath>
#include <array>
#include <boost/log/trivial.hpp>
#include <bitset>
#include <string>

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
  BOOST_LOG_TRIVIAL(debug) << "preprocess Called";
  uint64_t byteSize = message.size();
  uint64_t bitSize = message.size() * 8;

  BOOST_LOG_TRIVIAL(debug) << "Message: " << message.data();
  BOOST_LOG_TRIVIAL(debug) << "Bit size of message: " << bitSize;
  BOOST_LOG_TRIVIAL(debug) << "Byte size of message: " << byteSize;

  message.push_back(0x80); // Append 0x80 to the message

  BOOST_LOG_TRIVIAL(debug) << "Message after appending 0x80: " << message.data();

  while ((message.size() * 8) % 512 != 448)
  {
    message.push_back(0x00);
    BOOST_LOG_TRIVIAL(debug) << "Message: " << message.data();
  }

  for (size_t i = 0; i < 8; ++i)
  {
    auto byte = static_cast<uint8_t>((bitSize >> (i * 8)));
    std::bitset<8> bits(byte);
    std::string bitString = bits.to_string();
    BOOST_LOG_TRIVIAL(debug) << "Byte: " << bitString;

    message.push_back(byte);
  }

  BOOST_LOG_TRIVIAL(debug) << "Message after appending bit size: " << message.data();
}