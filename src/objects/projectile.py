from .entity import Entity

class Projectile(Entity):
    def __init__(self, texture, position, velocity, rotation, ident,
                       acceleration=.001, maxVelocity=.5, damage=1):
        super().__init__(texture, position, velocity, rotation)
        self.parentIdent  = ident
        self.acceleration = acceleration
        self.maxVelocity  = maxVelocity
        self.damage       = damage

    def update(self, board):
        super().update(board)
        if self.velocity < 0 and self.velocity > -self.maxVelocity:
            self.velocity -= self.acceleration
        elif self.velocity < self.maxVelocity:
            self.velocity += self.acceleration

    def collide(self, other):
        if other.ident != self.parentIdent:
            other.damage(self.damage)

