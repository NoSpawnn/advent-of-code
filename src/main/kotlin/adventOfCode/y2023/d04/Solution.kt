package adventOfCode.y2023.d04

import adventOfCode.lib.Solver
import kotlin.math.pow

data class Card(val matches: Int)

object Solution : Solver {
    override val year: String = "2023"
    override val day: String = "04"

    override fun part1(input: String): Number =
        input.lines().filter { it.isNotBlank() }.sumOf { line ->
            parseCard(line).takeIf { card -> card.matches > 0 }
                ?.let { card -> (2.0).pow(card.matches - 1) } ?: 0.0
        }.toInt()


    override fun part2(input: String): Number {
        val cards = input.lines().filter { it.isNotBlank() }.map { line -> parseCard(line) }
        val cardCounts = cards.map { 1 }.toMutableList();

        cards.forEachIndexed { idx, card ->
            for (i in 0..<card.matches) {
                cardCounts[idx + i + 1] += cardCounts[idx]
            }
        }

        return cardCounts.sum()
    }

    private fun parseCard(line: String): Card {
        val (_, lstr, rstr) = line.split(":", "|")

        // Woah, sets? Such performance!
        val lnums = Regex("\\d+").findAll(lstr).map { it.groupValues.first().toInt() }.toSet()
        val rnums = Regex("\\d+").findAll(rstr).map { it.groupValues.first().toInt() }.toSet()

        return Card(lnums.intersect(rnums).count())
    }

}