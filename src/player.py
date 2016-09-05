from ship       import Ship

import sf
from sf import key

class Player(Ship):

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
            projectile = self.weapon.use(self.texture, self.position, self.velocity, self.rotation)
            if projectile is not None:
                board.queue(projectile)
