use std::env;
use std::time::SystemTime;


fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        println!("usage: rust-n-queens-solver N [-d]");
        return;
    }

    let mut display_results: bool = false;
    if args.len() == 3 && args[2] == "-d" {
        display_results=true;
    }

    let size: usize = (&args[1]).parse().unwrap();

    let sys_time = SystemTime::now();

    let n_queen_positions : Vec<(usize, usize)> = Vec::new();
    let solutions = solve(size, n_queen_positions, 0);

    let end_time = SystemTime::now();
    let run_time = end_time.duration_since(sys_time)
                             .expect("SystemTime::duration_since failed");

    println!( "N-Queens Found {} solutions in {:.3}s on a {}x{} board",
                solutions.len(),
                run_time.as_secs() as f64 + run_time.subsec_nanos() as f64 * 0.000000001,
                size, size );

    if display_results {
        for i in 0..solutions.len() {
            println!("Solution: {}", i+1);
            display_queens(&solutions[i]);
        }
    }
}


fn is_valid_position( n_queen_positions: & Vec<(usize, usize)>, new_position: & (usize, usize) ) -> bool
{
    for existing_position in n_queen_positions.iter()
    {
        if existing_position.1 == new_position.1 || existing_position.0 == new_position.0
        {
            return false;
        }

        let row_difference = (new_position.1 as isize - existing_position.1 as isize).abs();
        let column_difference = (new_position.0 as isize - existing_position.0 as isize).abs();
        if row_difference == column_difference {
            return false;
        }
    }

    return true;
}



fn solve(n_queens_size: usize, n_queen_positions: Vec<(usize, usize)>, current_column: usize) -> Vec<Vec<(usize, usize)>> {

    if current_column == n_queens_size {
        return vec![n_queen_positions.clone()];
    }
    let mut solutions : Vec<Vec<(usize, usize)>> = Vec::new();
    for row in 0..n_queens_size {
        let new_position = (current_column, row);
        if is_valid_position(&n_queen_positions, &new_position) {
            let mut new_queen_positions = n_queen_positions.clone();
            new_queen_positions.push(new_position);
            let new_solutions = solve(n_queens_size, new_queen_positions, current_column+1);
            for new_solution in new_solutions {
                solutions.push(new_solution);
            }
        }
    }
    return solutions;
}


fn display_queens(solution: & Vec<(usize, usize)>) {
    for y in 0..solution.len() {
        for x in 0..solution.len() {
            let mut out = "_";
            for cord in solution.iter() {
                if cord.0 == x && cord.1 == y {
                    out = "Q";
                }
            }
            print!("{} ", out);
        }
        println!("");
    }
}
