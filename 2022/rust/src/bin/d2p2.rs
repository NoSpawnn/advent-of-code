use std::cmp::Ordering;
use std::fs;

mod d2p1;
use d2p1::RPS;

fn main() {
    let filepath = "src/input/Day 2 input.txt";
    match read_strategy(filepath) {
        Ok(s) => {
            let strategy = s;
            let score: u32 = calc_score(strategy);
            println!("{:}", score);
        }
        Err(e) => eprintln!("{:}", e),
    };
}

fn read_strategy(filepath: &str) -> Result<Vec<Vec<RPS>>, String> {
    let data: String = match fs::read_to_string(filepath) {
        Ok(lines) => lines,
        Err(_) => return Err("Failed to read the file".to_string()),
    };

    let mut strategy: Vec<Vec<RPS>> = vec![vec![], vec![]];
    for line in data.lines() {
        let vals: Vec<_> = line.split_ascii_whitespace().collect();
        strategy[0].push(match vals[0] {
            "A" => RPS::ROCK,
            "B" => RPS::PAPER,
            "C" => RPS::SCISSORS,
            &_ => panic!("Values in strategy need to be A, B, C or X, Y, Z"),
        });

        strategy[1].push(match vals[1] {
            "X" => match vals[0] {
                "A" => RPS::SCISSORS,
                "B" => RPS::ROCK,
                "C" => RPS::PAPER,
                &_ => panic!("What the hell happened?"),
            },
            "Y" => match vals[0] {
                "A" => RPS::ROCK,
                "B" => RPS::PAPER,
                "C" => RPS::SCISSORS,
                &_ => panic!("Values in strategy need to be A, B, C or X, Y, Z"),
            },
            "Z" => match vals[0] {
                "A" => RPS::PAPER,
                "B" => RPS::SCISSORS,
                "C" => RPS::ROCK,
                &_ => panic!("What the hell happened?"),
            },
            &_ => panic!("Values in strategy need to be A, B, C or X, Y, Z"),
        });
    }
    Ok(strategy)
}

fn calc_score(strategy: Vec<Vec<RPS>>) -> u32 {
    let mut total_score = 0;

    for round in 0..strategy[0].len() {
        let them = &strategy[0][round];
        let me = &strategy[1][round];

        match me.cmp(them) {
            Ordering::Equal => total_score += 3,
            Ordering::Greater => total_score += 6,
            Ordering::Less => total_score += 0,
        }

        total_score += {
            match me {
                RPS::ROCK => 1,
                RPS::PAPER => 2,
                RPS::SCISSORS => 3,
            }
        }
    }

    total_score
}
