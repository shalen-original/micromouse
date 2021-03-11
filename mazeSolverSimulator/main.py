import Maze
import Position
import Direction as dir
import MazeSolver
import FloodFill
import MazeDataImporter
import Robot


def main():
    robot = Robot.Robot(0.1, -0.1) # rotationPunish, straightReward
    #
    mazes = MazeDataImporter.getMazes()
    print("Testdata loaded: " + str(len(mazes)) + " Mazes")
    # init algorithms
    floodfill = FloodFill.FloodFill()
    #
    algos = [floodfill]
    #
    for alg in algos:
        print("-------------------")
        print("Algorithm: " + alg.getName())
        for mazeIndex in range(0, 1):#len(mazes)):
            maze = mazes[mazeIndex]
            [cost, steps] = alg.runSolverOnMaze(maze)
            [success, path, utility, totalMoves, totalRotations] = alg.calcPathAndUtility(robot)
            if success:
                print("" + maze.getName() + " cost: " + str(cost), "steps: " + str(steps))
                alg.print()
                print("Utility: " + str(utility) + "\t" + "#Moves: " + str(totalMoves) + "\t#Rotations: " + str(totalRotations))
                print("Path: " + str(path))


if __name__ == '__main__':
    main()

    #TODO implement other floodfill (rotation punish, l2norm, ...)