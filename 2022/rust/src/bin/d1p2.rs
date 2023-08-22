mod d1p1;

use d1p1::calc_calories;

#[allow(dead_code)]
fn main() {
    let filepath = "src/input/Day 1 input.txt";
    let calories: Result<Vec<u32>, String> = calc_calories(filepath);

    match calories {
        Ok(c) => {
            let top_three: Result<u32, String> = top_three_elves(&c);
            println!("{top_three:?}");
        }
        Err(e) => eprintln!("{e}"),
    }
}

fn top_three_elves(calories_vec: &Vec<u32>) -> Result<u32, String> {
    if calories_vec.len() < 3 {
        return Err("Must be a `Vec<u32>` with at least three values".to_string());
    } else if calories_vec.len() == 3 {
        return Ok(calories_vec[1] + calories_vec[2] + calories_vec[3]);
    } else {
        let total = {
            let three_index = calories_vec.len() - 3;
            let three = &calories_vec[three_index..];
            println!("{three:?}");
            three[0] + three[1] + three[2]
        };
        return Ok(total);
    }
}
