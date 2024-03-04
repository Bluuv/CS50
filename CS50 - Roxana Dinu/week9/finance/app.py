import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime, time


# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # return apology("TODO")
    user=db.execute("SELECT * FROM users WHERE id=?", session["user_id"])[0]
    # ownedStocks=db.execute("SELECT symbol, number_of_shares FROM shares_bought WHERE username=?", user["username"])
    ownedStocks=db.execute("SELECT symbol, number_of_shares FROM shares_bought WHERE username=?", user["username"])
    # sharesBought=db.execute("SELECT symbol, SUM(number_of_shares) FROM shares_bought WHERE username=? GROUP BY symbol HAVING transaction_type=Bought", user["username"])
    # sharesSold=db.execute("SELECT symbol, SUM(number_of_shares) FROM shares_sold WHERE username=? GROUP BY symbol HAVING transaction_type=Sold", user["username"])
    sum=0
    for element in ownedStocks:
        currentStockPrice=lookup(element['symbol'])
        sharesBought=db.execute("SELECT symbol, SUM(number_of_shares) AS nr_shares FROM shares_bought WHERE username=? and symbol=? GROUP BY symbol HAVING transaction_type='Bought'",
                                 user["username"], element['symbol'])[0]['nr_shares']
        sharesSold=db.execute("SELECT symbol, SUM(number_of_shares) AS nr_shares FROM shares_sold WHERE username=? and symbol=? GROUP BY symbol HAVING transaction_type='Sold'",
                            user["username"], element['symbol'])

        if not sharesSold:
            sharesSold = [{'nr_shares':0}]
        element['number_of_shares']=sharesBought-sharesSold[0]['nr_shares']
        element['currentPrice']=currentStockPrice['price']
        element['totalValue']=currentStockPrice['price']*element['number_of_shares']
        sum=sum+element['totalValue']
    cashBalance=db.execute("SELECT cash FROM users WHERE username=?", user["username"])
    totalBalance=sum+cashBalance[0]['cash']
    return render_template("index.html", results=ownedStocks, cashBalance=cashBalance[0]['cash'], totalBalance=totalBalance )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # return apology("TODO")
    if request.method== "GET":
        return render_template("buy.html")
    else:
        stockPrice=lookup(request.form.get("symbol"))["price"]
        stockNumber=int(request.form.get("nrshares"))
        stockSymbol=request.form.get("symbol")
        user=db.execute("SELECT * FROM users WHERE id=?", session["user_id"])[0]
        userCash=user["cash"]
        totalStockPrice = stockPrice * stockNumber
        cashRemaining=userCash-totalStockPrice
        currentTime= datetime.now()
        # current_time=now.strftime("%H:%M:%S")
        # currentTime=time.ctime()

        if (userCash < totalStockPrice ):
            return apology("Bitch you're poor", 403)
        else:
            db.execute("INSERT INTO shares_bought (username, symbol, price, number_of_shares, time) VALUES (?, ?, ?, ?, ?)",user["username"], stockSymbol , totalStockPrice, stockNumber, currentTime )
            db.execute("UPDATE users SET cash=?", cashRemaining)
        return redirect ("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # return apology("TODO")
    user=db.execute("SELECT * FROM users WHERE id=?", session["user_id"])[0]
    history=db.execute("SELECT username, symbol, price, number_of_shares, time, transaction_type FROM shares_bought WHERE username=? UNION ALL SELECT username, symbol, price, number_of_shares, time, transaction_type FROM shares_sold WHERE username=? ORDER BY time DESC",user["username"],user["username"])
    return render_template("history.html", results=history)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # return apology("TODO")
    if request.method== "GET":
        return render_template("quote.html")
    else:
        result=lookup(request.form.get("symbol"))
        return render_template("quoted.html", frontendResponse=result)




@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()

    if request.method== "POST":
        username = request.form.get("username")
        user = db.execute("SELECT * FROM users WHERE username=?", username)
        if not username or len(user)!=0:
            return apology("User name already in use or is empty!", 403)

        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not password or password!=confirmation:
            return apology("Please provide a password and make it sure it matches its confirmation! also fuck ur mom pwp", 403)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
        return redirect ("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # return apology("TODO")
    if request.method== "GET":
        return render_template("sell.html")
    else:
        stockPrice=lookup(request.form.get("symbol"))["price"]
        stockNumber=int(request.form.get("nrshares"))
        stockSymbol=request.form.get("symbol")
        user=db.execute("SELECT * FROM users WHERE id=?", session["user_id"])[0]
        userbought=db.execute("SELECT * FROM shares_bought WHERE username=?", user['username'])
        print(userbought)
        stockNumberHad=0
        for element in userbought:
            if element['symbol']==stockSymbol:
                stockNumberHad=element['number_of_shares']
        userCash=user["cash"]
        totalStockPrice = stockPrice * stockNumber
        cashRemaining=userCash+totalStockPrice
        currentTime= datetime.now()
        # current_time=now.strftime("%H:%M:%S")
        # currentTime=time.ctime()

        if (stockNumber > stockNumberHad ):
            return apology("Bitch you don't have enough", 403)
        else:
            db.execute("INSERT INTO shares_sold (username, symbol, price, number_of_shares, time) VALUES (?, ?, ?, ?, ?)",user["username"], stockSymbol , totalStockPrice, stockNumber, currentTime )
            db.execute("UPDATE users SET cash=?", cashRemaining)
        return redirect ("/")
