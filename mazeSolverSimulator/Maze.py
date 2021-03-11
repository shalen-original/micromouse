import Position
import Direction as dir
import numpy as np


class Maze:
    width = 16
    height = 16
    maze = 0
    name = 'Custom'

    def __init__(self):
        self.maze = [[0 for x in range(self.width)] for y in range(self.height)]
        for  xi in range(0, self.width):
            self.maze[xi][0] |= dir.south()
            self.maze[xi][self.height - 1] |= dir.north()
        for yi in range(0, self.height):
            self.maze[0][yi] |= dir.west()
            self.maze[self.width-1][yi] |= dir.east()

    #def getNeighborCellInDir(self, posi, direc):
    #    posChange = dir.getPositionFromDir(direc)
    #    neighborPos = Position.Pos(posi.x + posChange.x, posi.y + posChange.y)
    #    return self.getCellAt(neighborPos)

    def getCellAt(self, po):
        return self.maze[po.x][po.y]

    def setCellAt(self, po, val):
        self.maze[po.x][po.y] = val
        return val

    def setOrCell(self, po, val):
        self.maze[po.x][po.y] |= val
        return val

    def setAndCell(self, po, val):
        self.maze[po.x][po.y] &= val
        return val

    def addMazelWall(self, po, di):
        if di & dir.north() >= 1:
            nPos = po.getPosInDir(dir.north())
            self.setOrCell(po, dir.north())
            self.setOrCell(nPos, dir.south())
        if di & dir.south() >= 1:
            nPos = po.getPosInDir(dir.south())
            self.setOrCell(po, dir.south())
            self.setOrCell(nPos, dir.north())
        if di & dir.east() >= 1:
            nPos = po.getPosInDir(dir.east())
            self.setOrCell(po, dir.east())
            self.setOrCell(nPos, dir.west())
        if di & dir.west() >= 1:
            nPos = po.getPosInDir(dir.west())
            self.setOrCell(po, dir.west())
            self.setOrCell(nPos, dir.east())
        return 1

    def removeMazeWall(self, po, di):
        return 0

    def isMazeWallAt(self, po, di):
        return (self.getCellAt(po) & di) == di

    def print(self):
        print("-----------------------")
        for y in range(self.height-1, -1, -1):
            for x in range(self.width):
                po = Position.Pos(x, y)
                print(self.getCellAt(po), end='\t')
            print("")
        print("-----------------------")

    def loadFromFile(self, filename):
        data = open("mazes/" + str(filename) + "", "r")
        allLines = data.readlines()
        for lineIndex in range(1, len(allLines)-1):
            line = allLines[lineIndex]
            # even line
            self.loadEvenLine(lineIndex, line)
            # odd line
            lineIndex += 1
            line = allLines[lineIndex]
            self.loadOddLine(lineIndex, line)
        self.loadEvenLine(len(allLines)-1, allLines[len(allLines)-1])
        data.close()
        self.name = str(filename)
        return self

    def loadOddLine(self, index, line):
        for xi in range(0, self.width):
            lineX = int(xi * 2 + 1)
            if lineX < 0 or lineX >= len(line):
                print("error at:" + str(xi) + ", " + str(lineX) + "\t" + str(line))
            if line[lineX] == "-":
                y = self.height - int(index / 2) - 1
                po = Position.Pos(xi, y)
                self.addMazelWall(po, dir.north())

    def loadEvenLine(self, index, line):
        for xi in range(1, self.width):
            lineX = xi * 2
            if line[lineX] == "|":
                y = self.height - int(index / 2) - 1
                po = Position.Pos(xi, y)
                self.addMazelWall(po, dir.west())
                # print("wall added")

    def getName(self):
        return self.name