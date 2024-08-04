package y2015.d01

import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Test

class SolutionTest {
    private val part1TestInputs = mapOf(
        "(())" to 0, "()()" to 0,
        "(((" to 3, "(()(()(" to 3,
        "())" to -1, "))(" to -1,
        ")))" to -3, ")())())" to -3
    )

    private val part2TestInputs = mapOf(
        ")" to 1, "()())" to 5
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