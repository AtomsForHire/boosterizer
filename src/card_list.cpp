#include "card_list.h"
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <stdexcept>
#include <vector>

CardList CardList::readFile(const std::string &filename) {

  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file: " + filename);
  }

  CardList cards;
  std::string line;
  bool legendaries = true;

  while (std::getline(file, line)) {
    // Check if we've hit a new empty line. If we have then start reading in
    // the rest of the cards
    if (line.find_first_not_of(" \t\n\r") == std::string::npos) {
      legendaries = false;
      continue;
    }

    std::string lineCopy = line;
    std::istringstream iss(lineCopy);
    int count;
    std::string text;

    if (iss >> count >> text) {
      // std::cout << "There are " << count << " copies of " << text <<
      // std::endl;
      if (legendaries) {
        for (int i = 0; i < count; i++) {
          cards.legendaries.push_back(text);
        }
      } else {
        for (int i = 0; i < count; i++) {
          cards.rest.push_back(text);
        }
      }
    }
  }
  file.close();
  return cards;
}

void CardList::makeBoosters(int numLegendaries, int numRest, int numPlayers,
                            int boostersPerPlayer, bool noDupes,
                            std::string outputFile) {

  int numBoosters = numPlayers * boostersPerPlayer;

  // Create output file stream
  std::ofstream output(outputFile);
  if (!output.is_open()) {
    throw std::runtime_error("Failed to open file: output.txt");
  }

  // Draft
  for (int i = 0; i < numBoosters; i++) {
    std::vector<std::string> legendariesCopy = legendaries;
    std::vector<std::string> restCopy = rest;

    std::vector<std::string> outLeg;
    std::vector<std::string> outRest;

    // Draft the required number of legendaries
    for (int j = 0; j < numLegendaries; j++) {
      outLeg.push_back(getRandomLegendary(legendariesCopy, noDupes));
    }

    // Draft the required number of cards for rest of booster
    for (int j = 0; j < numRest; j++) {
      outRest.push_back(getRandomRest(restCopy, noDupes));
    }

    // Count number of occurences
    std::map<std::string, int> legCounts;
    std::map<std::string, int> restCounts;
    for (const auto &str : outLeg) {
      legCounts[str]++;
    }

    for (const auto &str : outRest) {
      restCounts[str]++;
    }

    // Write to file
    for (const auto &line : legCounts) {
      output << line.second << " " << line.first << std::endl;
    }

    for (const auto &line : restCounts) {
      output << line.second << " " << line.first << std::endl;
    }

    if (i != numBoosters - 1) {
      output << std::endl;
    }
  }

  output.close();
}

std::string
CardList::getRandomLegendary(std::vector<std::string> &legendariesCopy,
                             bool noDupes) {
  // Set up random number generator
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<> legendariesDist(0,
                                                  legendariesCopy.size() - 1);
  int randomIdx = legendariesDist(gen);

  std::string randomLegendary = legendariesCopy[randomIdx];

  if (noDupes) {
    legendariesCopy.erase(legendariesCopy.begin() + randomIdx);
  }

  return randomLegendary;
}

std::string CardList::getRandomRest(std::vector<std::string> &restCopy,
                                    bool noDupes) {
  // Set up random number generator
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<> restDist(0, restCopy.size() - 1);
  int randomIdx = restDist(gen);

  std::string randomRest = restCopy[randomIdx];

  if (noDupes) {
    restCopy.erase(restCopy.begin() + randomIdx);
  }

  return randomRest;
}
