from .entity import Entity
from .weapon import Weapon
from ..tools import sf, gen_texture

class Ship(Entity):

    def __init__(self, x=20, y=20):
        texture = gen_texture(x, y)
        super().__init__(texture)
        self.weapon = Weapon()

    def shoot(self, board):
        projectile = self.weapon.use(self.position, self.velocity, self.rotation, self.ident)
        if projectile is not None:
            board.queue(projectile)

    def collide(self, other):
        other.damage(self.velocity)

