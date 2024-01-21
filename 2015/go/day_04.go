package main

import (
	"crypto/md5"
	"encoding/hex"
	"fmt"
	"log"
	"os"
	"strings"
)

func main() {
	day04()
}

func day04() {
	input, err := os.ReadFile("input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(day04Part1(string(input)))
	fmt.Println(day04Part2(string(input)))
}

func day04Part1(input string) int {
	return solve(input, 5)

}

func day04Part2(input string) int {
	return solve(input, 6)
}

func solve(input string, leading int) int {
	toMatch := strings.Repeat("0", leading)
	hashNo := 1

	for {
		if hash(input, hashNo)[:leading] == toMatch {
			return hashNo
		}
		hashNo++
	}
}

func hash(s string, n int) string {
	hash := md5.Sum([]byte(fmt.Sprintf("%s%d", s, n)))
	return hex.EncodeToString(hash[:])
}
