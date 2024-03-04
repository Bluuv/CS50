# TODO

def main():

    while True:
        number=input("Number: ")
        number=number.replace('-', '')
        if number.isnumeric()==True:
            break

    length=len(number)
    twosum=0
    sum=0
    finalSum=0

    try:
        for i in range(length-2, -1, -2):
            twosum = twosum + (int(number[i])*2)%10+(int(number[i])*2)//10
    except:
        print("Error occured")

    try:
        for i in range(length-1, -1, -2):
            sum = sum + int(number[i])
    except:
        print("Error occured")

    finalSum = twosum+sum

    if finalSum % 10==0 and isMasterCard(number)==True:
        print("MasterCard")
    elif finalSum % 10==0 and isAmex(number)==True:
        print("Amex")
    elif finalSum % 10==0 and isVisa(number)==True:
        print("Visa")
    else:
        print("Invalid")


def isMasterCard (stri):
    if len(stri)==16 and stri[0]=="5" and stri[1] in "12345":
        return True
    else:
        return False

def isAmex (stri):
    if len(stri)==15 and stri[0]=="3" and stri[1] in "47":
        return True
    else:
        return False

def isVisa (stri):
    if len(stri)==13 and stri[0]=="4" or len(stri)==16 and stri[0]=="4":
        return True
    else:
        return False

if __name__=="__main__":
    main()