# Homework 01 - Game of life
# 
# Your task is to implement part of the cell automata called
# Game of life. The automata is a 2D simulation where each cell
# on the grid is either dead or alive.
# 
# State of each cell is updated in every iteration based state of neighbouring cells.
# Cell neighbours are cells that are horizontally, vertically, or diagonally adjacent.
#
# Rules for update are as follows:
# 
# 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
# 2. Any live cell with two or three live neighbours lives on to the next generation.
# 3. Any live cell with more than three live neighbours dies, as if by overpopulation.
# 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
#
# 
# Our implementation will use coordinate system will use grid coordinates starting from (0, 0) - upper left corner.
# The first coordinate is row and second is column.
# 
# Do not use wrap around (toroid) when reaching edge of the board.
# 
# For more details about Game of Life, see Wikipedia - https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life


def update(alive, size, iter_n):
    # TODO: Implement update rules
    # Should return set of coordinates of alive cells
    # after iter_n iterations.
    cell_neighbours = -1
    for _ in range(iter_n):
        for i in range(size[-1]):
            for j in range(size[0]):
                if (j, i) in alive:
                    for x in range(-1, 1):
                        for y in range(-1, 1):
                            if (j+x, i+y) in alive:
                                cell_neighbours += 1
                    if not (cell_neighbours == 2 or cell_neighbours == 3):
                        alive.remove((j, i))
                else:
                    for x in range(-1, 1):
                        for y in range(-1, 1):
                            if (j+x, i+y) in alive:
                                cell_neighbours += 1
                    if cell_neighbours == 3:
                        alive.add((j, i))
        cell_neighbours = -1
    return alive


def draw(alive, size):
    """
    alive - set of cell coordinates marked as alive, can be empty
    size - size of simulation grid as  tuple - ( 

    output - string showing the board state with alive cells marked with X
    """
    # TODO: implement board drawing logic and return it as output
    # Don't call print in this method, just return board string as output.
    # Example of 3x3 board with 1 alive cell at coordinates (0, 2):
    # +---+ 
    # |  X|
    # |   |
    # |   |
    # +---+
    board_drawing = "+"
    for _ in range(size[0]):
        board_drawing += "-"
    board_drawing += "+\n"
    for i in range(size[-1]):
        board_drawing += "|"
        for j in range(size[0]):
            if (j, i) in alive:
                board_drawing += "X"
            else:
                board_drawing += " "
        board_drawing += "|\n"
    board_drawing += "+"
    for _ in range(size[0]):
        board_drawing += "-"
    board_drawing += "+"
    return board_drawing
