#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <sstream>
// wc command line tool for counting characters, words, and lines in a file

#ifndef CCWC_H
#define CCWC_H

namespace ccwc
{
  using CounterType = int;
  using PipeFunction = std::function<void(const std::string&)>;

  extern int char_count;
  extern int word_count;
  extern int line_count;

  extern ccwc::PipeFunction count_chars;
  extern ccwc::PipeFunction count_words;
  extern ccwc::PipeFunction count_lines;
  class Pipeline {
  public:
    void pipe(PipeFunction&);
    void process(std::istream& input);
    void reportResults(std::string inputFile, bool countChars, bool countWords, bool countLines);

  private:
    std::vector<PipeFunction> pipes;
  };
}

#endif // 
