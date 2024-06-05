class Game:
    
    def __init__(self, word):
        self.letterFound = [False, False, False, False]
        self.missedLetters = 0
        self.badGuesses = 0
        self.lettersRequested = []
        self.success = True
        self.word = word
        self.currentGuess = ['-', '-', '-', '-']
        self.score = 0.00