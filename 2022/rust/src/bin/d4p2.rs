use std::ops::RangeInclusive;

mod d4p1;

const FILEPATH: &str = "src/input/Day 4 input.txt";

fn main() {
    let pairs: Vec<(RangeInclusive<i32>, RangeInclusive<i32>)> = d4p1::get_pairs(FILEPATH);
    let partial_overlaps = find_partial_overlaps(&pairs);

    println!("Partial overlaps: {partial_overlaps}");
}

fn find_partial_overlaps(pairs: &Vec<(RangeInclusive<i32>, RangeInclusive<i32>)>) -> i32 {
    let mut overlaps = 0;

    for (elf1, elf2) in pairs {
        if elf1.contains(elf2.start()) || elf1.contains(elf2.end()) {
            // Range 1 contains range 2
            overlaps += 1;
        } else if elf2.contains(elf1.start()) || elf2.contains(elf1.end()) {
            // Range 2 contains range 1
            overlaps += 1;
        }
    }

    overlaps
}
