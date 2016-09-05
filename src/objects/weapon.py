from time        import time
from .projectile import Projectile

from ..tools import sf

class Weapon:
    def __init__(self, period=1, damage=10, x=10, y=10):
        self.period = period
        self.damage = damage
        self.last   = time()

        image   = sf.Image.create(x, y, sf.Color(0, 0, 0,0))

        for j in range(y):
            for i in range(x):
                pixel = image[i, j]
                image[i, j] = sf.Color(0, 0, 255, 255)

        texture = sf.Texture.create(image.width, image.height)
        texture = texture.from_image(image)

        self.projectileTexture = texture

    def use(self, position, velocity, rotation):
        passed = time() - self.last
        if passed > self.period:
            self.last = time()
            return Projectile(self.projectileTexture, position, velocity, rotation)
        else:
            return None



