# TODO
from cs50 import get_int

# gets user input
try:
    h = int(get_int("Height: "))
except ValueError:
    h = int(get_int("Height: "))
if h > 8 or h < 1:
    h = int(get_int("Height: "))

# creates pyramid
for i in range(h):
    for j in range(h-(i+1)):
        print(" ", end="")
    print("#" * (i+1))