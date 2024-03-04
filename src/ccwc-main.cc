#include <iostream>
#include <boost/program_options.hpp>
#include <boost/log/trivial.hpp>
#include "ccwc.h"

/**
 * 
*/
namespace po = boost::program_options;

/**
 * @brief Entry point for the application https://codingchallenges.fyi/challenges/challenge-wc
 * @param argc count of parameters passed to the program
 * @param argv c-string array of the params
 */
int main(int argc, char* argv[])
{
  // for (int i = 0; i < argc; i++)
  // {
  //   std::cout << "Argument " << i << ": " << argv[i] << std::endl;
  // }
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "produce help message")
    ("chars,c", "count characters")
    ("words,w", "count words")
    ("lines,l", "count lines")
    ("input-file", po::value<std::string>(), "input file");

  po::positional_options_description p;
  p.add("input-file", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);

  if (vm.count("help")) {
    std::cout << desc << std::endl;
  }

  bool countChars = vm.count("chars") || (!vm.count("words") && !vm.count("lines"));
  bool countWords = vm.count("words") || (!vm.count("chars") && !vm.count("lines"));
  bool countLines = vm.count("lines") || (!vm.count("words") && !vm.count("chars"));

  ccwc::Pipeline pl{};

  if (countChars) {
    pl.pipe(ccwc::count_chars);
  }
  if (countWords) {
    pl.pipe(ccwc::count_words);
  }
  if (countLines) {
    pl.pipe(ccwc::count_lines);
  }

  bool piped_input = !isatty(STDIN_FILENO);
  std::string input_file = vm.count("input-file") ? vm["input-file"].as<std::string>() : "";

  if (vm.count("input-file")) {
    std::ifstream file(input_file);

    if (!file.is_open()) {
      std::cout << "Failed to open file: " << input_file << std::endl;
      return EXIT_FAILURE;
    }

    pl.process(file);

    file.close();
  }
  else if (piped_input) {
    pl.process(std::cin);
  }
  else {
    return EXIT_FAILURE;
  }

  pl.reportResults(input_file, countChars, countWords, countLines);

  return EXIT_SUCCESS;
}
