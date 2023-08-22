use std::fs;
use std::ops::RangeInclusive;

const FILEPATH: &str = "src/input/Day 4 input.txt";

#[allow(dead_code)]
fn main() {
    let pairs: Vec<(RangeInclusive<i32>, RangeInclusive<i32>)> = get_pairs(FILEPATH);
    let complete_overlaps = find_complete_overlaps(&pairs);
    println!("Complete overlaps: {complete_overlaps}");
}

pub fn get_pairs(filepath: &str) -> Vec<(RangeInclusive<i32>, RangeInclusive<i32>)> {
    let mut data: String = String::new();
    match fs::read_to_string(filepath) {
        Ok(s) => {
            data = s;
        }
        Err(e) => eprintln!("{e}"),
    };

    let mut pairs: Vec<(RangeInclusive<i32>, RangeInclusive<i32>)> = Vec::new();

    for line in data.lines() {
        let pair_of_elves: Vec<&str> = line.split(',').collect();

        let (elf1_range, elf2_range) = {
            let elf1: Vec<&str> = pair_of_elves[0].split('-').collect();
            let elf2: Vec<&str> = pair_of_elves[1].split('-').collect();

            let elf1_r: RangeInclusive<i32> = elf1[0].parse().unwrap()..=elf1[1].parse().unwrap();
            let elf2_r: RangeInclusive<i32> = elf2[0].parse().unwrap()..=elf2[1].parse().unwrap();

            (elf1_r, elf2_r)
        };

        pairs.push((elf1_range, elf2_range));
    }

    pairs
}

fn find_complete_overlaps(pairs: &Vec<(RangeInclusive<i32>, RangeInclusive<i32>)>) -> i32 {
    let mut overlaps = 0;

    for (elf1, elf2) in pairs {
        if elf1.contains(elf2.start()) && elf1.contains(elf2.end()) {
            // Range 1 contains range 2
            overlaps += 1;
        } else if elf2.contains(elf1.start()) && elf2.contains(elf1.end()) {
            // Range 2 contains range 1
            overlaps += 1;
        }
    }

    overlaps
}
