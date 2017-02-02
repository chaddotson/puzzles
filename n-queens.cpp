#include <array>
#include <stdint.h>
#include <string>
#include <vector>
#include <chrono>

template<typename C, typename... Args>
long benchmark(const C &c, Args &&... args) {
    auto begin = std::chrono::high_resolution_clock::now();
    c(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    return diff.count();
}

constexpr auto Max = 16;

using Solution = std::array<int8_t, Max>;

struct Solver {
    Solution m_positions;
    int8_t m_n, m_current = 0;
    std::vector<Solution> *m_solutions;

    Solver(int n, std::vector<Solution> &solutions): m_n(n), m_solutions(&solutions) {}

    // finds solutions for the given positions and the given column
    void next(int column);
    void nonRec();
    inline bool valid(int column, int row) const;
};

void Solver::next(int column) {
    if(m_n == column) { m_solutions->push_back(m_positions); return; }
    for(int row = 0; row < m_n; ++row) {
        if(valid(column, row)) {
            m_positions[column] = row;
            next(column + 1);
        }
    }
}

void Solver::nonRec() {
    struct Frame { int column, row; };
    std::array<Frame, Max> frames = {{ 0, 0 }};
    int ndx = 0;
    for(;;) {
        while(frames[ndx].row < m_n) {
            if(valid(frames[ndx].column, frames[ndx].row)) {
                m_positions[frames[ndx].column] = frames[ndx].row;
                if(m_n == ++ndx) {
                    m_solutions->push_back(m_positions);
                    --ndx;
                } else {
                    frames[ndx].column = frames[ndx - 1].column + 1;
                    frames[ndx].row = 0;
                    continue;
                }
            }
            ++frames[ndx].row;
        }
        if(!ndx--) { break; }
        ++frames[ndx].row;
    }
}

bool Solver::valid(int column, int new_y) const {
    for(auto qNdx = 0; qNdx < column; ++qNdx) { // go over the existing queens
        auto at = m_positions[qNdx];
        if(at == new_y) { return false; } // same row
        auto rowDifference = abs(new_y - at);
        auto colDifference = column - qNdx;
        if(rowDifference == colDifference) { return false; }
    }
    return true;
}

#include <iostream>
#include <iomanip>

int main(int argc, const char *argv[]) {
    if(argc < 2) {
        std::cerr << "Lacks number of queens" << std::endl;
        return 1;
    }
    auto n = std::stoi(argv[1]);
    if(n < 1 && 16 < n) {
        std::cerr << "Invalid number of queens " << n << std::endl;
        return 1;
    }
    std::vector<Solution> solutions;
    solutions.reserve(1 << 24); // reserve over 16 million
    Solver s(n, solutions);
    auto time = benchmark([&](){ s.next(0); });
    
    std::cout << "N-Queens Found " << solutions.size() << " Solutions in " <<
        std::fixed << std::setprecision(6) << time/1000000.0 << "s on a " <<
        n << 'x' << n << " board" << std::endl;
    return 0;
}
