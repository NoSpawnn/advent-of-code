use std::{collections::HashMap, fs};

const FILEPATH: &str = "src/input/Day 5 input.txt";

#[derive(Debug)]
struct Move {
    count: u32,
    from: u32,
    to: u32,
}

fn main() {
    let mut stacks: HashMap<u32, Vec<char>> = HashMap::new();
    stacks.insert(1, vec!['G', 'D', 'V', 'Z', 'J', 'S', 'B']);
    stacks.insert(2, vec!['Z', 'S', 'M', 'G', 'V', 'P']);
    stacks.insert(3, vec!['C', 'L', 'B', 'S', 'W', 'T', 'Q', 'F']);
    stacks.insert(4, vec!['H', 'J', 'G', 'W', 'R', 'V', 'Q', 'M']);
    stacks.insert(5, vec!['C', 'L', 'S', 'N', 'F', 'M', 'D']);
    stacks.insert(6, vec!['R', 'G', 'C', 'D']);
    stacks.insert(7, vec!['H', 'G', 'T', 'R', 'J', 'D', 'S', 'Q']);
    stacks.insert(8, vec!['P', 'F', 'V']);
    stacks.insert(9, vec!['D', 'R', 'S', 'T', 'J']);

    let moves = read_moves(FILEPATH);
    let done = do_moves(stacks, moves);

    for key in 1..=done.len() as u32 {
        print!("{}", done[&key].last().unwrap());
    }
    println!();
}

fn read_moves(filepath: &str) -> Vec<Move> {
    let mut data: String = String::new();
    match fs::read_to_string(filepath) {
        Ok(s) => data = s,
        Err(e) => eprintln!("{e}"),
    };

    let mut moves: Vec<Move> = Vec::new();

    for line in data.lines() {
        let parsed_line: Vec<&str> = line.split(' ').collect();

        let count = parsed_line[1].parse().unwrap();
        let from = parsed_line[3].parse().unwrap();
        let to = parsed_line[5].parse().unwrap();

        moves.push(Move { count, from, to });
    }

    moves
}

fn do_moves(mut stacks: HashMap<u32, Vec<char>>, moves: Vec<Move>) -> HashMap<u32, Vec<char>> {
    for m in moves {
        let mut to = stacks.get(&m.to).unwrap().clone();
        let mut from = stacks.get(&m.from).unwrap().clone();
        let next_push = &from[from.len() - m.count as usize..].to_owned();

        for c in next_push {
            to.push(*c);
            from.pop();
        }

        stacks.insert(m.to, to);
        stacks.insert(m.from, from);
    }
    // println!("{stacks:?}");
    stacks
}
