import sys
import os
from collections import defaultdict
import time
from termcolor import colored
from queue import PriorityQueue, Queue, LifoQueue
import random


def main(argv):
    if not 1 < len(argv) < 3:
        print("Wrong input, try again.\nCorrect format: file algorithm\nExample: python prohledavaci_algoritmy.py testovaci_data/00_11_11_1550177690.txt astar")
        exit(0)
    elif not os.access(argv[0], os.R_OK):
        print("File couldn't be opened, try again.\nCorrect format: file algorithm\nExample: python prohledavaci_algoritmy.py testovaci_data/00_11_11_1550177690.txt astar")
        exit(0)
    elif not argv[1].upper() in ["DFS", "BFS", "RANDOMSEARCH", "GREEDYSEARCH", "DIJKSTRA", "ASTAR"]:
        print(
            "Algorithm couldn't be found.\nPossible algorithms: BFS, DFS, randomSearch, greedySearch, dijkstra, aStar")
        exit(0)
    labyrinth, graph, start, end = loadFile(argv[0])

    if argv[1].upper() == "DFS":
        visited, path = DFS(graph, start, end, labyrinth)
    elif argv[1].upper() == "BFS":
        visited, path = BFS(graph, start, end, labyrinth)
    elif argv[1].upper() == "GREEDYSEARCH":
        visited, path = greedySearch(graph, start, end, labyrinth)
    elif argv[1].upper() == "RANDOMSEARCH":
        visited, path = randomSearch(graph, start, end, labyrinth)
    elif argv[1].upper() == "DIJKSTRA":
        visited, path = dijkstra(graph, start, end, labyrinth)
    elif argv[1].upper() == "ASTAR":
        visited, path = aStar(graph, start, end, labyrinth)
    printlabyrinth(start, end, labyrinth, visited, path)


def loadFile(fileName):
    file = open(fileName, "r")
    y = 0
    x = 0
    labyrinth = []
    graph = defaultdict(list)
    for line in file.readlines():
        if line[0] == "X":
            labyrinth.append(line)
        elif line[0] == "s":
            start = (int(line[line.find(" ") + 1:line.find(",")]), int(line[line.find(" ", line.find(" ") + 1) + 1:-1]))
        elif line[0] == "e":
            end = (int(line[line.find(" ") + 1:line.find(",")]), int(line[line.find(" ", line.find(" ") + 1) + 1:-1]))

    for line in labyrinth:
        for letter in line:
            if letter == " ":
                if labyrinth[y - 1][x] == " ":
                    graph[(x, y)].append((x, y - 1))
                if labyrinth[y][x + 1] == " ":
                    graph[(x, y)].append((x + 1, y))
                if labyrinth[y + 1][x] == " ":
                    graph[(x, y)].append((x, y + 1))
                if labyrinth[y][x - 1] == " ":
                    graph[(x, y)].append((x - 1, y))
            x += 1
        x = 0
        y += 1

    return labyrinth, graph, start, end


def printlabyrinth(start, end, labyrinth, visited, path=None):
    x = 0
    y = 0
    for line in labyrinth:
        printedLine = ""
        for char in line:
            if (x, y) == start:
                if start == end:
                    printedLine += "Ω"
                else:
                    printedLine += "S"
            elif (x, y) == end:
                printedLine += "E"
            elif path and (x, y) in path:
                printedLine += "o"
            elif (x, y) in visited:
                printedLine += "."
            elif char == "X" or char == " ":
                printedLine += char
            x += 1
        x = 0
        y += 1
        for char in printedLine:
            if char == "o":
                print(colored(char, "green"), end="")
            elif char in ["S", "E", "Ω"]:
                print(colored(char, "red"), end="")
            else:
                print(char, end="")
        print()
    print("hmmm")
    if start == end:
        print("That was easy.. Start == End")
    # time.sleep(0.1)


def BFS(graph, start, goal, labyrinth):
    opened = Queue()
    opened_iterable = {start}
    closed = set()
    prev = {}
    opened.put(start)
    while not opened.empty():
        x = opened.get()
        opened_iterable.remove(x)
        if x == goal:
            return closed, reconstructPath(prev, x)
        for y in graph[x]:
            if y not in opened_iterable.union(closed):
                opened.put(y)
                opened_iterable.add(y)
                prev[y] = x
        closed.add(x)
        printlabyrinth(start, goal, labyrinth, closed)

