// https://adventofcode.com/2023/day/7

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

#define FIVE_KIND "five"
#define FOUR_KIND "four"
#define FULL_HOUSE "full"
#define THREE_KIND "three"
#define TWO_PAIR "two"
#define ONE_PAIR "one"
#define HIGH_CARD "high"

typedef struct Hand {
  int bet;
  string type;
  string cards;
} Hand;

static int total1, total2;
static vector<Hand> hands;
static const map<char, int> CARD_STRENGTHS_1 = {
    {'2', 1}, {'3', 2}, {'4', 3},  {'5', 4},  {'6', 5},  {'7', 6},  {'8', 7},
    {'9', 8}, {'T', 9}, {'J', 10}, {'Q', 11}, {'K', 12}, {'A', 13},
};
static const map<char, int> CARD_STRENGTHS_2 = {
    {'J', 1}, {'2', 2}, {'3', 3},  {'4', 4},  {'5', 5},  {'6', 6},  {'7', 7},
    {'8', 8}, {'9', 9}, {'T', 10}, {'Q', 11}, {'K', 12}, {'A', 13},
};
static const map<string, int> HAND_STRENGTHS = {
    {HIGH_CARD, 1},  {ONE_PAIR, 2},  {TWO_PAIR, 3},  {THREE_KIND, 4},
    {FULL_HOUSE, 5}, {FOUR_KIND, 6}, {FIVE_KIND, 7},
};

struct {
  bool operator()(Hand a, Hand b) const {
    if (HAND_STRENGTHS.at(a.type) < HAND_STRENGTHS.at(b.type))
      return true;
    if (HAND_STRENGTHS.at(a.type) > HAND_STRENGTHS.at(b.type))
      return false;

    for (size_t i = 0; i < 5; ++i) {
      if (CARD_STRENGTHS_1.at(a.cards[i]) < CARD_STRENGTHS_1.at(b.cards[i]))
        return true;
      if (CARD_STRENGTHS_1.at(a.cards[i]) > CARD_STRENGTHS_1.at(b.cards[i]))
        return false;
    }

    return true;
  }
} card_comp;

string categorize_hand(string cards) {
  map<char, int> card_occurences;

  for (auto card : cards) {
    card_occurences[card] += 1;
  }

  int unique_cards = card_occurences.size();

  switch (unique_cards) {
  case 1:
    return FIVE_KIND;

    break;
  case 2: {
    auto it = card_occurences.begin();
    int card1_count = it->second;
    ++it;
    int card2_count = it->second;

    if (abs(card1_count - card2_count) == 3) {
      return FOUR_KIND;
    } else {
      return FULL_HOUSE;
    }

    break;
  }
  case 3: {
    auto it = card_occurences.begin();
    int card1_count = it->second;
    ++it;
    int card2_count = it->second;
    ++it;
    int card3_count = it->second;

    if (card1_count == 2 || card2_count == 2 || card3_count == 2) {
      return TWO_PAIR;
    } else {
      return THREE_KIND;
    }

    break;
  }
  case 4:
    return ONE_PAIR;

    break;
  case 5:
    return HIGH_CARD;

    break;
  default:
    return NULL;
  }
}

static int part_1(ifstream &input) {
  int ans = 0;
  string cards;
  int bet;

  while (input >> cards >> bet) {
    hands.push_back(Hand{bet, categorize_hand(cards), cards});
  }

  sort(hands.begin(), hands.end(), card_comp);

  for (int i = 0; i < hands.size(); ++i) {
    ans += hands[i].bet * (i + 1);
  }

  return ans;
}

int main() {
  ifstream input("../input/day7.txt");

  cout << "PART 1 TOTAL: " << part_1(input) << endl;
  input.clear();
  input.seekg(ifstream::beg);
  cout << "PART 2 TOTAL: " << total2 << endl;

  return 0;
}