import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
# app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

db.execute("CREATE TABLE IF NOT EXISTS orders (id INTEGER, user_id NUMERIC NOT NULL, name TEXT NOT NULL, symbol TEXT NOT NULL, shares NUMERIC NOT NULL, price NUMERIC NOT NULL, total NUMERIC NOT NULL, PRIMARY KEY(id), FOREIGN KEY(user_id) REFERENCES users(id))")
db.execute("CREATE INDEX IF NOT EXISTS orders_by_user_id_index ON orders (user_id)")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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
    if request.method == "GET":
        return render_template("index.html")
    symbol = db.execute("SELECT symbol FROM orders")
    return render_template("index.html", symbol=symbol)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    symbol = request.form.get("symbol")
    shares = int(request.form.get("shares"))
    # check for invalids
    if not symbol or lookup(symbol) == None:
        return apology("invalid symbol")
    if shares <= 0:
        return apology("invalid number; enter a positive integer")
    user_id = session["user_id"]
    balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
    print(balance)
    cost = shares * lookup(symbol)["price"]
    if cost > balance:
        return apology("lol you're too poor.")

    db.execute("UPDATE users SET cash = ? WHERE id = ?", balance-cost, user_id)
    # create new table
    db.execute("INSERT INTO orders (user_id, name, symbol, shares, price, total) VALUES (?, ?, ?, ?, ?, ?)",
    user_id, lookup(symbol)["name"], symbol, shares, lookup(symbol)["price"], cost)
    name = lookup(symbol)["name"]
    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    if request.method == "GET":
        return render_template("history.html")
    orders = db.execute("SELECT * FROM orders")
    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    total = cash + db.execute("SELECT total FROM orders WHERE user_id = ?", user_id)
    return render_template("history.html", orders=orders, balance=cash, total=total)


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
    if request.method == "GET":
        return render_template("quote.html")
    symbol = request.form.get("symbol")
    # validS = db.execute ("SELECT * FROM users")
    if lookup(symbol) == None:
        return apology("invalid symbol")
    # if successful, display current price
    return render_template("quoted.html", name=lookup(symbol)["name"], price=usd(lookup(symbol)["price"]), symbol=lookup(symbol)["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    if request.method == "POST":
        name = request.form.get("username")
        pw = request.form.get("password")
        con = request.form.get("confirmation")
        registrants = db.execute("SELECT * FROM users")
        # checks for invalid registrations
        if not name:
            return apology("invalid username")
        if not pw or not con or pw != con:
            return apology("invalid password")
        if name in registrants:
            return apology("invalid username")
        # insert a valid registration into database
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", name, generate_password_hash(pw))
        # login user
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        # Redirect user to home page
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        # check for invalids
        portfolio = db.execute(
            "SELECT symbol, SUM(shares) AS shares FROM purchases WHERE users_id = ? GROUP BY symbol", session["user_id"])
        for stock in portfolio:
            folio_symbol = stock["symbol"]
            shares_owned = int(stock["shares"])
        return render_template("sell.html")
    symbol = request.form.get("symbol")
    shares = int(request.form.get("shares"))
    # check for invalids
    portfolio = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM purchases WHERE users_id = ? GROUP BY symbol", session["user_id"])
    for stock in portfolio:
        folio_symbol = stock["symbol"]
        shares_owned = int(stock["shares"])
        # check invalids
        if not symbol:
            return apology("select stock to sell")
        if symbol != folio_symbol:
            return apology("invalid symbol; you can only sell stocks you own")
        if shares < 1:
            return apology("invalid number of shares to sell")
        if shares_owned < shares:
            return apology("you don't have enough shares to sell")

        # update
        db.execute("UPDATE purchases SET shares = ? WHERE users_id = ?", shares_owned-shares, session["user_id"])
        users = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        cash = users[0]["cash"]
        stock_info = lookup(symbol)
        sell_amt = shares*stock_info["price"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash+sell_amt, session["user_id"])

        flash("Sold!")
        return redirect("/", portfolio=portfolio, stock=stock)
