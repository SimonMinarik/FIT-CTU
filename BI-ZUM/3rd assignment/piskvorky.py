from copy import deepcopy
import math

totalNodes = 0
tilesOccupied = 0

winningLines = [{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}, {1, 5, 9, 13}, {2, 6, 10, 14},
                {3, 7, 11, 15}, {4, 8, 12, 16}, {1, 6, 11, 16}, {4, 7, 10, 13}]


class State:
    def __init__(self, player):
        self.player = player
        self.board = {}
        self.quality = 0
        self.possibleStates = {}
        self.xPlayerTiles = set()
        self.yPlayerTiles = set()
        for y in range(0, 4):
            for x in range(0, 4):
                self.board[x, y] = '_'

    def printBoard(self):
        for x in range(0, 4):
            for y in range(0, 4):
                print(f' {self.board[x, y]} ', end="")
            print()


def getPossibleStates(state):
    possibleStates = []
    for i in range(0, 4):
        for j in range(0, 4):
            if state.board[i, j] == '_':
                possibleBoard = deepcopy(state.board)
                possibleBoard[i, j] = state.player
                possibleState = State(state.player)
                possibleState.xPlayerTiles = deepcopy(state.xPlayerTiles)
                possibleState.yPlayerTiles = deepcopy(state.yPlayerTiles)
                if possibleState.player == 'X':
                    possibleState.player = 'Y'
                    possibleState.xPlayerTiles.add(i * 4 + j + 1)
                else:
                    possibleState.player = 'X'
                    possibleState.yPlayerTiles.add(i * 4 + j + 1)
                possibleState.board = possibleBoard
                possibleState.quality = state.quality
                possibleStates.append(possibleState)

    return possibleStates


def getUtility(state):
    for x in winningLines:
        if x.issubset(state.xPlayerTiles):
            return -1000
        elif x.issubset(state.yPlayerTiles):
            return 1000
    return 0


def checkTerminalState(state):
    for x in winningLines:
        if x.issubset(state.xPlayerTiles) or x.issubset(state.yPlayerTiles):
            return True
    if tilesOccupied == 4 * 4:
        return True
    return False


def maxi(state, alpha, beta):
    global totalNodes
    totalNodes += 1
    if checkTerminalState(state):
        return getUtility(state)
    quality = -math.inf
    state.possibleStates = getPossibleStates(state)
    if totalNodes > 100000:
        return evalFunc(state)
    for a in state.possibleStates:
        quality = max(quality, mini(a, alpha, beta))
        a.quality = quality
        if quality >= beta:
            return quality
        alpha = max(alpha, quality)
    return quality


def mini(state, alpha, beta):
    if checkTerminalState(state):
        return getUtility(state)
    quality = math.inf
    new_beta = beta
    state.possibleStates = getPossibleStates(state)
    for a in state.possibleStates:
        quality = min(quality, maxi(a, alpha, new_beta))
        a.quality = quality
        if quality <= alpha:
            return quality
        new_beta = min(new_beta, quality)
    return quality


def evalFunc(state):
    x = {0: 0, 1: 0, 2: 0, 3: 0, 4: 0}
    o = {0: 0, 1: 0, 2: 0, 3: 0, 4: 0}

    for r in range(0, 4):
        numberOfXs = 0
        numberOfOs = 0
        for c in range(0, 4):
            if state.board[r, c] == 'O':
                numberOfOs += 1
            elif state.board[r, c] == 'X':
                numberOfXs += 1
        if numberOfOs == 0:
            o[numberOfXs] += 1
        if numberOfXs == 0:
            x[numberOfOs] += 1

    for c in range(0, 4):
        numberOfXs = 0
        numberOfOs = 0
        for r in range(0, 4):
            if state.board[r, c] == 'O':
                numberOfOs += 1
            elif state.board[r, c] == 'X':
                numberOfXs += 1
        if numberOfOs == 0:
            o[numberOfXs] += 1
        if numberOfXs == 0:
            x[numberOfOs] += 1

    numberOfXs = 0
    numberOfOs = 0
    for i in range(0, 4):
        if state.board[i, i] == 'O':
            numberOfOs += 1
        elif state.board[i, i] == 'X':
            numberOfXs += 1
    if numberOfOs == 0:
        o[numberOfXs] += 1
    if numberOfXs == 0:
        x[numberOfOs] += 1

    numberOfXs = 0
    numberOfOs = 0
    for i in range(0, 4):
        if state.board[4 - i - 1, i] == 'O':
            numberOfOs += 1
        elif state.board[4 - i - 1, i] == 'X':
            numberOfXs += 1
    if numberOfOs == 0:
        o[numberOfXs] += 1
    if numberOfXs == 0:
        x[numberOfOs] += 1

    return (10 * x[3] + 5 * x[2] + x[1]) - (10 * o[3] + 5 * o[2] + o[1])


def main():
    global totalNodes, tilesOccupied
    game = State('X')
    game.printBoard()
    while not checkTerminalState(game):
        while True:
            try:
                x = int(input("Enter row (0-3): "))
                if x not in game.yPlayerTiles or x not in game.xPlayerTiles:
                    break
                else:
                    print("Tile is occupied")
            except ValueError:
                print("Only numbers (0-3)")
        while True:
            try:
                y = int(input("Enter column (0-3): "))
                if x not in game.yPlayerTiles or x not in game.xPlayerTiles:
                    break
                else:
                    print("Tile is occupied")
            except ValueError:
                print("Only numbers (0-3)")
        game.board[x, y] = 'X'
        game.xPlayerTiles.add(x * 4 + y + 1)
        tilesOccupied += 1
        game.player = 'O'
        game.printBoard()
        if checkTerminalState(game):
            break
        quality = maxi(game, -1000, 1000)
        game = list(filter(lambda z: z.quality == quality, game.possibleStates))[0]
        for x in range(4):
            for y in range(4):
                if game.board[x, y] == 'O':
                    game.yPlayerTiles.add(x * 4 + y + 1)
        game.printBoard()
        tilesOccupied += 1
        totalNodes = 0


if __name__ == "__main__":
    main()
