package y2023.d03

import lib.Solver
import kotlin.math.abs

data class Part(val text: String, val row: Int, val col: Int) {
    val int = text.toIntOrNull() ?: 0
}

object Solution : Solver {
    override val year: String = "2023"
    override val day: String = "03"

    override fun part1(input: String): Number {
        val lines = input.lines()
        val numbers = parse(lines, Regex("\\d+"))
        val symbols = parse(lines, Regex("[^.0-9]"))

        return numbers.filter { num -> symbols.any { sym -> areAdjacent(num, sym) } }.sumOf { it.int }
    }

    override fun part2(input: String): Number {
        val lines = input.lines()
        val numbers = parse(lines, Regex("\\d+"))
        val gears = parse(lines, Regex("\\*"))

        return gears.sumOf { gear ->
            numbers.filter { num -> areAdjacent(num, gear) }.takeIf { neighbours -> neighbours.size == 2 }
                ?.let { neighbours -> neighbours.first().int * neighbours.last().int } ?: 0
        }
    }

    private fun areAdjacent(p1: Part, p2: Part): Boolean =
        abs(p1.row - p2.row) <= 1 &&
                p1.col <= p2.col + p2.text.length &&
                p2.col <= p1.col + p1.text.length

    private fun parse(rows: List<String>, regex: Regex): List<Part> =
        rows.filter { it.isNotBlank() }
            .flatMapIndexed { idx, row ->
                regex.findAll(row).map { match -> Part(match.value, idx, match.range.first) }
            }
}
