//let input = File::read_to_string("sample.txt");
let input = File::read_to_string("input.txt");
let input = input.unwrap();
let lines = input.split("\n");

let nums = List::new();
for line in lines {
    if line != "" {
        nums.push(line.parse_int().unwrap());
    }
}

print(f"part 1: {part1(nums)}");
print(f"part 2: {part2(nums)}");

fn part1(nums: List<int>) -> int {
    let mut last = Option::None;
    let mut result = 0;
    for num in nums {
        match last {
            Option::None => (),
            Option::Some(last_num) => {
                if last_num < num {
                    result = result + 1;
                }
            }
        }
        last = Option::Some(num);
    }
    result
}

fn part2(nums: List<int>) -> int {
    let mut last3 = Option::None;
    let mut last2 = Option::None;
    let mut last1 = Option::None;
    let mut result = 0;
    for num in nums {
        match last3 {
            Option::Some(last3_num) => match last2 {
                Option::Some(last2_num) => match last1 {
                    Option::Some(last1_num) => {
                        let last = last3_num + last2_num + last1_num;
                        let curr = last2_num + last1_num + num;
                        if last < curr {
                            result = result + 1;
                        }
                    },
                    Option::None => (),
                },
                Option::None => (),
            },
            Option::None => (),
        }
        last3 = last2;
        last2 = last1;
        last1 = Option::Some(num);
    }
    result
}

