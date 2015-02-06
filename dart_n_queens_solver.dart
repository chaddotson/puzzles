import 'dart:io';

void displayQueens(solution){
  int len = solution.length;
  bool isQueen(row, col) => solution.any((p){
    return p[0] == row && p[1] == col;
  });
  for(int row=0; row<len; row++){
    for(int col=0; col<len; col++){
      stdout.write( isQueen(row, col) ? 'Q ' : '_ ');
    }
    stdout.write('\n');
  }
}

bool isValidPosition(ps, p){
  for(int i=0; i<ps.length; i++){
    var t = ps[i];
    if( t[0] == p[0] || t[1] == p[1] ) return false;
    var drow = p[0] - t[0];
    var dcol = p[1] - t[1];
    if( drow.abs() == dcol.abs() ) return false;
  }
  return true;
}

List solve(size, pos, col){
  if(col == size && pos.length == size) return [pos];
  var solutions = [];
  for(int row=0; row<size; row++){
    var p = [col, row];
    if(isValidPosition(pos, p)){
      var pos_ = [];
      pos_.addAll(pos);
      pos_.add(p);
      var solution = solve(size, pos_, col+1);
      for(int i=0; i<solution.length; i++){
        solutions.add(solution[i]);
      }
    }
  }
  return solutions;
}

void main(args){
  if( args.length == 0 ){
    print('usage: dart dart_n_queens_solver.dart <BOARD_SIZE> [-d]');
    exit(1);
  }
  int size = int.parse(args[0]);
  bool displaySolutions = args.length > 1 && args[1] == '-d';
  var startTime = new DateTime.now();
  var solutions = solve(size, [], 0);
  var endTime = new DateTime.now();

  var tdiff = endTime.difference(startTime).inMilliseconds / 1000;
  print('N-Queens Found ${solutions.length} solutions in ${tdiff}s on a ${size}x${size} board');

  if(displaySolutions){
    for(int i=0; i<solutions.length; i++){
      print('Solution ${i+1}');
      displayQueens(solutions[i]);
    }
  }
}