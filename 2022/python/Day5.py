import os

dirname = os.path.dirname(__file__)
FILE = os.path.join(dirname, "./input/Day5.txt")

STACKS1 = {
    1: ["G", "D", "V", "Z", "J", "S", "B"],
    2: ["Z", "S", "M", "G", "V", "P"],
    3: ["C", "L", "B", "S", "W", "T", "Q", "F"],
    4: ["H", "J", "G", "W", "R", "V", "Q", "M"],
    5: ["C", "L", "S", "N", "F", "M", "D"],
    6: ["R", "G", "C", "D"],
    7: ["H", "G", "T", "R", "J", "D", "S", "Q"],
    8: ["P", "F", "V"],
    9: ["D", "R", "S", "T", "J"],
}

STACKS2 = {
    1: ["G", "D", "V", "Z", "J", "S", "B"],
    2: ["Z", "S", "M", "G", "V", "P"],
    3: ["C", "L", "B", "S", "W", "T", "Q", "F"],
    4: ["H", "J", "G", "W", "R", "V", "Q", "M"],
    5: ["C", "L", "S", "N", "F", "M", "D"],
    6: ["R", "G", "C", "D"],
    7: ["H", "G", "T", "R", "J", "D", "S", "Q"],
    8: ["P", "F", "V"],
    9: ["D", "R", "S", "T", "J"],
}


def read_data() -> list[tuple[str, str, str]]:
    with open(FILE, "r") as f:
        lines = f.readlines()

        moves: list[tuple[str, str, str]] = []

        for line in lines:
            words = line.strip().split(" ")

            move = int(words[1]), int(words[3]), int(words[5])
            moves.append(move)

        return moves


def do_moves1(moves: list[tuple[str, str, str]]) -> str:
    for move in moves:
        for m in range(move[0]):
            STACKS1[move[2]].append(STACKS1[move[1]].pop())

    return "".join(s[-1] for s in STACKS1.values())


def do_moves2(moves: list[tuple[str, str, str]]) -> str:
    for move in moves:
        orig_crate = STACKS2[move[1]]
        to_crate = STACKS2[move[2]]
        to_push = orig_crate[-move[0] :]

        for c in to_push:
            to_crate.append(c)
            orig_crate.pop()

        STACKS2[move[1]] = orig_crate
        STACKS2[move[2]] = to_crate

    return "".join(s[-1] for s in STACKS2.values())


if __name__ == "__main__":
    moves = read_data()
    result1 = do_moves1(moves=moves)
    print("Part 1 result:", result1)

    result2 = do_moves2(moves=moves)
    print("Part 2 result:", result2)
