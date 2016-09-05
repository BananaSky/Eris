from . import sf
from math   import radians, degrees, cos, sin, atan2, ceil, sqrt
from random import randint, choice

def gen_texture(x, y):
    image   = sf.Image.create(x, y, sf.Color(0, 0, 0,0))

    for j in range(y):
        for i in range(x):
            pixel = image[i, j]
            image[i, j] = sf.Color(0, 0, 255, 255)

    texture = sf.Texture.create(image.width, image.height)
    texture = texture.from_image(image)
    return texture

def collide(a, b):
    a.collide(b)
    b.collide(a)

def distance(a, b):
    dx = abs(a.position.x - b.position.x)
    dy = abs(a.position.y - a.position.y)
    return sqrt(dx * dx + dy * dy)

def angle_between(a, b):
    x1, y1 = a
    x2, y2 = b
    angle = atan2(y1 - y2, x1 - x2)
    angle = (degrees(angle) - 90) % 360
    return angle

