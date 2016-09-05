from ..tools import sf
from math import cos, sin, radians

class Entity(sf.Sprite):

    def __init__(self, texture, position=(0,0), velocity=0, rotation=0):
        super().__init__(texture)
        self.origin   = (self.local_bounds.width/2, self.local_bounds.height/2) 
        self.position = position
        self.velocity = velocity
        self.rotation = rotation

    def update(self, board):
        rotation = radians((self.rotation + 90) % 360)
        self.move((self.velocity * cos(rotation), self.velocity * sin(rotation)))

    def render(self, target):
        target.draw(self)

    def handle(self, event):
        pass
