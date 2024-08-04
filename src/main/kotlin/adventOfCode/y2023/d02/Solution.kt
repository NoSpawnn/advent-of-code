package adventOfCode.y2023.d02

import adventOfCode.lib.Solver

data class Game(val id: Int, val red: Int, val green: Int, val blue: Int)

object Solution : Solver {
    override val year: String = "2023"
    override val day: String = "02"

    override fun part1(input: String): Number =
        input.lines().filter { it.isNotBlank() }.sumOf { line ->
            val game = gameFrom(line)
            if (game.red <= 12 && game.green <= 14 && game.blue <= 14) game.id else 0
        }


    override fun part2(input: String): Number =
        input.lines().filter { it.isNotBlank() }.sumOf { line ->
            val game = gameFrom(line)
            game.red * game.green * game.blue
        }


    private fun gameFrom(input: String) = Game(
        getInts(input, "Game (\\d+)").first(),
        getInts(input, "(\\d+) red").maxOrNull()!!,
        getInts(input, "(\\d+) green").maxOrNull()!!,
        getInts(input, "(\\d+) blue").maxOrNull()!!
    )

    private fun getInts(input: String, pattern: String) = sequence {
        Regex(pattern).findAll(input).forEach { match ->
            yield(Integer.parseInt(match.groups[1]!!.value))
        }
    }
}
