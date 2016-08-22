#!/usr/bin/env python3

import sf

from load   import load
from board  import Board
from player import Player

if __name__ == '__main__':
    try: 
        texture = sf.Texture.from_file("../resources/ship.png")
    except IOError as e: 
        print(e)
        exit(1)

    player = Player(texture)

    resources = load()
    board     = Board(resources, 'Eris', 1200, 1200)
    player.move((board.window.width/2, board.window.height/2))
    board.add_entity(player)
    board.run()

