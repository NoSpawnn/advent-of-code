package adventOfCode.y2023.d02

import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Test


class SolutionTest {
    private val testInput = """
        Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
        Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
        Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
        Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
        Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
    """.trimIndent()

    private val part1Expected = 8
    private val part2Expected = 2286

    @Test
    fun part1() {
        assertEquals(Solution.part1(testInput), part1Expected)
    }

    @Test
    fun part2() {
        assertEquals(Solution.part2(testInput), part2Expected)
    }
}