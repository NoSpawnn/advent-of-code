package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

var (
	disallowedPairs = []string{"ab", "cd", "pq", "xy"}
	vowels          = []string{"a", "e", "i", "o", "u"}
)

func main() {
	day05()
}

func day05() {
	lines, err := readLinesToArray("input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(day05Part1(lines))
	// fmt.Println(day05Part2(lines))
}

func day05Part1(input []string) int {
	total := 0

	for _, line := range input {
		if isNice(line) {
			total++
		}
	}

	return total
}

func isNice(s string) bool {
	vowelCount := 0
	hasPair := false

	for _, pair := range disallowedPairs {
		if strings.Contains(s, pair) {
			return false
		}
	}

	for _, vowel := range vowels {
		vowelCount += strings.Count(s, vowel)

		if vowelCount >= 3 {
			break
		}
	}

	for i := 0; i < len(s)-1; i++ {
		if s[i] == s[i+1] {
			hasPair = true
			break
		}
	}

	return vowelCount >= 3 && hasPair
}

func readLinesToArray(path string) ([]string, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	var lines []string
	scan := bufio.NewScanner(file)
	for scan.Scan() {
		lines = append(lines, scan.Text())
	}

	return lines, scan.Err()
}
