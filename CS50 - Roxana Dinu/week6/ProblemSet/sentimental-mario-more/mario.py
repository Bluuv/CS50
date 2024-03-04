# TODO
from cs50 import get_int

def main():

    h = get_int("Height: ")

    if h < 1 or h > 8:
        print("Please type a valid input")
        exit()

    for i in range(h):
        s1 = "".join([" "]*(h-i))
        s2 = "".join("#"*(i+1))
        s3 = "  "
        print(s1+s2+s3+s2, end='\n')

if __name__=="__main__":
    main()