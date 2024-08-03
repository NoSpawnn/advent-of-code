package com.nospawnn.adventOfCode.lib;

import java.util.HashMap;
import java.util.Map;

public class SolverMap {
    private static final Map<String, Solver> SOLVERS = new HashMap<>();

    static {
        SOLVERS.put("2023/01", new com.nospawnn.adventOfCode.y2023.Day01());
    }

    public static Solver getSolver(String name) {
        return SOLVERS.get(name);
    }
}
