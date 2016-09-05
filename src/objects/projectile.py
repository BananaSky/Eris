from .entity import Entity

from time import time

class Projectile(Entity):
    def __init__(self, texture, position, velocity, rotation, ident,
                       acceleration=.001, maxVelocity=.5, damage=1, duration=1):
        super().__init__(texture, position, velocity, rotation)
        self.parentIdent  = ident
        self.acceleration = acceleration
        self.maxVelocity  = maxVelocity
        self.damageamount = damage
        self.duration     = duration

        self.created = time()

    def update(self, board):
        super().update(board)
        if self.velocity < 0 and self.velocity > -self.maxVelocity:
            self.velocity -= self.acceleration
        elif self.velocity < self.maxVelocity:
            self.velocity += self.acceleration

        elapsed = time() - self.created
        if elapsed > self.duration:
            self.life = 0

    def collide(self, other):
        if other.ident != self.parentIdent:
            print('Projectile damaged entity')
            other.damage(self.damageamount)

