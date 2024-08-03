package adventOfCode.lib;

import java.util.HashMap;
import java.util.Map;

public class SolverMap {
    private static final Map<String, Solver> SOLVERS = new HashMap<>();

    static {
        SOLVERS.put("2023/01", new adventOfCode.y2023.Day01());
    }

    public static Solver getSolver(String name) {
        return SOLVERS.get(name);
    }
}
