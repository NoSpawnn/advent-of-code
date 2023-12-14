package main

import (
	"bufio"
	"fmt"
	"log"
	"math"
	"os"
	"strconv"
	"strings"
	"unicode"
)

type Card struct {
	id             int
	WinningNumbers []int
	DrawNumbers    []int
}

var cardCount = make(map[int]int)

func main() {
	input, err := os.Open("../input/day4.txt")
	defer input.Close()

	if err != nil {
		log.Fatal(err)
	}

	var lines []string
	scanner := bufio.NewScanner(input)
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}

	cards := parseCards(lines)
	total1, total2 := 0, 0
	for _, card := range cards {
		matches := 0
		for _, winningNum := range card.WinningNumbers {
			for _, drawNum := range card.DrawNumbers {
				if drawNum == winningNum {
					matches++
				}
			}
		}

		// TODO: understand
		// (i have absolutely no idea how this part works)
		for i := 0; i < matches; i++ {
			cardCount[card.id+i+1] += cardCount[card.id]
		}

		total1 += int(math.Pow(float64(2), float64(matches-1)))
	}

	for _, count := range cardCount {
		total2 += count
	}

	fmt.Printf("P1 TOTAL: %d\n", total1)
	fmt.Printf("P2 TOTAL: %d\n", total2)
}

func parseCards(lines []string) []Card {
	var cards []Card

	for _, line := range lines {
		cards = append(cards, parseCard(line))
	}

	return cards
}

func parseCard(line string) Card {
	var winningNumbers []int
	var drawNumbers []int

	colonPos := strings.IndexRune(line, ':')
	sections := strings.Split(line[colonPos+2:len(line)], " | ")

	numPos := colonPos - 1
	for unicode.IsDigit(rune(line[numPos])) {
		numPos--
	}

	cardId, _ := strconv.Atoi(line[numPos+1 : colonPos])

	for i := 0; i < len(sections[0]); i += 3 {
		s := strings.ReplaceAll(sections[0][i:i+2], " ", "")
		num, _ := strconv.Atoi(s)
		winningNumbers = append(winningNumbers, num)
	}

	for i := 0; i < len(sections[1]); i += 3 {
		s := strings.ReplaceAll(sections[1][i:i+2], " ", "")
		num, _ := strconv.Atoi(s)
		drawNumbers = append(drawNumbers, num)
	}

	cardCount[cardId] = 1
	return Card{cardId, winningNumbers, drawNumbers}
}
