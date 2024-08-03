import os

from math import trunc
from typing import NamedTuple

dirname = os.path.dirname(__file__)
FILE = os.path.join(dirname, "./input/Day3.txt")


class Backpack(NamedTuple):
    """NamedTuple representing a backpack with two compartments.

    Attributes:
        front (str): Front compartment
        back (str): Back compartment
    """

    front: list[str]
    back: list[str]


def read_data_pt1() -> list[Backpack]:
    result = []
    with open(FILE, "r") as f:
        lines = f.readlines()

        for line in lines:
            line = line.strip()
            half = trunc(len(line) / 2)
            front = line[:half]
            back = line[half:]

            result.append(Backpack(front=front, back=back))

    return result


def read_data_pt2() -> list[tuple[str, str, str]]:
    result = []
    with open(FILE, "r") as f:
        lines = f.readlines()

        for i in range(0, len(lines), 3):
            group_lines = lines[i : i + 3]
            group_lines = [line.strip() for line in group_lines]

            group = tuple(line for line in group_lines)
            result.append(group)

    return result


def calc_priority_scores(backpacks: list[Backpack]) -> int:
    def find_shared(pack: Backpack) -> str:
        """Find shared characted between 3 backpacks.

        Args:
            pack (tuple[str, str, str]): Group of 3 bacpacks.

        Returns:
            str: Shared character.
        """

        for char in pack.front:
            if char in pack.back:
                return char

    score = 0

    for pack in backpacks:
        if char := find_shared(pack):
            if char.isupper():
                score += ord(char) - 38
            else:
                score += ord(char) - 96

    return score


def find_badges(groups: list[tuple[str, str, str]]) -> int:
    """Find badges, items shared betweeen all three backpacks.

    Args:
        groups (list[tuple[str, str, str]]): groups of 3 backpacks.

    Returns:
        int: The tallied score.
    """

    def find_shared(pack: tuple[str, str, str]) -> str:
        """Find shared characted between 3 backpacks.

        Args:
            pack (tuple[str, str, str]): Group of 3 bacpacks.

        Returns:
            str: Shared character.
        """

        for char in pack[0]:
            if char in pack[1] and char in pack[2]:
                return char

    score = 0

    for pack in groups:
        if char := find_shared(pack):
            if char.isupper():
                score += ord(char) - 38
            else:
                score += ord(char) - 96

    return score


if __name__ == "__main__":
    lines = read_data_pt1()
    priority_scores = calc_priority_scores(lines)
    print("Part 1 priority scores:", priority_scores)

    badges = read_data_pt2()
    badges_scores = find_badges(badges)
    print("   Part 2 badge scores:", badges_scores)
