import Position
# solved via Integers

def north():
    return 0b0001
def east():
    return 0b0010
def south():
    return 0b0100
def west():
    return 0b1000


def getDir():
    return [north(), east(), south(), west()]


def inverseDir(dir):
    if dir == north():
        return south()
    elif dir == east():
        return west()
    elif dir == south():
        return north()
    elif dir == west():
        return east()
    else:
        return 0


def getPositionFromDir(dir):
    posChange = Position.Pos(0, 0)
    if dir & north() > 0:
        posChange.y += 1
    elif dir & south() > 0:
        posChange.y -= 1
    if dir & east() > 0:
        posChange.x += 1
    elif dir & west() > 0:
        posChange.x -= 1
    return posChange