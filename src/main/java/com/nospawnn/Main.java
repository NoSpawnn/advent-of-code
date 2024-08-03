package com.nospawnn;

import com.nospawnn.adventOfCode.lib.GetInput;
import com.nospawnn.adventOfCode.lib.Solver;
import com.nospawnn.adventOfCode.lib.SolverMap;

public class Main {
    public static void main(String[] args) throws Exception {
        Solver solver = SolverMap.getSolver(args[0]);

        String[] parts = args[0].split("/");
        assert parts.length == 2;

        GetInput.download(parts[0], parts[1]);
    }
}