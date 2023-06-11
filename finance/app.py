import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, time, val_pass

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

    person_id = session["user_id"]

    portfolio = db.execute("SELECT * FROM shares WHERE person_id = ?", person_id)
    prices = {}
    totals = {}
    cash = float(db.execute("SELECT cash FROM users WHERE id = ?", person_id)[0]["cash"])
    totalCash = cash

    for p in portfolio:
        prices[p["id"]] = float(lookup(p["symbol"])["price"])
        totals[p["id"]] = prices[p["id"]]*p["shares"]
        totalCash += totals[p["id"]]
        prices[p["id"]] = usd(prices[p["id"]])
        totals[p["id"]] = usd(totals[p["id"]])

    return render_template("index.html", portfolio=portfolio, prices=prices, totals=totals, cash=usd(cash), totalCash=usd(totalCash))

    # return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        # Check to see if form is correctly submitted
        if not request.form.get("symbol"):
            return apology("Must provide a symbol")
        elif not request.form.get("shares"):
            return apology("Must provide a number of shares")

        stock = lookup(request.form.get("symbol"))
        if stock is None:
            return apology("Symbol does not exist")

        # Define all variables for later use
        person_id = session["user_id"]
        transaction_type = "BUY"
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        price = float(lookup(symbol)["price"])
        name = lookup(symbol)["name"]
        timestamp = time()

        # Check share is numeric data type
        try:
            shares = int(shares)
        except ValueError:
            return apology("INVALID SHARES")

        # Check shares is positive number
        if not (shares > 0):
            return apology("INVALID SHARES")

        total = price*shares

        user = db.execute("SELECT * FROM users WHERE id = ?", person_id)[0]

        # Check to see if user has enough cash
        if total > user["cash"]:
            return apology("Not enough cash to buy shares")

        # Check to see if symbol already exists for user in the shares table and respond accordingly
        symbols = db.execute("SELECT symbol FROM shares WHERE person_id = ?", person_id)
        if symbol not in symbols:
            db.execute("INSERT INTO shares (person_id, symbol, name, shares) VALUES(?, ?, ?, ?)", person_id, symbol, name, shares)
        else:
            current = db.execute("SELECT * FROM shares WHERE person_id = ? AND symbol = ?", person_id, symbol)[0]
            db.execute("UPDATE shares SET shares = ? WHERE person_id = ?", current["shares"] + shares, person_id)

        total = shares*price

        # Update users cash and insert a new transaction for history tab
        db.execute("UPDATE users SET cash = ? WHERE id = ?", (user["cash"]-total), person_id)
        db.execute("INSERT INTO transactions (person_id, transaction_type, symbol, shares, price, timestamp, total) VALUES(?, ?, ?, ?, ?, ?, ?)",
                   person_id, transaction_type, symbol, shares, usd(price), timestamp, usd(total))

        return redirect("/")
    else:
        return render_template("buy.html")

    # return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute("SELECT transaction_type, symbol, shares, price, total, timestamp FROM transactions")

    return render_template("history.html", transactions=transactions)

    # return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password",)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password")

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

    if request.method == "POST":
        symbol = lookup(request.form.get("symbol"))
        if not symbol:
            return apology("Invalid symbol")
        symbol["price"] = usd(symbol["price"])
        return render_template("quoted.html", symbol=symbol)
    else:
        return render_template("quote.html")

    # return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        p = request.form.get("password")
        c = request.form.get("confirmation")

        username = request.form.get("username")

        # Check to see if submission is valid
        if not username:
            return apology("must provide username")
        elif not p or not c:
            return apology("must provide password")
        elif p != c:
            return apology("password and confirmation must be the same")
        elif val_pass(p):
            return apology("Password must contain two digits and three letters")
        elif username == "" or len(db.execute('SELECT username FROM users WHERE username = ?', username)) > 0:
            return apology("Invalid Username: Blank, or already exists")

        # Hash password and export user information into users table
        username = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
        return redirect("/login")
    else:
        return render_template("register.html")
    # return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    person_id = session["user_id"]

    if request.method == "POST":

        symbol = request.form.get("symbol")
        numOfShares = int(request.form.get("shares"))

        shares = int(db.execute("SELECT shares FROM shares WHERE person_id = ? AND symbol = ?", person_id, symbol)[0]["shares"])

        # Check to see if sufficient shares are available
        if numOfShares > shares:
            return apology("Number of shares selected is more than currently in inventory")

        share = db.execute("SELECT * FROM shares WHERE person_id = ? AND symbol = ?", person_id, symbol)[0]

        # Check to see if num of shares is equal to zero and act accordingly
        s = share["shares"] - numOfShares
        if s == 0:
            db.execute("DELETE FROM shares WHERE person_id = ? AND symbol = ?", person_id, symbol)
        else:
            db.execute("UPDATE shares SET shares = ? WHERE person_id = ? AND symbol = ?", s, person_id, symbol)

        user = db.execute("SELECT * FROM users WHERE id = ?", person_id)[0]

        price = float(lookup(symbol)["price"])
        total = price * numOfShares

        # Update users cash and add transaction to transactions table
        db.execute("UPDATE users SET cash = ? WHERE id = ?", (user["cash"] + total), person_id)
        db.execute("INSERT INTO transactions (person_id, transaction_type, symbol, shares, price, timestamp, total) VALUES(?, ?, ?, ?, ?, ?, ?)",
                   person_id, "SELL", symbol, -numOfShares, usd(price), time(), usd(total))

        return redirect("/")
    else:

        symbols = db.execute("SELECT symbol FROM shares WHERE person_id = ?", person_id)

        return render_template("sell.html", symbols=symbols)

    # return apology("TODO")