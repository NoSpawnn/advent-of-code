package adventOfCode.y2023;

import adventOfCode.lib.Solver;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.regex.MatchResult;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Day01 implements Solver {
    @Override
    public String getYearStr() {
        return "2023";
    }

    @Override
    public String getDayStr() {
        return "01";
    }

    @Override
    public Number part1(String input) {
        return parseLines(input, Pattern.compile("\\d"));
    }

    @Override
    public Number part2(String input) {
        return parseLines(input, Pattern.compile("(?=(\\d|one|two|three|four|five|six|seven|eight|nine))"));
    }

    private int parseLines(String input, Pattern pattern) {
        return input.lines().filter(l -> !l.isBlank()).mapToInt(l -> {
            Matcher m = pattern.matcher(l);
            List<MatchResult> matchResults = new ArrayList<>(m.results().toList());

            String first = matchResults.stream().findFirst().orElse(matchResults.get(1)).group(0);

            Collections.reverse(matchResults);

            String last = matchResults.stream().findFirst().orElse(matchResults.get(1)).group(0);

            return convertMatch(first) * 10 + convertMatch(last);
        }).sum();
    }

    private int convertMatch(String match) {
        return switch (match) {
            case "one" -> 1;
            case "two" -> 2;
            case "three" -> 3;
            case "four" -> 4;
            case "five" -> 5;
            case "six" -> 6;
            case "seven" -> 7;
            case "eight" -> 8;
            case "nine" -> 9;
            default -> Integer.parseInt(match);
        };
    }

}
