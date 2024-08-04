package adventOfCode.lib

object SolverMap {
    private val solvers: Map<String, Solver> = hashMapOf(
        "2015/01" to adventOfCode.y2015.d01.Solution(),
        "2015/02" to adventOfCode.y2015.d02.Solution(),
        "2023/01" to adventOfCode.y2023.d01.Solution()
    )

    fun getSolver(name: String): Solver? {
        return solvers[name]
    }
}
