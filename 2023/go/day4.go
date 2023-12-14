package main

import (
	"bufio"
	"fmt"
	"log"
	"math"
	"os"
	"strconv"
	"strings"
)

type Card struct {
	id             int
	WinningNumbers []int
	DrawNumbers    []int
	Matches        int
}

var totalCards = make(map[int]int)

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
	total1 := 0
	total2 := len(cards)

	for i, card := range cards {
		matches := 0
		for _, winningNum := range card.WinningNumbers {
			for _, drawNum := range card.DrawNumbers {
				if drawNum == winningNum {
					matches++
					break
				}
			}
		}

		total1 += int(math.Pow(float64(2), float64(matches-1)))

		cards[i].Matches += matches
	}

	fmt.Println(totalCards)

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

	numStartPos := strings.IndexRune(line, ' ')
	colonPos := strings.IndexRune(line, ':')
	game_id, _ := strconv.Atoi(line[numStartPos+1 : colonPos])
	sections := strings.Split(line[colonPos+2:len(line)], " | ")
	winningNumbersStr := sections[0]
	drawNumbersStr := sections[1]

	for i := 0; i < len(winningNumbersStr)-1; i += 3 {
		s := strings.ReplaceAll(winningNumbersStr[i:i+2], " ", "")
		num, _ := strconv.Atoi(s)
		winningNumbers = append(winningNumbers, num)
	}

	for i := 0; i < len(drawNumbersStr)-1; i += 3 {
		s := strings.ReplaceAll(drawNumbersStr[i:i+2], " ", "")
		num, _ := strconv.Atoi(s)
		drawNumbers = append(drawNumbers, num)
	}

	totalCards[game_id] = 1
	return Card{game_id, winningNumbers, drawNumbers, 0}
}
