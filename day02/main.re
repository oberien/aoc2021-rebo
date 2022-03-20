enum Command {
    Forward(int),
    Down(int),
    Up(int),
}
struct State {
    depth: int,
    horizontal: int,
    aim: int,
}

//let input = File::read_to_string("sample.txt");
let input = File::read_to_string("input.txt");
let input = input.unwrap();
let lines = input.split("\n");

let mut commands = List::new();
for line in lines {
    if line != "" {
        let parts = line.split(" ");
        let cmd = parts.get(0).unwrap();
        let num = parts.get(1).unwrap().parse_int().unwrap();
        let command = match cmd {
            "forward" => Command::Forward(num),
            "down" => Command::Down(num),
            "up" => Command::Up(num),
            _ => panic(f"unknow command {line}"),
        };
        commands.push(command);
    }
}

let state1 = part1(commands);
let state2 = part2(commands);
print(f"part1: {state1}, total: {state1.depth * state1.horizontal}");
print(f"part2: {state2}, total: {state2.depth * state2.horizontal}");

fn part1(commands: List<Command>) -> State {
    let mut state = State { depth: 0, horizontal: 0, aim: 0 };
    for command in commands {
        match command {
            Command::Forward(i) => state.horizontal = state.horizontal + i,
            Command::Down(i) => state.depth = state.depth + i,
            Command::Up(i) => state.depth = state.depth - i,
        }
    }
    state
}
fn part2(commands: List<Command>) -> State {
    let mut state = State { depth: 0, horizontal: 0, aim: 0 };
    for command in commands {
        match command {
            Command::Forward(i) => {
                state.horizontal = state.horizontal + i;
                state.depth = state.depth + state.aim * i;
            },
            Command::Down(i) => state.aim = state.aim + i,
            Command::Up(i) => state.aim = state.aim - i,
        }
    }
    state
}
