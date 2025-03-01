import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("check your command-line usage!")
        sys.exit()

    dna_path = sys.argv[1]
    seq_path = sys.argv[2]
    # TODO: Read database file into a variable
    with open(dna_path, "r") as file:
        reader = csv.DictReader(file)
        # instead of using 'for row in reader:', there's a built in list converter!
        dna = list(reader)

    # TODO: Read DNA sequence file into a variable
    with open(seq_path, "r") as file:
        # for txt files
        DNA_reader = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    longestNum = 0
    longestName = "No match"

    # STR collection
    STRs = []
    max = []
    for j in range(1, len(reader.fieldnames)):
        # print(f"dna: {dna[i]}")
        # i think right now, it is simply giving the same values for every person
        STR = reader.fieldnames[j]
        STRs.append(STR)
        max.append(0)

    # print(STRs)
    k = 0
    # loops through all people
    for i in range(len(dna)):
        # loops through all STRs possible
        # print(f"str: {STR}")
        # print(f"dna reader: {DNA_reader}")
        for k in range(len(STRs)):
            current = longest_match(DNA_reader, STRs[k])
        # print(current)
            if (current > max[k]):
                max[k] = current
            # print(f"longest name: {longestName}")

    for i in range(len(dna)):
        matches = 0
        for j in range(1, len(reader.fieldnames)):
            if int(max[j - 1]) == int(dna[i][reader.fieldnames[j]]):
                matches += 1
            if matches == (len(reader.fieldnames) - 1):
                print(dna[i]['name'])
                exit(0)
    print("No match")

    # print(longestName)
    # return longestName


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
