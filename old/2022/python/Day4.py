import os

dirname = os.path.dirname(__file__)
FILE = os.path.join(dirname, "./input/Day4.txt")


def read_data() -> list[tuple[range, range]]:
    with open(FILE, "r") as f:
        lines = f.readlines()

        ranges = []

        for line in lines:
            pair = line.split(",")
            this_ranges = []
            for elf in pair:
                start, end = elf.split("-")
                r = range(int(start), int(end))
                this_ranges.append(r)
            ranges.append(this_ranges)

        return ranges


def find_overlaps(ranges: list[tuple[range, range]], only_total: bool = False) -> int:
    """Find partial or complete overlaps between ranges.

    Args:
        ranges (list[tuple[range, range]]): List of tuples of ranges to compare.
        only_total (bool, optional): Flag for whether to find all overlaps or only complete overlaps. Defaults to all.

    Returns:
        int: Number of overlaps
    """
    overlaps = 0

    if only_total:
        for elf1, elf2 in ranges:
            if (elf1.start <= elf2.start and elf1.stop >= elf2.stop) or (
                elf2.start <= elf1.start and elf2.stop >= elf1.stop
            ):
                overlaps += 1
    else:
        for elf1, elf2 in ranges:
            if (elf1.start <= elf2.start <= elf1.stop) or (
                elf2.start <= elf1.start <= elf2.stop
            ):
                overlaps += 1

    return overlaps


if __name__ == "__main__":
    ranges = read_data()
    total_overlaps = find_overlaps(ranges=ranges, only_total=True)
    print("  Total overlaps (Part 1):", total_overlaps)

    partial_overlaps = find_overlaps(ranges=ranges, only_total=False)
    print("Partial overlaps (Part 2):", partial_overlaps)
