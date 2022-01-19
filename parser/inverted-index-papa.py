import csv

import os


filename = "/mnt/d/OneDrive/OneDrive - National University of Sciences & Technology/NUST/3 Semester/DSA/Project/search-engine/data/indexing/inverted-index-remake-complete.csv"
outdir = "/mnt/d/OneDrive/OneDrive - National University of Sciences & Technology/NUST/3 Semester/DSA/Project/search-engine/data/inverted-indices"


def main():

    os.path.isdir(outdir) or os.mkdir(outdir)

    with open(filename, 'r') as f:
        csvreader = csv.reader(f)
        headers = next(csvreader)

        counter = 0

        for wordId, fileId, frequency, positions in csvreader:
            file_to_write = os.path.join(outdir, wordId) + ".csv"

            if os.path.isfile(file_to_write):
                with open(file_to_write, 'a') as f:
                    csvwriter = csv.writer(f)
                    csvwriter.writerow([wordId, fileId, frequency, positions])
            else:
                with open(file_to_write, 'w') as f:
                    csvwriter = csv.writer(f)
                    csvwriter.writerows(
                        [headers, [wordId, fileId, frequency, positions]])

            # counter += 1
            # if counter == 20000:
            #     break

    print("Done!")


if __name__ == '__main__':
    main()
