import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name=request.form.get("name")
        month=request.form.get("month")
        day=request.form.get("day")

        sql= "INSERT INTO birthdays (name, month, day) VALUES ('{}', {}, {})".format(name, month, day)
        print(sql)
        db.execute(sql)
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        results=[{}]
        sql="SELECT id, name, month, day FROM birthdays"
        results=db.execute(sql)

        for res in results:
            print(res)
        return render_template("index.html", results=results)

@app.route("/delete", methods=["POST"])
def delete():
    
    id=request.form.get("id")

    sql="DELETE FROM birthdays WHERE id={}".format(id)
    db.execute(sql)

    return redirect("/")
