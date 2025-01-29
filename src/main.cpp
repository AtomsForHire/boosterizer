#include "argparse.hpp"
#include "card_list.h"
#include <exception>
#include <iostream>

int main(int argc, char *argv[]) {
  try {
    argparse::ArgumentParser program("Boosteriser");

    program.add_argument("-l", "--legendaries")
        .default_value(4)
        .scan<'i', int>()
        .nargs(1)
        .help("Number of legendaries required in a booster pack");

    program.add_argument("-m", "--main")
        .default_value(16)
        .scan<'i', int>()
        .nargs(1)
        .help("Number of main cards required in a booster pack");

    program.add_argument("-p", "--players")
        .default_value(4)
        .scan<'i', int>()
        .nargs(1)
        .help("Number of players in draft");

    program.add_argument("-b", "--boosters")
        .default_value(3)
        .scan<'i', int>()
        .nargs(1)
        .help("Number of booster packs per player");

    program.add_argument("--nodupes")
        .default_value(false)
        .implicit_value(true)
        .help("Do not allow duplicates into draft");

    program.add_argument("-i", "--input")
        .default_value(std::string("input.txt"))
        .nargs(1)
        .help("Name of input file");

    program.add_argument("-o", "--output")
        .default_value(std::string("output.txt"))
        .nargs(1)
        .help("Name of output file");

    program.parse_args(argc, argv);

    int numLegendaries = program.get<int>("legendaries");
    int numRest = program.get<int>("main");
    int numPlayers = program.get<int>("players");
    int boostersPerPlayer = program.get<int>("boosters");
    bool noDupes = program.get<bool>("nodupes");
    std::string inputFile(program.get<std::string>("input"));

    // Read in all cards
    CardList cards = CardList::readFile(inputFile);

    if (noDupes && (numLegendaries > cards.getLegendaries().size() ||
                    numRest > cards.getRest().size())) {
      std::cout << "WARNING: Number of requested legendaries/rest per pack is "
                   "larger than number of total legendaries/rest in card list. "
                   "Automatically allowing duplicates."
                << std::endl;
      noDupes = false;
    }

    // Make boosters
    cards.makeBoosters(numLegendaries, numRest, numPlayers, boostersPerPlayer,
                       noDupes, program.get<std::string>("output"));

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
