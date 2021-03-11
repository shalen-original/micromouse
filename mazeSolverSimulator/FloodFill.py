import Direction as dir
import MazeSolver


class FloodFill(MazeSolver.MazeSolver):
    name = "FloodFill (classic)"

    def solverStep(self, po):
        steps = 1
        # is called for each goal state
        directions = dir.getDir()
        curCost = self.getCostAt(po)
        newCost = curCost +1
        for di in directions:
            #po.print()
            #print(di)
            posInDir = po.getPosInDir(di)
            #posInDir.print()
            # print(self.maze.isMazeWallAt(po, di))
            if self.maze.isMazeWallAt(po, di) == False and self.getCostAt(posInDir) > newCost:
                self.setCostAt(posInDir, newCost)
                steps += self.solverStep(posInDir)
        return steps