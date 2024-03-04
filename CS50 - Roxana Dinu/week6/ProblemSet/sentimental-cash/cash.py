# TODO
from cs50 import get_float

def main ():

    while True:
        change = get_float("Change owed: ")
        if change < 0 :
            print("Provide a valid numeric positive value")
        # elif isinstance(change, float) == False:
        #     print("Provide a valid numeric positive value")
        else:
            break

    counter=0
    a = calculate_quarters(change)
    change=change-0.25*a
    counter+=a

    a = calculate_dimes(change)
    change=change-0.1*a
    counter+=a

    a = calculate_nickels(change)
    change=change-0.05*a
    counter+=a

    a = calculate_pennies(change)
    change=change-0.01*a
    counter+=a

    print(counter)

def calculate_quarters(x):
    result = x//0.25
    return int(result)

def calculate_dimes(x):
    result = x//0.10
    return int(result)

def calculate_nickels(x):
    result = x//0.05
    return int(result)

def calculate_pennies(x):
    result = x//0.01
    return int(result)


if __name__=="__main__":
    main()