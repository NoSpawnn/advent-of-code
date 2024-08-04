package adventOfCode.lib

interface Solver {
    val year: String
    val day: String

    fun solve(input: String) {
        val part1Ans = part1(input)
        val part2Ans = part2(input)

        println("${this.day} Day ${this.year}:\n  Part 1: $part1Ans\n  Part 2: $part2Ans")
    }

    fun part1(input: String): Number

    fun part2(input: String): Number
}
