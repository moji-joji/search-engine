import os

FILE_PATH = "/mnt/d/OneDrive/OneDrive - National University of Sciences & Technology/NUST/3 Semester/DSA/Project/search-engine/data/indexing/inverted-index-cleaned.csv"
OUTPUT_DIR = "/mnt/d/OneDrive/OneDrive - National University of Sciences & Technology/NUST/3 Semester/DSA/Project/search-engine/data/barrels"

curr_line = 0
curr_wordId = None
file = None

# i = 0

with open(FILE_PATH, "r") as f:
    # iterate over each line
    for line in f:
        if curr_line == 0:
            curr_line += 1
            continue

        wordId = line.split(",")[0]

        if (wordId != curr_wordId):
            if file is not None:
                # print("Closing a file...")
                file.close()

            curr_wordId = wordId
            file = open(os.path.join(OUTPUT_DIR, curr_wordId + ".csv"), "w")
            file.write("wordId, fileId, frequency, positions\n")
            file.write(line)

        else:
            file.write(line)

        # i += 1
        # if i == 40000:
        #     break
        curr_line += 1

        if curr_line % 1000000 == 0:
            print("Total printed lines right now are ", curr_line)
            print("Total printed word right nwo are ", curr_wordId)
