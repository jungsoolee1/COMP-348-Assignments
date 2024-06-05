import random

class StringDatabase:

    def __init__(self):
        f = open("four_letters.txt", "r")
        stringToSplit = f.read()
        self.words = stringToSplit.split()
        f.close()
    
    def pickWord(self):
        return random.choice(self.words)
