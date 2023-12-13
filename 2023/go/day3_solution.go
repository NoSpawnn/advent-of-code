package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"unicode"
)

const LINE_LEN = 10

func main() {
	file, err := os.Open("day3_input.txt")
	defer file.Close()

	if err != nil {
		log.Fatal(err)
	}

	var arr []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		arr = append(arr, scanner.Text())
	}

	for line_idx, line := range arr {
		numbers := find_digits(line)

		for _, a := range numbers {
			start, end := a[0], a[1]

		}
	}
}

func find_digits(line string) [][2]int {
	var arr [][2]int

	for idx := 0; idx < LINE_LEN; idx++ {
		if unicode.IsDigit(rune(line[idx])) {
			first_digit_idx := idx
			last_digit_idx := idx + 1

			if last_digit_idx == LINE_LEN {
				arr = append(arr, [2]int{first_digit_idx, last_digit_idx})
				break
			}

			for unicode.IsDigit(rune(line[last_digit_idx])) {
				last_digit_idx++
			}

			fmt.Printf("%d : %d - ", first_digit_idx, last_digit_idx)
			arr = append(arr, [2]int{first_digit_idx, last_digit_idx})
			idx = last_digit_idx
		}
	}

	return arr
}
