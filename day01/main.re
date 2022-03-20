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
    if nums.len() < 1 {
        0
    } else {
        let mut last = nums.get(0).unwrap();
        let nums = nums.slice(1);
        let mut result = 0;
        for num in nums {
            if last < num {
                result = result + 1;
            }
            last = num;
        }
        result
    }
}

fn part2(nums: List<int>) -> int {
    if nums.len() < 3 {
        0
    } else {
        let mut last3 = nums.get(0).unwrap();
        let mut last2 = nums.get(1).unwrap();
        let mut last1 = nums.get(2).unwrap();
        let nums = nums.slice(3);
        let mut result = 0;
        for num in nums {
            let last = last3 + last2 + last1;
            let curr = last2 + last1 + num;
            if last < curr {
                result = result + 1;
            }
            last3 = last2;
            last2 = last1;
            last1 = num;
        }
        result
    }
}

