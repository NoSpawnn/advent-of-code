use std::cmp::Ordering;
use std::fs;

#[derive(PartialEq, PartialOrd, Eq, Debug)]
pub enum RPS {
    ROCK,
    PAPER,
    SCISSORS,
}

impl Ord for RPS {
    fn cmp(&self, other: &Self) -> Ordering {
        if self == other {
            return Ordering::Equal;
        }

        match self {
            RPS::ROCK => match other {
                RPS::PAPER => Ordering::Less,
                _ => Ordering::Greater,
            },
            RPS::PAPER => match other {
                RPS::SCISSORS => Ordering::Less,
                _ => Ordering::Greater,
            },
            RPS::SCISSORS => match other {
                RPS::ROCK => Ordering::Less,
                _ => Ordering::Greater,
            },
        }
    }
}

#[allow(dead_code)]
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
            "A" | "X" => RPS::ROCK,
            "B" | "Y" => RPS::PAPER,
            "C" | "Z" => RPS::SCISSORS,
            &_ => panic!("Values in strategy need to be A, B, C or X, Y, Z"),
        });
        strategy[1].push(match vals[1] {
            "A" | "X" => RPS::ROCK,
            "B" | "Y" => RPS::PAPER,
            "C" | "Z" => RPS::SCISSORS,
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
