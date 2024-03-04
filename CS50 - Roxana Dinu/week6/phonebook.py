# from cs50 import get_string

# people = {
#     "Rox": "+1234",
#     "Link": "+5678"
# }

# name = get_string("Name: ")
# if name in people:
#     print(f"Number: {people[name]}")

import csv
from cs50 import get_string

name = get_string("Name: ")
number = get_string("Number: ")

#file = open("phonebook.csv", "a")
with open("phonebook.csv", "a") as file:

    writer = csv.writer(file)
    writer.writerow([name, number])

#file.close()