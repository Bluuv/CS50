import csv
# import re

counter=0
title = input("Title: ").strip().upper()

with open("favorites.csv", "r") as file:

    reader=csv.DictReader(file)
    for row in reader:
        if row["title"].strip().upper()==title:
            counter+=1

        # if re.search("^(OFFICE|THE.OFFICE)$", title):
        #     counter+=1
print(counter)
