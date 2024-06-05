import sys
from Guess import Guess

if __name__ == "__main__":
    if len(sys.argv) == 2:
        cmdArg = sys.argv[1].lower()
        if cmdArg == "play" or cmdArg == "test":
            wow = [1,2,];
            print(len(wow));
            holy = [1,wow];
            hello = "joe", "markham",;
            print(len(hello))
            ret = "lel"
            a,b,c = ret
            print(a)
            holy[1][0] = 15
            print(wow)
            gameStart = Guess()
            gameStart.start(cmdArg)
        else:
            print("Incorrect input values. The game will not start. Please input correct values: \"play\" or \"test\".")
            exit()
    else:
        print("Incorrect input values. The game will not start. Please input correct values: \"play\" or \"test\".")
        exit()