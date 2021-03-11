import os
import Maze

def getMazes():
    mazes = []
    for filename in os.listdir("mazes"):
        if filename.endswith(".maze"):
            newMaze = Maze.Maze().loadFromFile(filename)
            # print(filename + " is done!")
            mazes.append(newMaze)
    return mazes