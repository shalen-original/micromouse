import Direction as dir
import numpy as np

class Pos:
    x = 0
    y = 0

    def __init__(self, xi, yi):
        self.x = xi
        self.y = yi

    def getDirection(self):
        direction = 0
        if self.x == 1 and self.y == 0:
            direction = dir.east()
        if self.x == -1 and self.y == 0:
            direction = dir.west()
        if self.x == 0 and self.y == 1:
            direction = dir.north()
        if self.x == 0 and self.y == -1:
            direction = dir.south()
        return direction

    def getPosInDir(self, di):
        posChange = dir.getPositionFromDir(di)
        return self.getPosOffset(posChange)

    def getPosOffset(self, po):
        posVal = Pos(po.x + self.x, po.y + self.y)
        return posVal

    def getL2Norm(self, po):
        dist = np.sqrt(np.abs(po.x*po.x - self.x*self.x + po.y*po.y - self.y*self.y))
        return dist

    def getString(self):
        x = str(self.x)
        y = str(self.y)
        return "(" + x + ", " + y + ")"

    def print(self):
        print(self.getString())