def DFS(graph, start, goal, labyrinth):
    opened = LifoQueue()
    closed = set()
    prev = {}
    opened_iterable = {start}
    opened.put(start)
    while not opened.empty():
        x = opened.get()
        opened_iterable.remove(x)
        if x == goal:
            return closed, reconstructPath(prev, x)
        for y in reversed(graph[x]):
            if y not in opened_iterable.union(closed):
                opened.put(y)
                opened_iterable.add(y)
                prev[y] = x
        closed.add(x)
        printlabyrinth(start, goal, labyrinth, closed)

def randomSearch(graph, start, goal, labyrinth):
    opened = {start}
    closed = set()
    prev = {}
    while opened:
        x = random.choice(tuple(opened))
        if x == goal:
            return closed, reconstructPath(prev, x)
        for y in graph[x]:
            if y not in opened.union(closed):
                opened.add(y)
                prev[y] = x
        opened.remove(x)
        closed.add(x)
        printlabyrinth(start, goal, labyrinth, closed)

def greedySearch(graph, start, goal, labyrinth):
    opened = PriorityQueue()
    opened_iterable = {start}
    closed = set()
    prev = {}
    opened.put((manhattanDistance(start, goal), start))
    while not opened.empty():
        x = opened.get()
        opened_iterable.remove(x[1])
        if x[1] == goal:
            return closed, reconstructPath(prev, x[1])
        for y in graph[x[1]]:
            if y not in opened_iterable.union(closed):
                opened.put((manhattanDistance(y, goal), y))
                opened_iterable.add(y)
                prev[y] = x[1]
        closed.add(x[1])
        printlabyrinth(start, goal, labyrinth, closed)

def dijkstra(graph, start, goal, labyrinth):
    Q = PriorityQueue()
    dist = {}
    prev = {}
    Q.put((0, start))
    dist[start] = 0
    visited = [start]
    while not Q.empty():
        x = Q.get()
        visited.append(x[1])
        if x[1] == goal:
            return visited, reconstructPath(prev, x[1])
        for y in graph[x[1]]:
            d = dist[x[1]] + 1
            if y not in dist.keys() or d < dist[y]:
                if y not in dist.keys():
                    Q.put((d, y))
                else:
                    Q = changeQueueKey(Q, y, d)
                dist[y] = d
                prev[y] = x[1]
        printlabyrinth(start, goal, labyrinth, visited)


def aStar(graph, start, goal, labyrinth):
    opened = PriorityQueue()
    dist = {}
    prev = {}
    closed = set()
    opened.put((manhattanDistance(start, goal), start))
    opened_iterable = {start}
    dist[start] = 0
    while not opened.empty():
        x = opened.get()
        opened_iterable.remove(x[1])
        if x[1] == goal:
            return closed, reconstructPath(prev, x[1])
        for y in set(graph[x[1]]).difference(closed):
            d = dist[x[1]] + 1
            if y not in opened_iterable or dist[y] > d:
                dist[y] = d
                prev[y] = x[1]
                if y not in opened_iterable:
                    opened.put((d + manhattanDistance(y, goal), y))
                    opened_iterable.add(y)
                else:
                    opened = changeQueueKey(opened, y, d + manhattanDistance(y, goal))
                    opened_iterable.add(y)
        closed.add(x[1])
        printlabyrinth(start, goal, labyrinth, closed)


# heuristic
def manhattanDistance(start, goal) -> int:
    return abs(start[0] - goal[0]) + abs(start[1] - goal[1])


def reconstructPath(prev, x):
    path = [x]
    while x in prev.keys():
        path.append(prev[x])
        x = prev[x]
    return path


def changeQueueKey(queue, key, new_val):
    temp_list = []
    new_queue = PriorityQueue()
    while not queue.empty():
        x = queue.get()
        print(x)
        if x[1] == key:
            temp_list.append((new_val, x[1]))
        else:
            temp_list.append(x)
    for x in temp_list:
        new_queue.put((x[0], x[1]))
    return new_queue


if __name__ == '__main__':
    main(sys.argv[1:])
