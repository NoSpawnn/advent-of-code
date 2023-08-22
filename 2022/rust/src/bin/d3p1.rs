use std::fs;

const FILEPATH: &str = "src/input/Day 3 input.txt";

#[allow(dead_code)]
fn main() {
    let items = get_items_per_compartment(FILEPATH);
    let shared_items = get_shared_items(&items);
    let priorities_sum = sum_shared_items(&shared_items);
    println!("Sum of shared item priorities: {priorities_sum}");
}

fn get_items_per_compartment(filepath: &str) -> Vec<Vec<String>> {
    let mut items_per_compartment: Vec<Vec<String>> = Vec::new();

    let mut data: String = String::new();
    match fs::read_to_string(filepath) {
        Ok(s) => {
            data = s;
        }
        Err(e) => eprintln!("{e}"),
    };

    for line in data.lines() {
        let compartments = line.split_at(line.len() / 2);
        items_per_compartment.push(vec![compartments.0.to_owned(), compartments.1.to_owned()]);
    }

    items_per_compartment
}

fn get_shared_items(rucksacks: &Vec<Vec<String>>) -> Vec<char> {
    let mut shared_items = Vec::new();

    'rucksack_loop: for rucksack in rucksacks {
        for char in rucksack[0].chars() {
            if rucksack[1].contains(char) {
                shared_items.push(char);
                continue 'rucksack_loop;
            }
        }
    }

    shared_items
}

pub fn sum_shared_items(items: &Vec<char>) -> u32 {
    let mut total = 0_u32;

    for c in items {
        if c.is_ascii_uppercase() {
            total += (*c as u32) - 38
        } else {
            total += (*c as u32) - 96
        }
    }

    total
}
