from .ship import Ship

class Character(Ship):
    def __init__(self, faction):
        super().__init__()
        self.faction = faction
        self.interactdistance = 500
