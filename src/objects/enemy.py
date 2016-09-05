from .character import Character
from ..tools import angle_between

class Enemy(Character):
    def __init__(self, faction):
        super().__init__(faction)
        self.shooting = True

    def update(self, board):
        super().update(board)
        if self.shooting:
            self.shoot(board)

    def interact(self, other):
        if hasattr(other, 'faction'):
            angle = angle_between(other.position, self.position)
            print(angle)
            self.rotation = angle
            if other.faction != self.faction:
                print('Shooting')
                self.velocity = 0.1



