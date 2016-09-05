#!/usr/bin/env python3

import src.tools.sf as sf

from src.tools   import *
from src.objects import *

if __name__ == '__main__':
    resources = load()


    player = Player()
    board  = Board(resources, 'Eris', 1200, 1200)

    player.move((board.window.width/2, board.window.height/2))
    board.add_entity(player)
    board.run()

