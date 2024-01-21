package main

import (
	"fmt"
	"log"
	"os"
)

const (
	North = '^'
	South = 'v'
	East  = '>'
	West  = '<'
)

func main() {
	day03()
}

func day03() {
	input, err := os.ReadFile("input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(day03Part1(string(input)))
	fmt.Println(day03Part2(string(input)))
}

func day03Part1(input string) int {
	var size int
	if len(input)%2 == 0 {
		size = len(input)
	} else {
		size = len(input) + 1
	}

	houses := make([][]int, size*2)
	for i := range houses {
		houses[i] = make([]int, size*2)
	}
	centerX, centerY := size-1, size-1
	x, y := centerX, centerY
	houses[y][x] = 1

	for _, direction := range input {
		switch direction {
		case North:
			y++
		case South:
			y--
		case East:
			x++
		case West:
			x--
		}

		if x < 0 && y < 0 {
			houses[centerY-y][centerX-x] = 1
		} else if x < 0 {
			houses[centerY-y][x] = 1
		} else if y < 0 {
			houses[y][centerX-x] = 1
		} else {
			houses[y][x] = 1
		}
	}

	count := 0
	for _, row := range houses {
		for _, col := range row {
			if col == 1 {
				count++
			}
		}
	}

	return count
}

func day03Part2(input string) int {
	var size int
	if len(input)%2 == 0 {
		size = len(input)
	} else {
		size = len(input) + 1
	}

	visited := make([][]int, size*2)
	for i := range visited {
		visited[i] = make([]int, size*2)
	}
	centerX, centerY := size-1, size-1
	santaX, santaY, roboX, roboY := centerX, centerY, centerX, centerY
	visited[santaY][santaX] = 1

	for i, direction := range input {
		if i%2 == 0 {
			switch direction {
			case North:
				santaY++
			case South:
				santaY--
			case East:
				santaX++
			case West:
				santaX--
			}

			if santaX < 0 && santaY < 0 {
				visited[centerY-santaY][centerX-santaX] = 1
			} else if santaX < 0 {
				visited[centerY-santaY][santaX] = 1
			} else if santaY < 0 {
				visited[santaY][centerX-santaX] = 1
			} else {
				visited[santaY][santaX] = 1
			}
		} else {
			switch direction {
			case North:
				roboY++
			case South:
				roboY--
			case East:
				roboX++
			case West:
				roboX--
			}

			if roboX < 0 && roboY < 0 {
				visited[centerY-roboY][centerX-roboX] = 1
			} else if roboX < 0 {
				visited[centerY-roboY][roboX] = 1
			} else if roboY < 0 {
				visited[roboY][centerX-roboX] = 1
			} else {
				visited[roboY][roboX] = 1
			}
		}
	}

	count := 0
	for _, r := range visited {
		for _, c := range r {
			if c == 1 {
				count++
			}
		}
	}

	return count
}
