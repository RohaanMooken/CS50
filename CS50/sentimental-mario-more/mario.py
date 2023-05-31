# Promot user for integer input
while True:
    try:
        n = int(input("Height: "))
    # If input is not an integer print error message
    except ValueError:
        print("Height must be an integer between 1 to 8")
    # If integer is between 1 and 8 exit loop
    else:
        if n < 9 and n > 0:
            break

# Print n number of columns
for i in range(n):
    # Print spaces for left side of pyramid
    for j in range(n - 1, i, -1):
        print(" ", end="")
    # Print left side of pyramid
    for k in range(i + 1):
        print("#", end="")
    # Add double space between the two sides
    print("  ", end="")
    # Print right side of pyramid
    for l in range(i + 1):
        print("#", end="")
    print()