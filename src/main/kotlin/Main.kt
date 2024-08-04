import adventOfCode.lib.Solver
import runner.GetInput
import runner.SolverMap
import java.io.IOException
import java.nio.file.Files

fun main(args: Array<String>) {
    when (args[0]) {
        "usage" -> printUsage()
        "download" -> {
            val dateParts = args[1].split("/")

            if (dateParts.size != 2) {
                println("Usage: download -Pdate=YYYY/DD")
                return
            }

            try {
                GetInput.download(dateParts[0], dateParts[1])
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

        "solve" -> {
            if (args[1] == "all") {
                SolverMap.solveAll()
                return
            }

            val solver: Solver? = SolverMap.getSolver(args[1])
            if (solver == null) {
                println("Invalid date ${args[1]}")
                return
            }

            val dateParts = args[1].split("/")
            if (dateParts.size != 2) {
                println("Usage: solve -Pdate=YYYY/DD")
                return
            }

            try {
                val input = Files.readString(GetInput.getInputPath(dateParts[0], dateParts[1]))
                solver.solve(input)
            } catch (e: IOException) {
                throw RuntimeException(e)
            }
        }

        else -> printUsage()
    }
}

private fun printUsage() {
    println(
        """
        Usage:
            gradle <solve|download|usage>
        """.trimIndent()
    )
}
