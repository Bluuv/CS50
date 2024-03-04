# TODO
from cs50 import get_int


def main():

    h = get_int("Height: ")

    if h < 1 or h > 8:
        print("Please type a valid input")
        exit()

    for i in range(h):
        print(" " * (h-i), end='')
        print("#" * (i+1), end='\n')


if __name__=="__main__":
    main()