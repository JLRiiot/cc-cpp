#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// wc command line tool for counting characters, words, and lines in a file

#ifndef CCWC_H
#define CCWC_H

namespace ccwc
{
  void count_chars(int& counter);
  void count_words(int& counter);
  void count_lines(int& counter);

  class Pipeline {
  public:
    void pipe(void (*func)(const std::string&));
    void process();

  private:
    std::vector<void (*)(const std::string&)> pipes;
  };
}

#endif // 
