//let input = File::read_to_string("sample.txt");
let input = File::read_to_string("input.txt");
let input = input.unwrap().trim();

let lines = Lines::parse(input);

lines.add_non_diagonal();
//lines.print();
print(f"part1 = {lines.at_least_two()}");
lines.add_diagonal();
//lines.print();
print(f"part2 = {lines.at_least_two()}");

struct Point {
    x: int,
    y: int,
}
struct Line {
    a: Point,
    b: Point,
}
struct Count {
    count: int,
}
impl Point {
    fn parse(s: string) -> Point {
        let parts = s.split(",");
        assert(parts.len() == 2);
        let x = parts.get(0).unwrap().trim().parse_int().unwrap();
        let y = parts.get(1).unwrap().trim().parse_int().unwrap();
        Point { x: x, y: y }
    }
}
impl Line {
    fn parse(s: string) -> Line {
        let parts = s.split("->");
        assert(parts.len() == 2);
        let a = Point::parse(parts.get(0).unwrap().trim());
        let b = Point::parse(parts.get(1).unwrap().trim());
        Line { a: a, b: b }
    }
    fn is_horizontal(self) -> bool {
        self.a.y == self.b.y
    }
    fn is_vertical(self) -> bool {
        self.a.x == self.b.x
    }
}
struct Lines {
    lines: List<Line>,
    map: Map<Point, Count>,
    width: int,
    height: int,
}
impl Lines {
    fn parse(input: string) -> Lines {
        let mut width = 0;
        let mut height = 0;
        let input_lines = input.split("\n");
        let mut lines = List::new();
        for line in input_lines {
            let line = Line::parse(line.trim());
            width = width.max(line.a.x).max(line.b.x);
            height = height.max(line.a.y).max(line.b.y);
            lines.push(line);
        }

        Lines {
            lines: lines,
            map: Map::new(),
            width: width,
            height: height,
        }
    }

    fn inc_count(self, point: Point) {
        let mut count = match self.map.get(point) {
            Option::Some(count) => count,
            Option::None => {
                let count = Count { count: 0 };
                self.map.insert(point, count);
                count
            }
        };
        count.count += 1;
    }

    fn add_non_diagonal(self) {
        for line in self.lines {
            if line.is_horizontal() {
                let x1 = line.a.x.min(line.b.x);
                let x2 = line.a.x.max(line.b.x);
                let mut x = x1;
                while x <= x2 {
                    self.inc_count(Point { x: x, y: line.a.y });
                    x += 1;
                }
            } else if line.is_vertical() {
                // vertical
                let y1 = line.a.y.min(line.b.y);
                let y2 = line.a.y.max(line.b.y);
                let mut y = y1;
                while y <= y2 {
                    self.inc_count(Point { x: line.a.x, y: y });
                    y += 1;
                }
            }
        }
    }

    fn add_diagonal(self) {
        for line in self.lines {
            if !line.is_horizontal() && !line.is_vertical() {
                let mut x = line.a.x;
                let mut xdir = if line.a.x < line.b.x { 1 } else { -1 };
                let mut y = line.a.y;
                let mut ydir = if line.a.y < line.b.y { 1 } else { -1 };
                while x != line.b.x + xdir {
                    self.inc_count(Point { x: x, y: y });
                    x += xdir;
                    y += ydir;
                }
                assert(y == line.b.y + ydir);
            }
        }
    }

    fn at_least_two(self) -> int {
        let mut sum = 0;
        for count in self.map.values() {
            if count.count > 1 {
                sum += 1;
            }
        }
        sum
    }

    fn print(self) {
        let mut y = 0;
        while y <= self.height {
            let mut s = "";
            let mut x = 0;
            while x <= self.width {
                match self.map.get(Point { x: x, y: y }) {
                    Option::Some(count) => s = f"{s}{count.count}",
                    Option::None => s = f"{s}.",
                }
                x += 1;
            }
            print(s);
            y += 1;
        }
    }
}
