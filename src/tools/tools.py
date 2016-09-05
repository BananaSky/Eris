from . import sf

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

