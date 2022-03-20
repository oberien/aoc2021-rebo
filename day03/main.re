//let input = File::read_to_string("sample.txt");
let input = File::read_to_string("input.txt");
let input = input.unwrap();

enum Bit {
    Zero,
    One,
}

let mut numbers = List::new();
for line in input.split("\n") {
    if line != "" {
        let digits = line.split("");
        let list = List::new();
        for digit in digits {
            match digit {
                "0" => list.push(Bit::Zero),
                "1" => list.push(Bit::One),
                _ => (),
            }
        }
        numbers.push(list);
    }
}

// counts
struct BitCount {
    zeroes: int,
    ones: int,
}
fn bit_counts(numbers: List<List<Bit>>) -> List<BitCount> {
    let mut counts = List::new();
    for number in numbers {
        let mut i = 0;
        while i < number.len() {
            let mut count = match counts.get(i) {
                Option::Some(count) => count,
                Option::None => {
                    let count = BitCount { zeroes: 0, ones: 0 };
                    counts.push(count);
                    count
                }
            };
            let bit = number.get(i).unwrap();
            match bit {
                Bit::Zero => count.zeroes = count.zeroes + 1,
                Bit::One => count.ones = count.ones + 1,
            }
            i = i + 1;
        }
    }
    counts
}

let part1 = part1(bit_counts(numbers));
print(f"part1: {part1}, {part1.gamma * part1.epsilon}");
let part2 = part2(numbers);
print(f"part2: {part2}, {part2.o2 * part2.co2}");

struct Rates {
    gamma: int,
    epsilon: int,
}

fn part1(counts: List<BitCount>) -> Rates {
    let mut gamma = 0;
    let mut epsilon = 0;
    for count in counts {
        gamma = gamma * 2;
        epsilon = epsilon * 2;
        let more_zeroes = count.zeroes >= count.ones;
        let more_ones = count.ones >= count.zeroes;
        gamma = gamma + more_ones.to_int();
        epsilon = epsilon + more_zeroes.to_int();
    }
    Rates {
        gamma: gamma,
        epsilon: epsilon,
    }
}

struct LifeSupport {
    o2: int,
    co2: int,
}

fn part2(numbers: List<List<Bit>>) -> LifeSupport {
    let mut o2_rest = numbers;
    let mut co2_rest = numbers;
    let mut bit_index = 0;
    while o2_rest.len() != 1 || co2_rest.len() != 1 {
        let counts = bit_counts(o2_rest);
        let count = counts.get(bit_index).unwrap();
        if o2_rest.len() != 1 {
            let bit = if count.ones >= count.zeroes { Bit::One } else { Bit::Zero };
            o2_rest = filter_bit(o2_rest, bit_index, bit);
        }

        let counts = bit_counts(co2_rest);
        let count = counts.get(bit_index).unwrap();
        if co2_rest.len() != 1 {
            let bit = if count.zeroes <= count.ones { Bit::Zero } else { Bit::One };
            co2_rest = filter_bit(co2_rest, bit_index, bit);
        }
        bit_index = bit_index + 1;
    }

    LifeSupport {
        o2: convert_number(o2_rest.get(0).unwrap()),
        co2: convert_number(co2_rest.get(0).unwrap()),
    }
}

fn filter_bit(numbers: List<List<Bit>>, bit_index: int, bit_value: Bit) -> List<List<Bit>> {
    let mut rest = List::new();
    for number in numbers {
        if number.get(bit_index).unwrap() == bit_value {
            rest.push(number);
        }
    }
    rest
}
fn convert_number(digits: List<Bit>) -> int {
    let mut res = 0;
    for digit in digits {
        res = res * 2;
        res = res + match digit {
            Bit::Zero => 0,
            Bit::One => 1,
        };
    }
    res
}
