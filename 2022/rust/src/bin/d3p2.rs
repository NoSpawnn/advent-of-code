use std::fs;

mod d3p1;
use d3p1::sum_shared_items;

const FILEPATH: &str = "src/input/Day 3 input.txt";

fn main() {
    let items = get_items_per_group(FILEPATH);
    let badge_items = get_badge_item(&items);
    let badge_item_sum = sum_shared_items(&badge_items);
    println!("Sum of badge items: {badge_item_sum}");
}

fn get_items_per_group(filepath: &str) -> Vec<Vec<String>> {
    let mut data: String = String::new();
    match fs::read_to_string(filepath) {
        Ok(s) => {
            data = s;
        }
        Err(e) => eprintln!("{e}"),
    };

    let mut line_counter = 0;
    let lines_per_group = 3;
    let mut items_per_group: Vec<Vec<String>> = Vec::new();
    let mut group: Vec<String> = Vec::new();

    for line in data.lines() {
        group.push(line.to_owned());
        line_counter += 1;

        if line_counter == lines_per_group {
            items_per_group.push(group.clone());
            group.clear();
            line_counter = 0;
        }
    }

    items_per_group
}

fn get_badge_item(groups: &Vec<Vec<String>>) -> Vec<char> {
    let mut badge_items: Vec<char> = Vec::new();

    for group in groups {
        for char in group[0].chars() {
            if group[1].contains(char) && group[2].contains(char) {
                badge_items.push(char);
                break;
            }
        }
    }

    badge_items
}
