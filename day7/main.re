//let input = File::read_to_string("sample.txt");
let input = File::read_to_string("input.txt");
let input = input.unwrap().trim();

let mut crabs = List::new();
let mut min = int::max_value();
let mut max = 0;
for num in input.split(",") {
    let num = num.parse_int().unwrap();
    min = min.min(num);
    max = max.max(num);
    crabs.push(num);
}

let part1 = calculate_min_fuel(Part::Part1, crabs, min, max);
print(f"part1: pos = {part1.pos}, fuel = {part1.min_fuel}");
let part2 = calculate_min_fuel(Part::Part2, crabs, min, max);
print(f"part2: pos = {part2.pos}, fuel = {part2.min_fuel}");


enum Part {
    Part1,
    Part2,
}

struct Res {
    min_fuel: int,
    pos: int,
}
fn calculate_min_fuel(part: Part, crabs: List<int>, min: int, max: int) -> Res {
    let mut i = min;
    let mut min_fuel = int::max_value();
    let mut pos = 0;
    while i <= max {
        let mut fuel = 0;
        for crab in crabs {
            let diff = crab - i;
            let diff = diff.abs();
            let cost = match part {
                Part::Part1 => diff,
                Part::Part2 => (diff * (diff + 1))/2,
            };
            fuel += cost;
        }
        if fuel < min_fuel {
            min_fuel = fuel;
            pos = i;
        }
        i += 1;
    }
    Res { min_fuel: min_fuel, pos: pos }
}

