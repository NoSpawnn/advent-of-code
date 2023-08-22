use std::fs;

#[allow(dead_code)]
fn main() {
    let filepath: &str = "src/input/Day 1 input.txt";
    let elves: Result<Vec<u32>, String> = calc_calories(filepath);
    println!("{elves:?}")
}

pub fn calc_calories(filepath: &str) -> Result<Vec<u32>, String> {
    let data: String = match fs::read_to_string(filepath) {
        Ok(lines) => lines,
        Err(e) => return Err(e.to_string()),
    };

    let mut elves: Vec<u32> = Vec::new();

    let mut elf: usize = 0_usize;
    for line in data.lines() {
        let this_cal: u32 = {
            match line.parse::<u32>() {
                Ok(c) => c,
                Err(_) => {
                    elf += 1;
                    continue;
                }
            }
        };

        if line != "" {
            match elves.get_mut(elf) {
                Some(calories) => *calories += this_cal,
                None => elves.push(this_cal),
            }
        }
    }

    elves.sort();
    // println!("{elves:?}");
    Ok(elves)
}
