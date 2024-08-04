package runner

import adventOfCode.lib.Solver
import runner.GetInput.getInputPath
import java.io.File
import java.nio.file.Files

object SolverMap {
    private val solvers: Map<String, Solver> = hashMapOf(
        // 2015
        "2015/01" to adventOfCode.y2015.d01.Solution(),
        "2015/02" to adventOfCode.y2015.d02.Solution(),

        // 2023
        "2023/01" to adventOfCode.y2023.d01.Solution()
    )

    fun getSolver(name: String): Solver? {
        return solvers[name]
    }

    fun solveAll() {
        solvers.toList().sortedBy { it.first }.forEach { (name, solver) ->
            val (year, day) = name.split("/");
            val inputFilePath = getInputPath(year, day)

            if (!Files.exists(inputFilePath)) return@forEach

            val f = File(inputFilePath.toUri())
            val input = f.readText()

            solver.solve(input);
        }
    }
}
