#/bin/sh

for i in {8..12}; do
    echo "=== testing $i ==="

    which node &>/dev/null && if [ -x $(which node) ]
        then
        echo "node: $(node javascript_n_queens_solver.js $i)"
    fi

    which luajit &>/dev/null && if [ -x $(which luajit) ]
        then
        echo "lua : $(board_size=$i luajit luajit_n_queens_solver.lua)"
    fi

    which pypy &>/dev/null && if [ -x $(which pypy) ]
        then
        echo "pypy: $(pypy python_n_queens_solver.py $i)"
    fi

    which python &>/dev/null && if [ -x $(which python) ]
        then
        echo "python: $(python python_n_queens_solver.py $i)"
    fi

    which scala &>/dev/null && if [ -x $(which scala) ]
        then
        echo "scala: $(scala scala_n_queens_solver.scala $i)"
    fi

    which ruby &>/dev/null && if [ -x $(which ruby) ]
        then
        echo "ruby: $(ruby ruby_n_queens_solver.rb $i)"
    fi

    which dart &> /dev/null && if [ -x $(which dart) ]
    then
      echo "dart: $(dart dart_n_queens_solver.dart $i)"
    fi

    echo "C: $(./c_solver $i)"

    echo

done
