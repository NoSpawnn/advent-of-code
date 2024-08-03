import os

dirname = os.path.dirname(__file__)
FILE = os.path.join(dirname, "./input/Day6.txt")


def read_data() -> str:
    with open(FILE, "r") as f:
        return f.read()


def find_marker_char(input_str: str, distinct: int) -> int:
    last_n = input_str[:distinct]

    for idx, char in enumerate(input_str[distinct:]):
        if len(set(last_n)) == len(last_n):
            return idx + distinct

        last_n = last_n[1:]
        last_n += char
    
    raise ValueError("No marker found.")


if __name__ == "__main__":
    packet = read_data()
    start_of_packet = find_marker_char(packet, 4)
    start_of_message = find_marker_char(packet, 14)

    print(" Start of packet marker (Part 1):", start_of_packet)
    print("Start of message marker (Part 2):", start_of_message)
