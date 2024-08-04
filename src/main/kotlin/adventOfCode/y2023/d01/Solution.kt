package adventOfCode.y2023.d01

import adventOfCode.lib.Solver

object Solution : Solver {
    override val year: String = "2023"
    override val day: String = "01"

    override fun part1(input: String): Int =
        solve(input, Regex("\\d"))


    override fun part2(input: String): Int =
        solve(input, Regex("(?=(\\d|one|two|three|four|five|six|seven|eight|nine))"))


    private fun solve(input: String, regex: Regex): Int =
        input.lines().filter { it.isNotBlank() }.sumOf { line ->
            val matches = regex.findAll(line).toList()

            // Takes into account whether the regex is wrapped in a group or not
            val first = matches.first().groupValues.getOrElse(1) { matches.first().groupValues[0] }
            val last = matches.last().groupValues.getOrElse(1) { matches.last().groupValues[0] }
            convertMatch(first) * 10 + convertMatch(last)
        }


    private fun convertMatch(match: String): Int =
        when (match) {
            "one" -> 1
            "two" -> 2
            "three" -> 3
            "four" -> 4
            "five" -> 5
            "six" -> 6
            "seven" -> 7
            "eight" -> 8
            "nine" -> 9
            else -> match.toInt()
        }

}

