local author = 'Chad Dotson'

local board_size = os.getenv('board_size')

if not board_size or arg[1] == '-h' then
    print 'board_size=15 display=true|false luajit ./luajit_n_queens_solver.lua'
    return
end

board_size = tonumber(board_size)

local display = os.getenv('display')
display = (display ~= nil) and (display ~= 'false')

function table.copy(t)
    local copy = {}
    for n,v in ipairs(t) do
        copy[n] = v
    end
    return copy
end

local function display_queens(n_queens_size, solution, test)
    local size = #solution
    for y = 1, n_queens_size do
        for x = 1, n_queens_size do
            local out
            if test and test[1] == x and test[2] == y then
                out = '?'
            else
                for _,cord in ipairs(solution) do
                    if cord[1] == x and cord[2] == y then
                        out = 'Q'
                        break
                    end
                end
                if out == nil then
                    if y > size or x > size then
                        out = 'x'
                    else
                        out = '_'
                    end
                end
            end
            io.write(out)
        end
        io.write('\n')
    end
end

local function valid_position(n_queens_positions, new_position)
    for i,existing_position in ipairs(n_queens_positions) do
        if existing_position[2] == new_position[2] or existing_position[1] == new_position[1] then
            return false
        end

        local row_difference = math.abs(new_position[2] - existing_position[2])
        local column_difference = math.abs(new_position[1] - existing_position[1])
        
        if row_difference == column_difference then
            return false
        end
    end

    return true
end

local function solve(n_queens_size, n_queens_positions, current_row, current_column, solutions)

    if current_column == n_queens_size + 1 then
        if #n_queens_positions == n_queens_size then
            solutions[#solutions+1] = table.copy(n_queens_positions)
        end
        current_row = table.remove(n_queens_positions)[2]
        return solve(n_queens_size, n_queens_positions, current_row+1, current_column-1,solutions)
    end

    if current_row == n_queens_size + 1 then
        if #n_queens_positions == 0 then
            return solutions
        end
        return solve(n_queens_size, n_queens_positions, table.remove(n_queens_positions)[2] + 1,current_column-1, solutions)
    end

    local new_position = {current_column, current_row}

    if valid_position(n_queens_positions, new_position) then

        n_queens_positions[#n_queens_positions+1] = new_position
        return solve(n_queens_size, n_queens_positions, 1, current_column+1, solutions)
    else
        return solve(n_queens_size, n_queens_positions, current_row + 1, current_column, solutions)
    end
end

local start_time = os.clock()
local solutions = solve(board_size, {}, 1, 1, {})
local end_time = os.clock()

print ("N-Queens Found "..#solutions.." Solutions in "..(end_time-start_time).." on a "..board_size..'x'..board_size.." board")

if display then
    for i,solution in ipairs(solutions) do
        print ("Solution", i)
        display_queens(board_size,solution)
    end
end
