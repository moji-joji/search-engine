import csv
import os


dirname = os.path.abspath(os.path.dirname(__file__))
in_filename = os.path.join(dirname, '..', 'data', 'metadata.csv')
out_filename = os.path.join(dirname, '..', 'data', 'metadata-cleaned.csv')

base_path_of_article = dirname

headers = []


def main():
    global headers

    articles = {}
    with open(in_filename, 'r') as f:
        csvreader = csv.reader(f)
        headers = next(csvreader)

        for id, title, path_to_file, updated_at in csvreader:
            if check_file_contains_REDIRECT(path_to_file):
                continue

            articles[title] = {
                'id': id,
                'title': title,
                'path_to_file': path_to_file,
                'updated_at': updated_at
            }

    with open(out_filename, 'w') as f:
        csvwriter = csv.writer(f)
        csvwriter.writerow(headers)

        for key in articles.keys():
            csvwriter.writerow([articles[key]['id'], articles[key]['title'],
                               articles[key]['path_to_file'], articles[key]['updated_at']])

    print("Done")


def check_file_contains_REDIRECT(filename):
    with open(os.path.join(base_path_of_article, filename), 'r') as f:
        line = f.readline()
        if line.startswith('#REDIRECT'):
            return True
    return False


if __name__ == '__main__':
    main()
