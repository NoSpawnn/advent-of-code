package adventOfCode.lib;

public interface Solver {
    public String getYearStr();

    public String getDayStr();

    public default String solve(String input) {
        Number part1Ans = this.part1(input);
        Number part2Ans = this.part2(input);

        return this.getYearStr() + " Day " + this.getDayStr() +
                ":\n  Part 1: " + part1Ans + "\n  Part 2: " + part2Ans;
    }

    public Number part1(String input);

    public Number part2(String input);
}
