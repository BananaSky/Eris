import sf
import os

from collections import namedtuple

Resources = namedtuple('Resources', ['textures'])

def load_texture(filepath):
    try: 
        return sf.Texture.from_file(filepath)
    except IOError as e: 
        print(e)
        exit(1)

def load(directory='../resources/'):

    textureDict = {}

    for (dirpath, dirnames, filenames) in os.walk(directory):
        basename = os.path.basename(dirpath)
        if basename == 'textures':
            for filename in filenames:
                filepath = os.path.join(dirpath, filename)
                noext    = os.path.splitext(filename)[0]
                textureDict[noext] = load_texture(filepath)

    return Resources(textureDict)

