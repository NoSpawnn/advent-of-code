package main

import (
	"bufio"
	"fmt"
	"log"
	"math"
	"os"
	"strconv"
	"unicode"
)

type DigitPos struct {
	line  int
	start int
	end   int
}

type PunctPos struct {
	line int
	col  int
}

func main() {
	input, err := os.Open("../input/day3.txt")
	defer input.Close()

	if err != nil {
		log.Fatal(err)
	}

	var lines []string
	scanner := bufio.NewScanner(input)
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}

	punctPositions := findPuncts(lines)
	numPositions := findDigits(lines)

	total1 := 0
	for _, pPos := range punctPositions {
		for _, nPos := range numPositions {
			if math.Abs(float64(pPos.line)-float64(nPos.line)) <= 1.0 && nPos.start-1 <= pPos.col && pPos.col <= nPos.end {
				t, _ := strconv.Atoi(lines[nPos.line][nPos.start:nPos.end])

				total1 += t
			}
		}
	}

	total2 := 0
	for _, pPos := range punctPositions {
		if lines[pPos.line][pPos.col] != '*' {
			continue
		}

		matched := [2]int{0, 0}
		for _, nPos := range numPositions {
			if math.Abs(float64(pPos.line)-float64(nPos.line)) <= 1.0 && nPos.start-1 <= pPos.col && pPos.col <= nPos.end {
				t, _ := strconv.Atoi(lines[nPos.line][nPos.start:nPos.end])

				if matched[0] == 0 {
					matched[0] = t
				} else {
					matched[1] = t
				}
			}
		}

		if matched[0] != 0 && matched[1] != 0 {
			total2 += matched[0] * matched[1]
		}

	}

	fmt.Printf("P1 TOTAL: %d\n", total1)
	fmt.Printf("P2 TOTAL: %d\n", total2)
}

func findDigits(lines []string) []DigitPos {
	var arr []DigitPos

	for lineIdx, line := range lines {
		lineLen := len(line) - 1

		for col := 0; col < lineLen; col++ {
			if unicode.IsDigit(rune(line[col])) {
				firstDigitIdx := col
				lastDigitIdx := col + 1

				for lastDigitIdx <= lineLen && unicode.IsDigit(rune(line[lastDigitIdx])) {
					lastDigitIdx++
				}

				arr = append(arr, DigitPos{lineIdx, firstDigitIdx, lastDigitIdx})
				col = lastDigitIdx
			}
		}
	}

	return arr
}

func findPuncts(lines []string) []PunctPos {
	var punctPos []PunctPos

	for row, text := range lines {
		for col, char := range []rune(text) {
			if char == '.' {
				continue
			}

			if unicode.IsPunct(char) || unicode.IsSymbol(char) {
				punctPos = append(punctPos, PunctPos{row, col})
			}
		}
	}

	return punctPos
}
