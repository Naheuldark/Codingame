import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

width, height = [int(i) for i in input().split()]
maze = []
for i in range(height):
    line = input()
    maze.append(line)
side = input()

def getPlayer(maze): #finds player, returns coordinates (x, y) in the maze and direction the player is facing
	playerStates = {'>': 'right', 'v': 'down', '<': 'left', '^': 'up'}
	for i, row in enumerate(maze):
		for j, char in enumerate(row):
			if char in playerStates:
				return((j, i), playerStates[char])   

def getAdjCells(playerCoords = tuple, maze = list): #find adjacent cells that player can move to || returns dictionary of possible moves
    x, y = playerCoords
    temp = {'right': (x+1, y), 'down': (x, y+1), 'left': (x-1, y), 'up':(x, y-1)}
    cells = {direction:temp[direction] for direction in temp if isValidMove(temp[direction], maze)}
    
    return cells

def isValidMove(coords = tuple, maze = list): #check if suggested move is valid (in bounds and not a wall)
	x, y = coords
	if x >= 0 and x <= len(maze[0])-1 and y >= 0 and y <= len(maze)-1 and maze[y][x] != '#':
		return True
	else:
		return False

def getDirection(moves = dict, facing = str, sideToFollow = str): #find direction of the next move || returns tuple (directionStr, (newCoords))
	if len(moves) == 0:
	    return('stay', (0, 0))
	if len(moves) == 1:
		return list(moves.items())[0]

	turnsOrder = {'L': ['up', 'right', 'down', 'left'], 'R':['right', 'up', 'left', 'down']}

	if sideToFollow != 'L' and sideToFollow != 'R':
		raise Exception("getDirection invalid sideToFollow")

	for i, value in enumerate(turnsOrder[sideToFollow]):
		if facing == value:
			temp = []

			for j in range(-1, 2):
				if i+j < len(turnsOrder[sideToFollow]):
					temp.append(turnsOrder[sideToFollow][i+j])
				else:
					temp.append(turnsOrder[sideToFollow][0])
			
			for direction in temp:
				if direction in moves:
					return (direction, moves[direction])

	raise Exception("getDirection no valid moves while following %s side and facing %s" % (sideToFollow, facing))

def makeMove(playerCoords = tuple, direction = str, moveCoords = (tuple), movesMade = list):
	if direction == 'stay':
	    return(playerCoords, direction)
	
	currentX, currentY = playerCoords

	movesMade[currentY][currentX] = str(int(movesMade[currentY][currentX]) + 1)

	return (moveCoords, direction)

def initMovesHistory(maze):
	movesHistory = []
	for row in maze:
		tempRow = [char if char == '#' else '0' for char in row]
		movesHistory.append(tempRow)
	return movesHistory

# initialize new maze to count moves
movesHistory = initMovesHistory(maze)

# initialize point of origin and direction of the player
initialCoords, initialFacing = getPlayer(maze)

originalCoords = initialCoords

while True:
	possibleMoves = getAdjCells(initialCoords, maze) # scan around the player for possible moves
	nextFacing, nextCoords = getDirection(possibleMoves, initialFacing, side) # see where player should be moving to
	initialCoords, initialFacing = makeMove(initialCoords, nextFacing, nextCoords, movesHistory) #make the move, set player location and direction to the new cell

	if initialCoords == originalCoords:
		break

for row in movesHistory:
	print(''.join(row))