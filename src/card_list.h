#include <string>
#include <vector>

class CardList {
private:
  std::vector<std::string> legendaries;
  std::vector<std::string> rest;

public:
  CardList() = default;

  static CardList readFile(const std::string &filename);

  const std::vector<std::string> getLegendaries() const { return legendaries; }
  const std::vector<std::string> getRest() const { return rest; }
  void makeBoosters(int numLegendaries, int numRest, int numPlayers,
                    int boostersPerPlayer, bool dupes, std::string outputFile);
  std::string getRandomLegendary(std::vector<std::string> &legendariesCopy,
                                 bool noDupes);
  std::string getRandomRest(std::vector<std::string> &restCopy, bool noDupes);
};
