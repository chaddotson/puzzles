for i in {8..13}; do 
  echo "=== testing $i ==="
  node javascript_n_queens_solver.js $i
  pypy python_n_queens_solver.py $i
  echo
done