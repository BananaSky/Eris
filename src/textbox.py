import sf
class Textbox(): 
    def __init__(self, fontsize, font):
        self._font       = font
        self._fontsize   = fontsize
        self._fontheight = fontsize - 1 

        self.text = sf.Text('', self._font, self._fontsize)

        self.processed  = []
        self.remaining  = []
        
        self.scrollback = []
        self.charbuffer = []

    def _log(self, string):
        typed          = sf.Text(string, self._font, self._fontsize)
        typed.position = self.text.position
        self.scrollback.append(typed)
        self.text.move((0, self._fontsize - 1))

    @property
    def unprocessed(self):
        unprocessed    = self.remaining
        self.remaining = []
        return unprocessed

    def update(self, windowheight):
        if len(self.scrollback) == (windowheight // self._fontheight):
            del self.scrollback[0]
            self.text.move((0, -self._fontheight))
            for item in self.scrollback:
                item.move((0, -self._fontheight))

    def draw(self, target):
        target.draw(self.text)
        for item in self.scrollback:
            target.draw(item)

    def handle(self, event):
        if type(event) is sf.TextEvent:
            char = event.unicode
            if char == '\r':
                string = ''.join(self.charbuffer)
                self._log(string)
                del self.charbuffer[:]
                self.text.string = ''
                self.remaining.append(string)
            else:
                self.charbuffer.append(char)
                self.text.string = ''.join(self.charbuffer)

        if sf.Keyboard.is_key_pressed(sf.Keyboard.BACK_SPACE):
            if len(self.charbuffer) > 0:
                self.charbuffer.pop()
