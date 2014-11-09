#!/usr/bin/env luajit

-- note: snarky "doubles the calculation time" comments only really apply at size=10 or lower
-- ...but they are spookily accurate

-- luajit factoid: removing this variable doubles the calculation time
local derp = 'derpderp'

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

local function display_queens(solution)
    -- luajit factoid: using "size" instead of n_queens_size doubles the calculation time
    local n_queens_size = #solution
    for y = 1, n_queens_size do
        for x = 1, n_queens_size do
            local out = '_'
            for i,cord in ipairs(solution) do
                if cord[1] == x and cord[2] == y then
                    out = 'Q'
                    break
                end
            end
            io.write(out)
        end
        io.write('\n')
    end
end

local function valid_position(n_queens_positions, new_position)
    for _,existing_position in ipairs(n_queens_positions) do
        --luajit factoid: using locals to hold table values doubles the calculation time
        if existing_position[2] == new_position[2] or existing_position[1] == new_position[1] then
            return false
        end

        -- luajit factoid: NOT using locals to hold math.abs results doubles the calculation time
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
        -- note: previous row is saved so we don't need true recursion yay
        return solve(
            n_queens_size, 
            n_queens_positions, 
            table.remove(n_queens_positions)[2]+1, 
            current_column-1, 
            solutions)
    end

    if current_row == n_queens_size + 1 then
        if #n_queens_positions == 0 then
            -- we ran outta piddies
            return solutions
        end
        -- note: previous row is saved so we don't need true recursion yay
        return solve(
            n_queens_size, 
            n_queens_positions, 
            table.remove(n_queens_positions)[2] + 1,
            current_column-1, 
            solutions)
    end

    local new_position = {current_column, current_row}

    if valid_position(n_queens_positions, new_position) then
        n_queens_positions[#n_queens_positions+1] = new_position
        -- success, onto the next column!
        return solve(
            n_queens_size, 
            n_queens_positions, 
            1, 
            current_column+1, 
            solutions)
    else
        -- fail, try the next row in the current column
        return solve(
            n_queens_size, 
            n_queens_positions, 
            current_row + 1, 
            current_column, 
            solutions)
    end
end

-- just in case...
collectgarbage('stop')
local start_time = os.clock()
local solutions = solve(board_size, {}, 1, 1, {})
local end_time = os.clock()
collectgarbage('restart')

print ("N-Queens Found "..#solutions.." Solutions in "..(end_time-start_time).."s on a "..board_size..'x'..board_size.." board")

if display then
    for i,solution in ipairs(solutions) do
        print ("Solution", i)
        display_queens(solution)
    end
end
