from time       import time
from projectile import Projectile

class Weapon:
    def __init__(self, period=1, damage=10):
        self.period = period
        self.damage = damage
        self.last   = time()

    def use(self, texture, position, velocity, rotation):
        passed = time() - self.last
        if passed > self.period:
            self.last = time()
            return Projectile(texture, position, velocity, rotation)
        else:
            return None



