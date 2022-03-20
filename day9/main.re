/*let input = File::read_to_string("sample.txt");*/
let input = File::read_to_string("input.txt");
let input = input.unwrap().trim();

let mut heightmap = List::new();

for line in input.split("\n") {
    let mut list = List::new();
    for digit in line.split("") {
        if digit == "" {
            continue;
        }
        let digit = digit.parse_int().unwrap();
        list.push(digit);
    }
    heightmap.push(list);
}

let low_points = low_points(heightmap);
print(f"part1: {part1(heightmap, low_points)}");
print(f"part2: {part2(heightmap, low_points)}");

fn get_or(heightmap: List<List<int>>, x: int, y: int, default: int) -> int {
    let row = match heightmap.get(y) {
        Option::Some(row) => row,
        Option::None => return default,
    };
    match row.get(x) {
        Option::Some(digit) => digit,
        Option::None => default,
    }
}

fn part1(heightmap: List<List<int>>, low_points: List<Point>) -> int {
    let mut result = 0;
    for point in low_points {
        result += get_or(heightmap, point.x, point.y, 999) + 1;
    }
    result
}
struct Point {
    x: int,
    y: int,
}
fn low_points(heightmap: List<List<int>>) -> List<Point> {
    let mut result = List::new();
    let mut x = 0;
    let mut y = 0;
    while y < heightmap.len() {
        while x < heightmap.get(y).unwrap().len() {
            let num = get_or(heightmap, x, y, 10);
            let left = get_or(heightmap, x-1, y, 10);
            let right = get_or(heightmap, x+1, y, 10);
            let above = get_or(heightmap, x, y+1, 10);
            let below = get_or(heightmap, x, y-1, 10);
            if num < left && num < right && num < above && num < below {
                result.push(Point { x: x, y: y });
            }
            x += 1;
        }
        x = 0;
        y += 1;
    }
    result
}

fn part2(heightmap: List<List<int>>, low_points: List<Point>) -> int {
    let basin_sizes = List::new();
    for low_point in low_points {
        let set = Set::new();
        set.insert(low_point);
        let num = get_or(heightmap, low_point.x, low_point.y, 9);
        basin_rec(heightmap, low_point, num+1, set);
        basin_sizes.push(set.len());
    }
    basin_sizes.sort();
    let a = basin_sizes.get(basin_sizes.len()-1).unwrap();
    let b = basin_sizes.get(basin_sizes.len()-2).unwrap();
    let c = basin_sizes.get(basin_sizes.len()-3).unwrap();
    a * b * c
}
fn basin_rec(heightmap: List<List<int>>, around: Point, num: int, set: Set<Point>) {
    basic_rec_point(heightmap, Point { x: around.x-1, y: around.y }, num, set);
    basic_rec_point(heightmap, Point { x: around.x+1, y: around.y }, num, set);
    basic_rec_point(heightmap, Point { x: around.x, y: around.y+1 }, num, set);
    basic_rec_point(heightmap, Point { x: around.x, y: around.y-1 }, num, set);
}
fn basic_rec_point(heightmap: List<List<int>>, at: Point, num: int, set: Set<Point>) {
    let value = get_or(heightmap, at.x, at.y, 9);
    if value != 9 && value >= num {
        set.insert(at);
        basin_rec(heightmap, at, num+1, set);
    }
}

