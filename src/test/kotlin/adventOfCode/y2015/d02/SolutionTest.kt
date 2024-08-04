package adventOfCode.y2015.d02

import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Test

class SolutionTest {
    private val part1TestInputs = mapOf(
        "2x3x4" to 58, "1x1x10" to 43
    )

    private val part2TestInputs = mapOf(
        "2x3x4" to 34, "1x1x10" to 14
    )

    @Test
    fun part1() {
        for ((input, expected) in part1TestInputs) {
            assertEquals(Solution.part1(input), expected)
        }
    }

    @Test
    fun part2() {
        for ((input, expected) in part2TestInputs) {
            assertEquals(Solution.part2(input), expected)
        }
    }
}