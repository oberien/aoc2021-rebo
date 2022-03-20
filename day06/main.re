//let input = File::read_to_string("sample.txt");
let input = File::read_to_string("input.txt");
let input = input.unwrap().trim();

let fishes = Fishes::parse(input);
let part1 = part1(fishes);
print(f"part1 = {part1}");
let fishes2 = Fishes2::parse(input);
let part2 = part2(fishes2);
print(f"part2 = {part2}");

fn part1(fishes: Fishes) -> int {
    let mut i = 0;
    while i < 80 {
        fishes.pass_day();
        i += 1;
    }
    fishes.fishes.len()
}
fn part2(fishes: Fishes2) -> int {
    let mut i = 0;
    while i < 256 {
        fishes.pass_day();
        i += 1;
    }
    fishes.num_fishes()
}

struct Fish {
    interval: int,
}
struct Fishes {
    fishes: List<Fish>,
    passed_days: int,
}
impl Fishes {
    fn parse(input: string) -> Fishes {
        let mut fishes = List::new();
        for num in input.split(",") {
            let fish = Fish {
                interval: num.parse_int().unwrap(),
            };
            assert(fish.interval >= 0 && fish.interval <= 8);
            fishes.push(fish);
        }
        Fishes {
            fishes: fishes,
            passed_days: 0,
        }
    }

    fn pass_day(self) {
        let max = self.fishes.len();
        let mut i = 0;
        while i < max {
            let mut fish = self.fishes.get(i).unwrap();
            if fish.interval == 0 {
                self.fishes.push(Fish { interval: 8 });
                fish.interval = 6;
            } else {
                fish.interval -= 1;
            }
            i += 1;
        }
    }

    fn print(self) {
        let mut s = "After {self.passed_days:3} days: ";
        for fish in self.fishes {
            s = f"{s}{fish.interval},";
        }
        print(s);
    }
}

struct Count {
    count: int,
}
struct Fishes2 {
    fishes: Map<int, Count>,
}
impl Fishes2 {
    fn parse(input: string) -> Fishes2 {
        let mut map = Map::new();
        let fishes = Fishes::parse(input);
        for fish in fishes.fishes {
            let mut count = match map.get(fish.interval) {
                Option::Some(count) => count,
                Option::None => {
                    let count = Count { count: 0 };
                    map.insert(fish.interval, count);
                    count
                }
            };
            count.count += 1;
        }
        Fishes2 { fishes: map }
    }
    fn pass_day(mut self) {
        let mut map = Map::new();
        for interval in self.fishes.keys() {
            let count = self.fishes.get(interval).unwrap();
            let mut num_new_fish = 0;
            let interval = if interval == 0 {
                num_new_fish = count.count;
                6
            } else {
                interval - 1
            };
            match map.get(interval) {
                Option::Some(mut c) => c.count += count.count,
                Option::None => { map.insert(interval, Count { count: count.count }); },
            }
            match map.get(8) {
                Option::Some(mut c) => c.count += num_new_fish,
                Option::None => { map.insert(8, Count { count: num_new_fish }); },
            }
        }
        self.fishes = map;
    }
    fn num_fishes(self) -> int {
        let mut sum = 0;
        for count in self.fishes.values() {
            sum += count.count;
        }
        sum
    }
}

