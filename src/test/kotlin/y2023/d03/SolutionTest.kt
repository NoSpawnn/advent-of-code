package y2023.d03

import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Test

class SolutionTest {
    private val testInput = """
        467..114..
        ...*......
        ..35..633.
        ......#...
        617*......
        .....+.58.
        ..592.....
        ......755.
        ...$.*....
        .664.598..
    """.trimIndent()

    private val part1Expected = 4361
    private val part2Expected = 467835

    @Test
    fun part1() {
        assertEquals(Solution.part1(testInput), part1Expected)
    }

    @Test
    fun part2() {
        assertEquals(Solution.part2(testInput), part2Expected)
    }
}