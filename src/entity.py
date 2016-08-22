import sf

class Entity(sf.Sprite):

    def update(self, board):
        pass

    def render(self, target):
        target.draw(self)

    def handle(self, event):
        pass
