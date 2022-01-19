import sys
import os
import re
import csv

dirname = os.path.abspath(os.path.dirname(__file__))
in_filename = "/mnt/d/OneDrive/OneDrive - National University of Sciences & Technology/NUST/3 Semester/DSA/Project/search-engine/data/metadata.csv"
in_dir = "/mnt/d/OneDrive/OneDrive - National University of Sciences & Technology/NUST/3 Semester/DSA/Project/search-engine/data/articles-randi"
out_dir = "/mnt/d/OneDrive/OneDrive - National University of Sciences & Technology/NUST/3 Semester/DSA/Project/search-engine/data/articles"

filenames_to_process = set()


def main():
    with open(in_filename, 'r') as f:
        csvreader = csv.reader(f)
        next(csvreader)

        for id, _, __, ___ in csvreader:
            filenames_to_process.add(id+'.txt')

    files_in_dir = set(os.listdir(in_dir))
    files_to_process = files_in_dir.intersection(filenames_to_process)

    # print(files_in_dir)
    # print(filenames_to_process)
    clean_files(files_to_process, in_dir, out_dir)


def clean_files(files, in_dir, out_dir):
    for file in files:
        # print('Processing file: ' + file)
        if file.endswith(".txt"):
            with open(os.path.join(in_dir, file), "r") as f:
                text = f.read()
                text = clean_text(text)

                with open(os.path.join(out_dir, file), "w") as f_out:
                    f_out.write(text)
        # input("Press Enter to continue...")


def clean_text(text):
    words = re.split(r'\W|\d', text)
    return ' '.join([word.lower().strip() for word in words if word.strip()])


if __name__ == '__main__':
    main()
    print("Done")
