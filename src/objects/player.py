from .character import Character

from ..tools import sf
from ..tools.sf import key

class Player(Character):

    def __init__(self):
        super().__init__('player')

    def update(self, board):
        super().update(board)
        if key('A') or key('LEFT'):
            self.rotate(-.05)

        if key('D') or key('RIGHT'):
            self.rotate(.05)

        if key('W') or key('UP'):
            self.velocity -= .00005

        if key('S') or key('DOWN'):
            self.velocity += .00005

        if key('SPACE'):
            self.shoot(board)

    def interact(self, other):
        pass
