#/bin/sh

for i in {8..13}; do 
  echo "=== testing $i ==="
  echo "node:" $(node javascript_n_queens_solver.js $i)
  echo "pypy:" $(pypy python_n_queens_solver.py $i)
  echo "ruby:" $(ruby ruby_n_queens_solver.rb $i)
  echo
done