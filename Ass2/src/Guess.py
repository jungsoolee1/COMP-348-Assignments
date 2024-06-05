import os
from Game import Game
from StringDatabase import StringDatabase


dog = 2

class Guess:
    frequencies = {
        "a": 8.17,
        "b": 1.49,
        "c": 2.78,
        "d": 4.25,
        "e": 12.70,
        "f": 2.23,
        "g": 2.02,
        "h": 6.09,
        "i": 6.97,
        "j": 0.15,
        "k": 0.77,
        "l": 4.03,
        "m": 2.41,
        "n": 6.75,
        "o": 7.51,
        "p": 1.93,
        "q": 0.10,
        "r": 5.99,
        "s": 6.33,
        "t": 9.06,
        "u": 2.76,
        "v": 0.98,
        "w": 2.36,
        "x": 0.15,
        "y": 1.97,
        "z": 0.07
    }
    
    
    def start( self, cmdArg):
        listOfGames = []
        dog = 4
        print(dog)
        stringDatabase = StringDatabase()
        if cmdArg == "play":
            Testing = False
        else:
            Testing = True
        nextGame = True
        gameNumber = -1
        #continues to next game after previous game finishes
        while nextGame:
            gameNumber += 1
            word = stringDatabase.pickWord()
            game = Game(word)
            listOfGames.append(game)
            notDone = True
            #keeps the same game going until give up or won
            while notDone:
                os.system('clear')
                print("++\n++ The great guessing game\n++\n")
                #Checking the mode of the game
                if Testing:
                    print("Current Word:\t" + game.word)
                print("Current Guess:\t", end="")
                for x in game.currentGuess:
                    print(x, end="")
                print("\nLetters guessed: ", end="")
                for x in game.lettersRequested:
                    print(x + " ", end="")
                option = input("\n\ng = guess, t = tell me, 1 for a letter, and q to quit\n\nEnter Option: ")
                realOption = option.lower()
                print("\n", end="")
                #determining the option selected
                while(realOption != 'g' and realOption != 't' and realOption != '1' and realOption != 'q'):
                    option = input("Invalid option. Please re-enter: ")
                    realOption = option.lower()
                if realOption == 'g':
                    correctGuess = self.guessWord(game)
                    notDone = correctGuess
                elif realOption == 't':
                    game.success = False
                    notDone = False
                    self.negativeScore(game)
                    print("@@\n@@ FEEDBACK: You really should have guessed this...'" + word + "'\n@@\n\n")
                    input("Press any key to continue... ")
                elif realOption == '1':
                    allLettersFound = 0
                    for x in game.letterFound:
                        if x == True:
                            allLettersFound += 1
                    if allLettersFound == 4:
                        input("All letters have been found. Please select another option. Press any key to continue... ")
                        continue
                    else:    
                        self.letterRequest(game)
                elif realOption == 'q':
                    notDone = False
                    nextGame = False
        
        #Final report
        listOfGames.pop()
        os.system('clear')
        finalScore = 0.00
        print("++\n++ Game Report\n++\n")
        print("%-15s %-15s %-15s %-15s %-15s %s" %("Game", "Word", "Status", "Bad Guesses", "Missed Letters", "Score"))
        print("%-15s %-15s %-15s %-15s %-15s %s" %("----", "----", "------", "-----------", "--------------", "-----"))
        for index, selectedGame in enumerate(listOfGames):
            gameNumber = str(index + 1)
            gameWord = selectedGame.word
            if selectedGame.success == True:
                gameStatus = "Success"
            else:
                gameStatus = "Gave up"
            gameBadGuesses = str(selectedGame.badGuesses)
            gameMissedLetters = str(selectedGame.missedLetters)
            gameScore = "{:0.2f}".format(selectedGame.score)
            finalScore += selectedGame.score

            print("%-15s %-15s %-15s %-15s %-15s %s" %(gameNumber, gameWord, gameStatus, gameBadGuesses, gameMissedLetters, gameScore))
        print("Final Score: {:0.2f}".format(finalScore))

    boo = start

    #When guessing a letter
    def letterRequest(self, game):
        nbOfLettersFound = 0
        inputLetter = input("Enter a letter: ")
        letter = inputLetter.lower()
        while len(letter) != 1 or not letter.isalpha() or letter in game.lettersRequested:
            inputLetter = input("\nInvalid option. Please re-enter: ")
            letter = inputLetter.lower()
        game.lettersRequested.append(letter)
        for index, x in enumerate(game.word):
            if letter == x:
                game.currentGuess[index] = x
                game.letterFound[index] = True
                nbOfLettersFound += 1
        if nbOfLettersFound != 0:
            print("\n@@\n@@ FEEDBACK: Woo hoo, you found " + str(nbOfLettersFound) + " letters\n@@\n\n")
        else:
            print("\n@@\n@@ FEEDBACK: No match found for the letter\n@@\n\n")
            game.missedLetters += 1
        input("Press any key to continue... ")
    
    #when guessing the word
    def guessWord(self, game):
        inputWordCheck = input("Make your guess: ")
        wordCheck = inputWordCheck.lower()
        while len(wordCheck) != 4 or not wordCheck.isalpha():
            inputWordCheck = input("\nInvalid option. Please re-enter: ")
            wordCheck = inputWordCheck.lower()
        if wordCheck == game.word:
            self.positiveScore(game)
            print("\n@@\n@@ FEEDBACK: You're right, Einstein!\n@@\n\n")
            input("Press any key to continue... ")
            return False
        elif wordCheck != game.word:
            print("\n@@\n@@ FEEDBACK: Wrong guess. Try again.\n@@\n\n")
            game.badGuesses += 1
            input("Press any key to continue... ")
            return True
    
    #scoring is negative
    def negativeScore(self, game):
        for index, letter in enumerate(game.currentGuess):
            if letter == '-':
                associatedLetter = game.word[index]
                game.score -= Guess.frequencies[associatedLetter]
                game.score = round(game.score, 2)
    
    #scoring is positive
    def positiveScore(self, game):
        for index, letter in enumerate(game.currentGuess):
            if letter == '-':
                associatedLetter = game.word[index]
                game.score += Guess.frequencies[associatedLetter]
        if game.missedLetters != 0:
            game.score = game.score / game.missedLetters
        game.score = game.score * (1 - game.badGuesses/10)
        game.score = round(game.score, 2)
        if game.score < 0:
            game.score = 0.00
            

        


                    

        
        


            