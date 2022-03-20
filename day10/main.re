/*let input = File::read_to_string("sample.txt");*/
let input = File::read_to_string("input.txt");
let input = input.unwrap().trim();
let input = input.split("\n");

let mut incompletes = List::new();

let part1 = part1(input, incompletes);
print(f"part1: {part1.error_score()}");

let part2 = part2(incompletes);
print(f"part2: {part2}");

enum Type {
    /// ()
    Round,
    /// []
    Square,
    /// {}
    Curly,
    /// <>
    Angle,
}

struct Invalid {
    round: int,
    square: int,
    curly: int,
    angle: int,
}
impl Invalid {
    fn new() -> Invalid {
        Invalid { round: 0, square: 0, curly: 0, angle: 0 }
    }
    fn invalid_round(mut self) {
        self.round += 1;
    }
    fn invalid_square(mut self) {
        self.square += 1;
    }
    fn invalid_curly(mut self) {
        self.curly += 1;
    }
    fn invalid_angle(mut self) {
        self.angle += 1;
    }
    fn error_score(self) -> int {
        self.round * 3 + self.square * 57 + self.curly * 1197 + self.angle * 25137
    }
}

fn part1(input: List<string>, mut incompletes: List<List<Type>>) -> Invalid {
    let mut invalid = Invalid::new();
    
    'line: for line in input {
        let mut stack = List::new();
        let mut i = 0;
        while i < line.len_utf8() {
            let invalid = match line.slice(i, i+1) {
                "(" => { stack.push(Type::Round); false },
                "[" => { stack.push(Type::Square); false },
                "{" => { stack.push(Type::Curly); false },
                "<" => { stack.push(Type::Angle); false },
                ")" => if stack.pop() != Option::Some(Type::Round) { invalid.invalid_round(); true } else { false },
                "]" => if stack.pop() != Option::Some(Type::Square) { invalid.invalid_square(); true } else { false },
                "}" => if stack.pop() != Option::Some(Type::Curly) { invalid.invalid_curly(); true } else { false },
                ">" => if stack.pop() != Option::Some(Type::Angle) { invalid.invalid_angle(); true } else { false },
                c => panic(f"unreachable: character is not a bracket: {c:?}"),
            };
            if invalid {
                continue 'line;
            }
            i += 1;
        }
        incompletes.push(stack);
    }

    invalid
}

fn part2(incompletes: List<List<Type>>) -> int {
    let mut scores = List::new();
    for stack in incompletes {
        let mut score = 0;
        let mut i = stack.len() - 1;
        while i >= 0 {
            score *= 5;
            let typ = stack.get(i).unwrap();
            match typ {
                Type::Round => score += 1,
                Type::Square => score += 2,
                Type::Curly => score += 3,
                Type::Angle => score += 4,
            }
            i -= 1;
        }
        scores.push(score);
    }
    scores.sort();
    scores.get(scores.len() / 2).unwrap()
}
