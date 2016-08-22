#!/usr/bin/env python3
import sf
from load    import load

from textbox import Textbox


class Board():
    def __init__(self, resources, title='', width=680, height=440):
        self.window    = sf.RenderWindow(sf.VideoMode(width, height), title)
        self.resources = resources
        self.entities  = {}
        self.entityID  = 0

    def add_entity(self, entity):
        self.entities[self.entityID] = entity
        self.entityID += 1

    def _handle(self, event):
        if type(event) is sf.CloseEvent:
            self.window.close()
        for entity in self.entities.values():
            entity.handle(event)

    def _render(self):
        for entity in self.entities.values():
            entity.render(self.window)

    def _update(self):
        for entity in self.entities.values():
            entity.update(self)

    def run(self):
        while self.window.is_open:
            for event in self.window.events:
                self._handle(event)

            self._update()
            self.window.clear() 
            self._render()
            self.window.display() 



