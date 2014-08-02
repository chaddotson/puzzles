


use std::num::abs;
use std::os::args;



fn main() {
    let args = args();
    
    if args.len() < 2 {
        println!("usage: rust-n-queens-solver N [-d]");
        return;
    }
    
    let mut displayResults: bool = false;
    
    
    if args.len() == 3 && args[2] == ~"-d" {
        displayResults=true;
    }

    let nQueenPositions: ~[~[uint]] = ~[];
    
    
    let size: uint = (from_str::<uint>(args[1])).unwrap();
    let solutions: ~[~[~[uint]]] = solve(size, nQueenPositions, 0);
    
    
    println!("Found {} solutions", solutions.len());


    if displayResults {
        for i in range(0, solutions.len()) {
            println!("Solution: {}", i+1);
            displayQueens(&solutions[0]);
        }
    }
}


fn isValidPosition( nQueenPositions: & ~[~[uint]], newPosition: & ~[uint]) -> bool
{
    let mut rowDifference: int = 0;
    let mut columnDifference: int = 0;

    for existingPosition in nQueenPositions.iter()
    {
        if existingPosition[1] == newPosition[1] || existingPosition[0] == newPosition[0]
        {
            return false;
        }
        
//        let something: int = abs(1);
        
        rowDifference = abs(newPosition[1] as int - existingPosition[1] as int);
        columnDifference = abs(newPosition[0] as int - existingPosition[0] as int);
        
        if rowDifference == columnDifference {
            return false;
        }

    }

    return true;
}



fn solve(nQueensSize: uint, nQueenPositions: ~[~[uint]], currentColumn: uint) -> ~[~[~[uint]]] {

    if currentColumn == nQueensSize && nQueenPositions.len() == nQueensSize {
        let mut rtn: ~[~[~[uint]]] = ~[];
        rtn.push(nQueenPositions.clone());
        return rtn;
    }


    let mut solutions: ~[~[~[uint]]] = ~[];

    for row in range(0, nQueensSize) {

        let mut newPosition: ~[uint];
        newPosition = ~[currentColumn, row];
        
        
        if isValidPosition(&nQueenPositions, &newPosition) {
        
            let mut newNQueenPositions: ~[~[uint]] = nQueenPositions.clone();
        
            newNQueenPositions.push(newPosition);
        
        
            let mut newSolutions: ~[~[~[uint]]] = ~[];
        
            newSolutions = solve(nQueensSize, newNQueenPositions, currentColumn+1);


            for i in range(0, newSolutions.len()) {
                solutions.push(newSolutions[i].clone());
            }
        }
    }

    
    return solutions;
    
}


fn displayQueens(solution: &~[~[uint]]) {

    let mut out = ~"";
    
    for y in range(0, solution.len()) {
        for x in range( 0, solution.len()) {
            out = ~"_";
            for cord in solution.iter() {
                if cord[0] == x && cord[1] == y {
                    out = ~"Q";
                }
            }
            print!("{} ", out);
        }
        println!("");
    }

}


