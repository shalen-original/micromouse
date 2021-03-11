import Position
import Direction as dir

class Robot:
    # TODO set actualy data here (best would be time needed for generic move, time for toation, time save for moving straight)
    speed = 1
    rotationPunish = 0.1
    straightReward = -0.1

    def __init__(self, rotPunish, strReward):
        self.rotationPunish = rotPunish
        self.straightReward = strReward