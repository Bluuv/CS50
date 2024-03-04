import sys

number = [3, 6, 8, 2, 7, 5, 0]

if 0 in number:
    print("Found")
    sys.exit(0)

print("Not found")
sys.exit(1)