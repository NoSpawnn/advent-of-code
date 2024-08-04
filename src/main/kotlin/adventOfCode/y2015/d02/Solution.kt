package adventOfCode.y2015.d02

import adventOfCode.lib.Solver

class Solution : Solver {
    override val year: String = "2015"
    override val day: String = "02"

    override fun part1(input: String): Int = boxes(input).sumOf { sides ->
        2 * sides[0] * sides[1] + 2 * sides[1] * sides[2] + 2 * sides[0] * sides[2] + sides[0] * sides[1]
    }

    override fun part2(input: String): Int = boxes(input).sumOf { sides ->
        sides[0] * 2 + sides[1] * 2 + sides[0] * sides[1] * sides[2]
    }

    private fun boxes(input: String) = sequence {
        input.split('\n').forEach { line ->
            if (line.isBlank()) return@forEach

            val sides = line.split('x')
            yield(sides.map { it.trim().toInt() }.sorted())
        }
    }
}
