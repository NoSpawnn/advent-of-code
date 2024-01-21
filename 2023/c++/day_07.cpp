// https://adventofcode.com/2023/day/7

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::map;
using std::string;
using std::vector;

static int categorise_hand(const string cards, const string strengths,
                           bool jokers);

const char JOKER = 'J';

enum HAND_TYPE {
  HIGH_CARD = 1,
  ONE_PAIR,
  TWO_PAIR,
  THREE_KIND,
  FULL_HOUSE,
  FOUR_KIND,
  FIVE_KIND
};

typedef struct Hand {
  int bet;
  int type;
  string cards;
} Hand;

static map<char, int> count_cards(string cards) {
  map<char, int> cards_count;

  for (const char &c : cards) {
    cards_count[c]++;
  }

  return cards_count;
}

int best_alternate(string cards, const string &strengths,
                   const int jokers_count) {
  switch (categorise_hand(cards, strengths, false)) {
  case FIVE_KIND:
    return FIVE_KIND;
  case FOUR_KIND:
    return FIVE_KIND;
  case FULL_HOUSE:
    switch (jokers_count) {
    case 1:
      return FOUR_KIND;
    case 2:
      return FIVE_KIND;
    case 3:
      return FIVE_KIND;
    }
  case THREE_KIND:
    return FOUR_KIND;
  case TWO_PAIR:
    switch (jokers_count) {
    case 1:
      return FULL_HOUSE;
    case 2:
      return FOUR_KIND;
    }
  case ONE_PAIR:
    return THREE_KIND;
  case HIGH_CARD:
    return ONE_PAIR;
  default:
    cerr << "bad cards? " << cards << endl;
    exit(EXIT_FAILURE);
  }
}

static int categorise_hand(const string cards, const string card_strengths,
                           bool jokers) {
  map<char, int> cards_count = count_cards(cards);

  if (jokers && cards_count.count(JOKER)) {
    return best_alternate(cards, card_strengths, cards_count.at(JOKER));
  }

  switch (cards_count.size()) {
  case 5:
    return HIGH_CARD;
  case 4:
    return ONE_PAIR;
  case 3:
    return std::any_of(cards_count.begin(), cards_count.end(),
                       [](auto count) { return count.second == 2; })
               ? TWO_PAIR
               : THREE_KIND;
  case 2:
    return std::abs(cards_count.begin()->second -
                    cards_count.rbegin()->second) == 3
               ? FOUR_KIND
               : FULL_HOUSE;
  case 1:
    return FIVE_KIND;
  default:
    cerr << "hands should be of length five, got length " << cards.length()
         << " (" << cards << ")" << endl;
    exit(EXIT_FAILURE);
  }
}

static int solve(ifstream &input, const string card_strengths, bool jokers) {
  int total = 0, bet;
  string cards;
  vector<Hand> hands;

  while (input >> cards >> bet) {
    hands.push_back(
        Hand{bet, categorise_hand(cards, card_strengths, jokers), cards});
  }

  std::sort(hands.begin(), hands.end(), [card_strengths](Hand a, Hand b) {
    if (a.type != b.type) {
      return a.type < b.type;
    }

    for (size_t i = 0; i < a.cards.length(); i++) {
      int score_a = card_strengths.find(a.cards[i]);
      int score_b = card_strengths.find(b.cards[i]);

      if (score_a != score_b) {
        return score_a < score_b;
      }
    }

    return true;
  });

  for (size_t rank = 0; rank < hands.size(); rank++) {
    total += hands[rank].bet * (rank + 1);
  }

  return total;
}

int part_1(ifstream &input) { return solve(input, "23456789TJQKA", false); }

int part_2(ifstream &input) { return solve(input, "J23456789TQKA", true); }

int main() {
  ifstream input("../input/day_07.txt");

  if (!input.is_open()) {
    perror(NULL);
    return -1;
  }

  cout << "PART 1 TOTAL: " << part_1(input) << endl;
  input.clear();
  input.seekg(ifstream::beg);
  cout << "PART 2 TOTAL: " << part_2(input) << endl;

  return 0;
}