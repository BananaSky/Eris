from sfml.graphics import *
from sfml.window   import *
from sfml.system   import *
from sfml.audio    import *

def key(name):
    return Keyboard.is_key_pressed(getattr(Keyboard, name))
