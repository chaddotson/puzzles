#!/usr/bin/ruby

require 'optparse'
require 'ostruct'

def get_args(args)
    options = OpenStruct.new
    options.board_size = 0
    options.display_queens = false

    opt_parser = OptionParser.new do |opts|
        opts.banner = "Usage: ruby_n_queens_solver.rb [options] board_size"

        opts.separator  "Arguments"
        opts.separator  "     board_size: Size of the board"
        opts.separator  ""
        opts.separator  "Options"

        opts.on("-d", "--display",
                "display the solutions") do
            options.display_queens = true
        end
    end

    opt_parser.parse!(args)

    if args.empty?
        puts opt_parser
        exit(-1)
    end

    options.board_size = Integer(ARGV[0])

    return options
end

def display_queens(solution)
    for y in 0..solution.length-1 do
        for x in 0..solution.length-1 do
            out = "_"
            for cord in solution do
                if cord[0] == x and cord[1] == y then
                    out = "Q"
                end
            end
            print "#{out} "
        end
        puts
    end
end

def valid_position(n_queen_positions, new_position)
    for existing_position in n_queen_positions
        if (existing_position[1] == new_position[1]) or (existing_position[0] == new_position[0])
            return false
        end

        row_difference = (new_position[1] - existing_position[1]).abs
        column_difference = (new_position[0] - existing_position[0]).abs

        if row_difference == column_difference
            return false
        end
    end

    return true
end


def solve(n_queens_size, n_queen_positions, current_column)

    if (current_column == n_queens_size) and (n_queen_positions.length == n_queens_size)
        return [n_queen_positions]
    end

    solutions = []

    for row in 0..n_queens_size-1
        new_position = [current_column, row]

        if valid_position(n_queen_positions, new_position)
            new_queen_positions = Array.new(n_queen_positions)
            new_queen_positions << new_position

            solution = solve( n_queens_size, new_queen_positions, current_column+1)

            if solution != []
                solutions.concat(solution)
            end
        end
    end

    return solutions
end

options = get_args(ARGV)

start_time = Time.now
solutions = solve(options.board_size, [], 0)
end_time = Time.now

puts "N-Queens Found #{solutions.length} Solutions in #{end_time-start_time} on a #{options.board_size}x#{options.board_size} board"

if options.display_queens
    for i in 0..solutions.length-1 do
        puts "Solution #{i+1}"
        display_queens(solutions[i])
    end
end
