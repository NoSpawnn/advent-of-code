import os

dirname = os.path.dirname(__file__)
FILE = os.path.join(dirname, "./input/Day1.txt")


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


def calc_calories(lines: list[str]) -> list[int]:
    """Sum the total calories for each elf from the lines of a text file. Each elf is separated by a blank line.

    Args:
        lines (list[str]): Lines of numbers read from text file.

    Raises:
        ValueError: Raised if a line fails to be parsed into an int.

    Returns:
        list[int]: List of calories carried by each elf in ascending order.
    """
    elf_calorie_totals = []

    total = 0
    for line in lines:
        if line != "\n":
            try:
                this_cal = int(line)
                total += this_cal

            except ValueError as e:
                raise ValueError(e)

        else:
            elf_calorie_totals.append(total)
            total = 0

    elf_calorie_totals.sort()
    return elf_calorie_totals


if __name__ == "__main__":
    try:
        lines = read_data()
        calories = calc_calories(lines=lines)

        # Part 1
        print(f"    Most calories carried by an elf: {calories[-1]}")

        # Part 2
        print(f"Calories carried by top three elves: {sum(calories[-3:])}")

    except ValueError as e:
        print("ValueError: ", e)
    except OSError as e:
        print("OSError: ", e)
