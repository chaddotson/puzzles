#/bin/sh

for i in {8..12}; do
    echo "=== testing $i ==="

    if [ -x $(which node) ]
        then
        echo "node: $(node javascript_n_queens_solver.js $i)"
    fi

    if [ -x $(which luajit) ]
        then
        echo "lua : $(board_size=$i luajit luajit_n_queens_solver.lua)"
    fi

    if [ -x $(which pypy) ]
        then
        echo "pypy: $(pypy python_n_queens_solver.py $i)"
    fi

    if [ -x $(which python) ]
        then
        echo "python: $(python python_n_queens_solver.py $i)"
    fi

    if [ -x $(which scala) ]
        then
        echo "scala: $(scala scala_n_queens_solver.scala $i)"
    fi

    if [ -x $(which ruby) ]
        then
        echo "ruby: $(ruby ruby_n_queens_solver.rb $i)"
    fi

    echo
done
