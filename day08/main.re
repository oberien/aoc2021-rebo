//let input = File::read_to_string("sample.txt");
let input = File::read_to_string("input.txt");
let input = input.unwrap().trim();

let mut displays = List::new();
for line in input.split("\n") {
    displays.push(Display::parse(line));
}
print(f"part1 = {part1(displays)}");
print(f"part2 = {part2(displays)}");

fn part1(displays: List<Display>) -> int {
    let mut count = 0;
    for display in displays {
        for output in display.outputs {
            match output.segments.len_utf32() {
                2 => count += 1,
                3 => count += 1,
                4 => count += 1,
                7 => count += 1,
                _ => (),
            }
        }
    }
    count
}
fn part2(displays: List<Display>) -> int {
    let mut sum = 0;
    for display in displays {
        display.solve();
        let mut num = 0;
        for output in display.outputs {
            num *= 10;
            num += display.solved.get(output.segments).unwrap();
        }
        sum += num;
    }
    sum
}

struct Digit {
    segments: string,
}
struct Display {
    digits: List<Digit>,
    outputs: List<Digit>,
    solved: Map<string, int>,
    inverse_solved: Map<int, string>,
}
impl Digit {
    fn new(segments: string) -> Digit {
        Digit { segments: segments.sorted() }
    }
}
impl Display {
    fn parse(line: string) -> Display {
        let parts = line.split(" \\| ");
        let mut digits = List::new();
        for digit in parts.get(0).unwrap().split(" ") {
            digits.push(Digit::new(digit))
        }
        let mut outputs = List::new();
        for output in parts.get(1).unwrap().split(" ") {
            outputs.push(Digit::new(output));
        }
        Display { digits: digits, outputs: outputs, solved: Map::new(), inverse_solved: Map::new() }
    }

    fn solve(mut self) {
        for digit in self.digits {
            match digit.segments.len_utf32() {
                2 => {
                    self.solved.insert(digit.segments, 1);
                    self.inverse_solved.insert(1, digit.segments);
                },
                3 => {
                    self.solved.insert(digit.segments, 7);
                    self.inverse_solved.insert(7, digit.segments);
                },
                4 => {
                    self.solved.insert(digit.segments, 4);
                    self.inverse_solved.insert(4, digit.segments);
                },
                7 => {
                    self.solved.insert(digit.segments, 8);
                    self.inverse_solved.insert(8, digit.segments);
                },
                5 => (),
                6 => (),
                x => panic(f"unreachable: digit has length {x}"),
            }
        }
        for digit in self.digits {
            match digit.segments.len_utf32() {
                5 => if digit.segments.find_matches(f"[{self.inverse_solved.get(7).unwrap()}]").len() == 3 {
                    self.solved.insert(digit.segments, 3);
                    self.inverse_solved.insert(3, digit.segments);
                } else if digit.segments.find_matches(f"[{self.inverse_solved.get(4).unwrap()}]").len() == 3 {
                    self.solved.insert(digit.segments, 5);
                    self.inverse_solved.insert(5, digit.segments);
                } else if digit.segments.find_matches(f"[{self.inverse_solved.get(4).unwrap()}]").len() == 2 {
                    self.solved.insert(digit.segments, 2);
                    self.inverse_solved.insert(2, digit.segments);
                } else {
                    panic("unknown");
                },
                6 => if !digit.segments.find_matches(f"[{self.inverse_solved.get(7).unwrap()}]").len() == 3 {
                    self.solved.insert(digit.segments, 6);
                    self.inverse_solved.insert(6, digit.segments);
                } else if digit.segments.find_matches(f"[{self.inverse_solved.get(4).unwrap()}]").len() == 4 {
                    self.solved.insert(digit.segments, 9);
                    self.inverse_solved.insert(9, digit.segments);
                } else {
                    self.solved.insert(digit.segments, 0);
                    self.inverse_solved.insert(0, digit.segments);
                },
                _ => (),
            }
        }
    }
}

