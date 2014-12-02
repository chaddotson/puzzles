__author__ = 'Chad Dotson'


import argparse
from datetime import datetime

def get_args():
    parser = argparse.ArgumentParser(description='Calculate N-Queens solutions.')
    parser.add_argument("board_size", type=int, help="the board size")
    parser.add_argument("-d", "--display", action="store_true",
                        help="display the solutions")

    return parser.parse_args()


def display_queens(solution):
    for y in range(0, len(solution)):
        for x in range(0, len(solution)):
            out = "_"
            for coordinate in solution:
                if coordinate[0] == x and coordinate[1] == y:
                    out = "Q"
            print out,
        print


def valid_position(n_queen_positions, new_position):
    for existing_position in n_queen_positions:
        if existing_position[1] == new_position[1] or existing_position[0] == new_position[0]:
            return False

        row_difference = abs(new_position[1] - existing_position[1])
        column_difference = abs(new_position[0] - existing_position[0])

        if row_difference == column_difference:
            return False

    return True


def solve(n_queens_size, n_queen_positions, current_column):

    if current_column == n_queens_size and len(n_queen_positions) == n_queens_size:
        return [n_queen_positions]

    solutions = []

    for row in range(0, n_queens_size):
        new_position = (current_column, row)

        if valid_position(n_queen_positions, new_position):

            new_queens_positions = n_queen_positions[:]
            new_queens_positions.append(new_position)

            solution = solve(n_queens_size, new_queens_positions, current_column+1)

            if solution is not None:
                solutions.extend(solution)

    return solutions


args = get_args()

start_time = datetime.now()
solutions = solve(args.board_size, [], 0)
end_time = datetime.now()

print "N-Queens Found {0} Solutions in {1}s on a {2}x{2} board".format(len(solutions), (end_time-start_time).total_seconds(), args.board_size, args.board_size)

if args.display:
    for i in range(0, len(solutions)):
        print "Solution", i+1
        display_queens(solutions[i])
