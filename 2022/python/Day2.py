import os

dirname = os.path.dirname(__file__)
FILE = os.path.join(dirname, "./input/Day2.txt")

ACCEPTED_PLAYS = ["A", "B", "C", "X", "Y", "Z"]
PLAY_VALUES = {"X": 1, "Y": 2, "Z": 3}


def read_data() -> list[str]:
    """Read the calorie data from a text file.

    Raises:
        OSError: Raised if the file failes to open.

    Returns:
        list[str]: A list of the read lines, including blank ones.
    """

    try:
        with open(FILE, "r") as f:
            return f.readlines()
    except OSError as e:
        raise OSError(e)


def to_strat_pt1(lines: list[str]) -> list[tuple[chr, chr]]:
    """Generate strategy based on part 1:
        X = Rock, Y = Paper, Z = Scissors

    Args:
        lines (list[str]): Lines read from the input

    Raises:
        OverflowError: Raised if more than the expected arguments per line are found
        ValueError: Raised if an invalid value (not A,B,C,X,Y,Z) is found

    Returns:
        list[tuple[chr, chr]]: list of tuples of characters representing the strategy
    """

    moves = []
    for line in lines:
        try:
            turn = line.strip().split(" ")
            if len(turn) > 2:
                raise OverflowError(
                    f"Too many arguments found. Expected 2, found {len(turn)}."
                )
            elif (length := max(map(len, turn))) > 1:
                raise OverflowError(
                    f"Each item should be a single character. Found item with length {length}."
                )

            if turn[0] not in ACCEPTED_PLAYS:
                raise ValueError(
                    f"Invalid play found. Must be one from {ACCEPTED_PLAYS}, found '{turn[0]}.'"
                )
            elif turn[1] not in ACCEPTED_PLAYS:
                raise ValueError(
                    f"Invalid play found. Must be one from {ACCEPTED_PLAYS}, found '{turn[1]}.'"
                )

            moves.append(turn)

        except ValueError as e:
            raise ValueError(e)
        except OverflowError as e:
            raise OverflowError(e)

    return moves


def to_strat_pt2(lines: list[str]) -> list[tuple[chr, chr]]:
    """Parse lines into the part 2 strategy.
    X = Lose, Y = Draw, Z = Win.

    Args:
        lines (list[str]): Lines read from input

    Raises:
        OverflowError: Raised if more than the expected arguments per line are found
        ValueError: Raised if an invalid value (not A,B,C,X,Y,Z) is found

    Returns:
        list[tuple[chr, chr]]: list of tuples of characters representing the strategy
    """

    moves = []
    for line in lines:
        try:
            turn = line.strip().split(" ")
            if len(turn) > 2:
                raise OverflowError(
                    f"Too many arguments found. Expected 2, found {len(turn)}."
                )
            elif (length := max(map(len, turn))) > 1:
                raise OverflowError(
                    f"Each item should be a single character. Found item with length {length}."
                )

            if turn[1] == "X":  # Lose
                if turn[0] == "A":
                    turn[1] = "Z"
                elif turn[0] == "C":
                    turn[1] = "Y"

            elif turn[1] == "Y":  # Draw
                if turn[0] == "A":
                    turn[1] = "X"
                elif turn[0] == "C":
                    turn[1] = "Z"

            elif turn[1] == "Z":  # Win
                if turn[0] == "A":
                    turn[1] = "Y"
                elif turn[0] == "C":
                    turn[1] = "X"

            turn = tuple(turn)
            moves.append(turn)

        except ValueError as e:
            raise ValueError(e)
        except OverflowError as e:
            raise OverflowError(e)

    return moves


def play(moves: list[tuple[chr, chr]]) -> int:
    """Tally the given moves and return a score.

    Args:
        moves (list[tuple[chr, chr]]): The calculated moves.

    Returns:
        int: Tallied score.
    """
    
    total_score = 0

    for them, me in moves:
        total_score += PLAY_VALUES[me]

        if (  # Draw
            (them == "A" and me == "X")
            or (them == "B" and me == "Y")
            or (them == "C" and me == "Z")
        ):
            total_score += 3
        elif (  # I win
            (them == "A" and me == "Y")
            or (them == "B" and me == "Z")
            or (them == "C" and me == "X")
        ):
            total_score += 6

    return total_score


if __name__ == "__main__":
    try:
        lines = read_data()

        moves_1 = to_strat_pt1(lines=lines)
        final_score_1 = play(moves=moves_1)
        print("Part 1 score:", final_score_1)

        moves_2 = to_strat_pt2(lines=lines)
        final_score_2 = play(moves=moves_2)
        print("Part 2 score:", final_score_2)

    except Exception as e:
        print("Error: ", e)
