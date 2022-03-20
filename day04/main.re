//let input = File::read_to_string("sample.txt");
let input = File::read_to_string("input.txt");
let input = input.unwrap().trim();

let game = Game::parse(input);
let part1 = part1(game);
print(f"{part1.sum_unmarked() * game.last_drawn}");
let game = Game::parse(input);
let part2 = part2(game);
print(f"{part2.sum_unmarked() * game.last_drawn}");

fn part1(mut game: Game) -> Board {
    let mut res = Option::None;
    while res.is_none() {
        game.draw_next_number();
        res = game.get_winning_board();
    }
    res.unwrap()
}
fn part2(mut game: Game) -> Board {
    while game.boards.len() > 1 {
        game.draw_next_number();
        game.remove_winning_boards()
    }
    let mut res = Option::None;
    while res.is_none() {
        game.draw_next_number();
        res = game.get_winning_board();
    }
    res.unwrap()
}

struct Field {
    num: int,
    marked: bool,
}
struct Board {
    fields: List<List<Field>>,
}
impl Board {
    fn parse(s: string) -> Board {
        let rows = s.split("\n");
        assert(rows.len() == 5);
        let mut nums = List::new();
        for row in rows {
            let mut list = List::new();
            for num in row.find_matches("\\d+") {
                list.push(Field {
                    num: num.parse_int().unwrap(),
                    marked: false,
                });
            }
            assert(list.len() == 5);
            nums.push(list);
        }
        Board { fields: nums }
    }
    fn mark_number(mut self, number: int) {
        for row in self.fields {
            for mut field in row {
                if field.num == number {
                    field.marked = true;
                }
            }
        }
    }
    fn has_won(self) -> bool {
        let mut won = false;
        // check rows
        for row in self.fields {
            let mut all_marked = true;
            for field in row {
                all_marked &= field.marked;
            }
            won |= all_marked;
        }
        // check columns
        let mut i = 0;
        while i < 5 {
            let mut all_marked = true;
            for row in self.fields {
                all_marked &= row.get(i).unwrap().marked;
            }
            won |= all_marked;
            i += 1;
        }
        won
    }
    fn sum_unmarked(self) -> int {
        let mut sum = 0;
        for row in self.fields {
            for field in row {
                if !field.marked {
                    sum += field.num;
                }
            }
        }
        sum
    }
}

struct Game {
    numbers_to_draw: List<int>,
    last_drawn: int,
    boards: List<Board>,
}
impl Game {
    fn parse(s: string) -> Game {
        let parts = s.split("\n\n");
        let mut numbers_to_draw = List::new();
        for num in parts.get(0).unwrap().split(",") {
            numbers_to_draw.push(num.parse_int().unwrap());
        }

        let mut boards = List::new();
        for board in parts.slice(1) {
            boards.push(Board::parse(board));
        }
        Game { numbers_to_draw: numbers_to_draw, last_drawn: 0, boards: boards }
    }

    fn draw_next_number(mut self) {
        self.last_drawn = self.numbers_to_draw.remove(0).unwrap();
        for board in self.boards {
            board.mark_number(self.last_drawn);
        }
    }

    fn get_winning_board(self) -> Option<Board> {
        let mut ret = Option::None;
        for board in self.boards {
            if board.has_won() {
                ret = Option::Some(board);
            }
        }
        ret
    }

    fn remove_winning_boards(mut self) {
        let mut i = 0;
        while i < self.boards.len() {
            if self.boards.get(i).unwrap().has_won() {
                self.boards.swap_remove(i);
            } else {
                i += 1;
            }
        }
    }
}

