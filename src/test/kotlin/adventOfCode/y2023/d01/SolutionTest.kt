package adventOfCode.y2023.d01

import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Test

class SolutionTest {

    private val part1TestInput = """
        1abc2
        pqr3stu8vwx
        a1b2c3d4e5f
        treb7uchet
    """.trimIndent()
    private val part1Expected = 142

    private val part2TestInput = """
        two1nine
        eightwothree
        abcone2threexyz
        xtwone3four
        4nineeightseven2
        zoneight234
        7pqrstsixteen
    """.trimIndent()
    private val part2Expected = 281

    @Test
    fun part1() {
        assertEquals(Solution.part1(part1TestInput), part1Expected)
    }

    @Test
    fun part2() {
        assertEquals(Solution.part2(part2TestInput), part2Expected)
    }
}