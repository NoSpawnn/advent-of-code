package main

import (
	"fmt"
	"log"
	"os"
)

func man() {
	day01()
}

func day01() Answer {
	input, err := os.ReadFile("input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(day01Part1(string(input)))
	fmt.Println(day01Part2(string(input)))

	return Answer{part1: int32(day01Part1(string(input))), part2: int32(day01Part2(string(input)))}

}

func day01Part1(input string) int {
	floor_no := 0

	for _, c := range input {
		switch c {
		case '(':
			floor_no++
		case ')':
			floor_no--
		}
	}

	return floor_no
}

func day01Part2(input string) int {
	floor_no := 0

	for i, c := range input {
		switch c {
		case '(':
			floor_no++
		case ')':
			floor_no--
		}

		if floor_no == -1 {
			return i + 1
		}
	}

	return -1
}
