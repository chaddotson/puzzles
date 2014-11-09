#/bin/sh

for i in {8..12}; do 
  echo "=== testing $i ==="
  echo "node: $(node javascript_n_queens_solver.js $i)"
  echo "lua : $(board_size=$i luajit luajit_n_queens_solver.lua)"
  echo "pypy: $(pypy python_n_queens_solver.py $i)"
  echo "ruby: $(ruby ruby_n_queens_solver.rb $i)"
  echo
done