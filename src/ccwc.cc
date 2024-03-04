#include "ccwc.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <sstream>

namespace ccwc {

  void Pipeline::pipe(PipeFunction& func) {
    Pipeline::pipes.push_back(func);
  }

  void Pipeline::process(std::istream& input) {
    std::string line;

    while (std::getline(input, line)) {
      for (auto& func : pipes) {
        func(line);
      }
    }
  }

  void Pipeline::reportResults(std::string inputFile, bool countChars, bool countWords, bool countLines) {
    std::string result = "";

    if (countChars) {
      result += std::to_string(char_count) + " ";
    }
    if (countWords) {
      result += std::to_string(word_count) + " ";
    }
    if (countLines) {
      result += std::to_string(line_count) + " ";
    }

    std::cout << result + inputFile << std::endl;
  }

  int char_count;
  int word_count;
  int line_count;

  ccwc::PipeFunction count_chars = [](const std::string& line) {
    char_count += line.size();
    };
  ccwc::PipeFunction count_lines = [](const std::string& line) {
    ++line_count;
    };
  ccwc::PipeFunction count_words = [](const std::string& line) {
    std::istringstream iss(line);
    std::string word;

    while (iss >> word) {
      ++word_count;
    }
    };
}
