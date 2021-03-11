import Maze
import Position
import Direction as dir
import abc

class MazeSolver:
    name = ""
    maze = 0
    costs = 0
    startPos = Position.Pos(0,0)
    goalStates = [Position.Pos(7,7), Position.Pos(8,7), Position.Pos(7,8), Position.Pos(8,8)]

    def setMaze(self, maze):
        self.maze = maze
        maxCost = maze.width * maze.height
        self.costs = [[maxCost for x in range(maze.width)] for y in range(maze.height)]
        for goal in self.goalStates:
            self.setCostAt(goal, 0)

    def getCostAt(self, po):
        if po.x >= self.maze.width or po.x < 0 or po.y >= self.maze.height or po.y < 0:
            return False
        return self.costs[po.x][po.y]

    def setCostAt(self, po, val):
        self.costs[po.x][po.y] = val
        return val

    def setCostRel(self, po, val):
        self.costs[po.x][po.y] += val
        return val

    def runSolver(self):
        steps = 0
        # while steps < (self.maze.width * self.maze.height):
        #    steps += 1
        #    self.solverStep()
        for goal in self.goalStates:
            steps += self.solverStep(goal)
        pathCost = self.getCostAt(self.startPos)
        return [pathCost, steps]

    @abc.abstractmethod
    def solverStep(self, po):
        return

    def runSolverOnMaze(self, maze):
        self.setMaze(maze)
        return self.runSolver()

    def calcPathAndUtility(self, robot):
        speed = robot.speed
        rotationPunish = robot.rotationPunish
        straightReward = robot.straightReward

        utility = 0

        path = []
        totalRotations = 0
        totalMoves = 0

        po = self.startPos
        rot = dir.north()

        while True:
            # check for goalstate
            for goal in self.goalStates:
                if po.x == goal.x and po.y == goal.y:
                    return [True, path, utility, totalMoves, totalRotations]
            # plan next move
            curMoveDir = 0
            curMoveCost = self.getCostAt(po)
            # figure out best direction based on mazeSolverValues
            for di in dir.getDir():
                neighborCost = self.getCostAt(po.getPosInDir(di))
                if neighborCost is not False and self.getCostAt(po.getPosInDir(di)) < curMoveCost and not self.maze.isMazeWallAt(po, di):
                    curMoveDir = di
                    curMoveCost = self.getCostAt(po.getPosInDir(di))
            # check whether there is a direction to move
            if curMoveDir == 0:
                return [False, path, utility, totalMoves, totalRotations]
            # move in that direction, update cost and path
            path.append(curMoveDir)
            totalMoves += 1
            utility += speed
            if curMoveDir == rot:
                utility += straightReward
            else:
                utility += rotationPunish
                totalRotations += 1
                rot = curMoveDir # update rotation
            po = po.getPosInDir(curMoveDir) # update position

    def print(self):
        print("-----------------------")
        for y in range(self.maze.height-1, -1, -1):
            for x in range(self.maze.width):
                po = Position.Pos(x, y)
                print(self.getCostAt(po), end='\t')
            print("")
        print("-----------------------")

    def getName(self):
        return self.name