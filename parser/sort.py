
import sys
import csv
from datetime import datetime

filename = "/mnt/d/OneDrive/OneDrive - National University of Sciences & Technology/NUST/3 Semester/DSA/Project/search-engine/data/indexing/inverted-index-remake-complete-pakka-wala.csv"
out_filename = "/mnt/d/OneDrive/OneDrive - National University of Sciences & Technology/NUST/3 Semester/DSA/Project/search-engine/data/indexing/inverted-index-cleaned.csv"


def main():
    rows = []
    initial = datetime.now()
    now = datetime.now()
    print(datetime.now(), "Reading file...")
    with open(filename, 'r') as f:
        csvreader = csv.reader(f)
        headers = next(csvreader)

        for row in csvreader:
            wordId, fileId, frequency, positions = row
            positions = ",".join([pos for pos in positions.split(',') if pos])
            row = [int(wordId), fileId, int(frequency), positions]
            rows.append(row)

        # lines = f.readlines()
        # headers = [word.strip() for word in lines[0].split(',')]

        # for line in lines[1:]:
        #     metadata, positions = line.split('[')
        #     positions = positions.split(']')[0]
        #     positions = positions.split(',')

        #     positions = [pos.strip() for pos in positions if pos.strip()]
        #     wordId, fileId, frequency = [x.strip()
        #                                  for x in metadata.split(',') if x.strip()]

        #     rows.append([wordId, fileId, frequency, ",".join(positions)])

    difference = datetime.now() - now
    now = datetime.now()
    print(datetime.now(), "Sorting array...", difference)
    # rows.sort(key=lambda x: x[0])
    rows.sort(key=lambda x: (x[0], -x[2]))

    difference = datetime.now() - now
    print(datetime.now(), "Writing file...", difference)
    with open(out_filename, 'w') as f:
        csvwriter = csv.writer(f)
        csvwriter.writerow(headers)
        csvwriter.writerows(rows)

    print("Done", "took", datetime.now() - initial)


if __name__ == "__main__":
    main()
