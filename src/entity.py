import sf
from math import cos, sin, radians

class Entity(sf.Sprite):

    def __init__(self, texture):
        super().__init__(texture)
        print(self.local_bounds)
        self.origin   = (self.local_bounds.width/2, self.local_bounds.height/2) 
        self.velocity = 0

    def update(self, board):
        rotation = radians((self.rotation + 90) % 360)
        self.move((self.velocity * cos(rotation), self.velocity * sin(rotation)))

    def render(self, target):
        target.draw(self)

    def handle(self, event):
        pass
