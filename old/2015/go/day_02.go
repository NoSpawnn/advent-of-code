package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"slices"
	"strconv"
	"strings"
)

type Box struct {
	l, w, h int
}

func (b *Box) area() int {
	return (2 * b.l * b.w) + (2 * b.w * b.h) + (2 * b.h * b.l)
}

func (b *Box) smallestFace() int {
	return min(b.l*b.w, b.l*b.h, b.w*b.h)
}

func (b *Box) minPerimiter() int {
	dimensions := []int{b.l, b.w, b.h}
	slices.Sort(dimensions)

	return dimensions[0]*2 + dimensions[1]*2
}

func (b *Box) cubicFtVol() int {
	return b.l * b.w * b.h
}

func parseBox(s string) *Box {
	nums := strings.SplitN(s, "x", 3)

	l, _ := strconv.Atoi(nums[0])
	w, _ := strconv.Atoi(nums[1])
	h, _ := strconv.Atoi(nums[2])

	return &Box{l: l, h: h, w: w}
}

func main() {
	day02()
}

func day02() {
	lines, err := readLinesToArray("input.txt")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(day02Part1(lines))
	fmt.Println(day02Part2(lines))

	// return Answer{part1: int32(day02Part1(lines)), part2: int32(day02Part2(lines))}
}

func day02Part1(input []string) int {
	total := 0

	for _, line := range input {
		b := parseBox(line)
		total += b.area() + b.smallestFace()
	}

	return total
}

func day02Part2(input []string) int {
	total := 0

	for _, line := range input {
		b := parseBox(line)
		total += b.cubicFtVol() + b.minPerimiter()
	}

	return total
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
