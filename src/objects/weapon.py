from time        import time
from .projectile import Projectile

from ..tools import sf
from ..tools import gen_texture

class Weapon:
    def __init__(self, period=.5, damage=10, x=10, y=10):
        self.period = period
        self.damage = damage
        self.last   = time()

        self.projectileTexture = gen_texture(x, y)

    def use(self, position, velocity, rotation, ident):
        passed = time() - self.last
        if passed > self.period:
            self.last = time()
            return Projectile(self.projectileTexture, position, velocity, rotation, ident)
        else:
            return None



