package adventOfCode.y2015.d01

import adventOfCode.lib.Solver

data class Floor(val level: Int, val idx: Int)

class Solution : Solver {
    override val year: String = "2015"
    override val day: String = "01"

    override fun part1(input: String): Int = floors(input).last().level

    override fun part2(input: String): Int = floors(input).find { floor -> floor.level == -1 }!!.idx + 1

    private fun floors(input: String) = sequence {
        var level = 0

        input.forEachIndexed { idx, char ->
            level += if (char == '(') 1 else -1
            yield(Floor(level, idx))
        }
    }
}
