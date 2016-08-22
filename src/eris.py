#!/usr/bin/env python3

import sf

from load   import load
from board  import Board
from entity import Entity

if __name__ == '__main__':
    try: 
        texture = sf.Texture.from_file("../resources/image.jpg")
    except IOError: 
        exit(1)

    entity = Entity(texture)

    resources = load()
    board     = Board(resources)
    board.add_entity(entity)
    board.run()

