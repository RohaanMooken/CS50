def main():
    text = input("Text: ")

    letters = 0
    words = 0
    sentences = 0

    # Add one to the corresponding variable
    for char in text:
        # Letter
        if char.isalpha():
            letters += 1
        # Words
        elif char.isspace():
            words += 1
        # Sentences
        elif char == "." or char == "!" or char == "?":
            sentences += 1
    words += 1

    # Calculate grade
    l = letters/words*100
    s = sentences/words*100
    subindex = 0.0588 * l - 0.29 * s - 15.8
    index = round(subindex)

    # Print grade
    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()