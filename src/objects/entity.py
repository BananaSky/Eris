from ..tools import sf, distance
from math import cos, sin, radians

class Entity(sf.Sprite):

    def __init__(self, texture, position=(0,0), velocity=0, rotation=0, life=100,
                 interactdistance=10):
        super().__init__(texture)
        self.ident    = 0 
        self.origin   = (self.local_bounds.width/2, self.local_bounds.height/2) 
        self.position = position
        self.velocity = velocity
        self.rotation = rotation
        self.life     = life
        self.interactdistance = interactdistance

    def update(self, board):
        rotation = radians((self.rotation + 90) % 360)
        self.move((self.velocity * cos(rotation), self.velocity * sin(rotation)))

    def render(self, target):
        target.draw(self)

    def handle(self, event):
        pass

    def touches(self, other):
        return self.global_bounds.intersects(other.global_bounds)

    def interacts(self, other):
        if distance(self, other) < self.interactdistance:
            return True
        else:
            return False

    def interact(self, other):
        pass

    def collide(self, other):
        pass

    def damage(self, amount):
        self.life -= amount

    def alive(self):
        return self.life > 0
