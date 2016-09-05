from entity import Entity
from weapon import Weapon
import sf

class Ship(Entity):

    def __init__(self, x=20, y=20):
        image   = sf.Image.create(x, y, sf.Color(0, 0, 0,0))
        texture = sf.Texture.create(image.width, image.height)

        for j in range(y):
            for i in range(x):
                pixel = image[i, j]
                image[i, j] = sf.Color(0, 255, 0, 255)

        texture = texture.from_image(image)
        super().__init__(texture)

        self.weapon = Weapon()
