# TODO
from cs50 import get_string

# prompts user for text input
text = get_string("Text: ")

# count our values
letters = 0
words = 1
sentences = 0
for i in text:
    if i == ' ':
        words += 1
    elif (i.lower() >= 'a' and i.lower() <= 'z'):
        letters += 1
    elif (i == '!' or i == '.' or i == '?'):
        sentences += 1

# determine the Coleman-Liau index
avgw = words/100
L = letters / avgw
print(L)
S = sentences / avgw
print(S)

index = round(0.0588 * L - 0.296 * S - 15.8)

# printing the corresponding grade level
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
