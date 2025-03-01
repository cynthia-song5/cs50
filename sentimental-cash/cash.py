# TODO
from cs50 import get_float

try:
    amount = get_float("Change owed: ")
except ValueError:
    amount = get_float("Change owed: ")
if amount < 0:
    amount = get_float("Change owed: ")


# determining change
count = 0
# quarters
while round(amount, 2) >= 0.250:
    count += 1
    amount -= 0.25

# dimes
while round(amount, 2) >= 0.100:
    count += 1
    amount -= 0.10

# nickels
while round(amount, 2) >= 0.050:
    count += 1
    amount -= 0.05

# pennies
while round(amount, 2) >= 0.010:
    count += 1
    amount -= 0.01


print(f"{count}")