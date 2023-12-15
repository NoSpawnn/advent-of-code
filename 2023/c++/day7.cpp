// https://adventofcode.com/2023/day/7

#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

#define FIVE_KIND "five"
#define FOUR_KIND "four"
#define FULL_HOUSE "full"
#define TWO_PAIR "two"
#define ONE_PAIR "one"
#define HIGH_CARD "high"

int main() {
  ifstream input("../input/day7.txt");

  string hand;
  int bet;
  while (input >> hand) {
    input >> bet;

    

    cout << hand << " " << bet << '\n';
  }

  return 0;
}