import xml.etree.ElementTree as ET
from typing import List, Dict, Tuple
import xml.etree.ElementTree as etree
import codecs
from datetime import datetime
import csv
import time
import os

CSV_TO_WRITE = '../data/fuck.csv'
XML_SOURCE = "../data/enwiki-20211220-pages-articles-multistream1.xml"
ARTICLES_TO_WRITE_DIR = "../data/articles"

tag_garbage = "{http://www.mediawiki.org/xml/export-0.10/}"
glen = len(tag_garbage)
i = 0
pages = 0

header = ["id", "title", "path_to_file", "updated_at", "another_title"]


row_dict = {
    "id": "",
    "title": "",
    "path_to_file": "",
    "updated_at": "",
    "anotherTitle": "",
    "text": ""
}

got_text = False

with open(CSV_TO_WRITE, 'w') as f:
    writer = csv.writer(f)
    writer.writerow(header)
    # row = ["1"]
    curr_article = 0
    for event, elem in etree.iterparse(XML_SOURCE, events=('start', 'end')):
        if event == 'start' and elem.tag[glen:] == "page":
            curr_article += 1
            row_dict["id"] = curr_article
        if event == 'start' and elem.tag[glen:] == "redirect":
            row_dict["title"] = elem.attrib['title']

        if event == 'start' and elem.tag[glen:] == "title":
            row_dict["anotherTitle"] = elem.text

        if elem.tag[glen:] == "text":
            path_to_file = f"{ARTICLES_TO_WRITE_DIR}/{row_dict['id']}.txt"
            # print(elem.attrib['bytes'])
            # write the text elem's text to a txt file
            row_dict["path_to_file"] = path_to_file
            text = elem.text
            if not got_text and text is not None:
                row_dict["text"] = text
                got_text = True
                # print(text)

        if event == 'start' and elem.tag[glen:] == "timestamp":
            date = ""
            if elem.text:
                date = elem.text
            else:
                date = datetime.now().isoformat()
            row_dict["updated_at"] = date
        if event == 'end' and elem.tag[glen:] == "page":
            if (len(row_dict["title"]) == 0):
                row_dict["title"] = row_dict["anotherTitle"]

            with open(row_dict["path_to_file"], 'w') as f:
                if not got_text:
                    f.write("")
                    print(
                        f"no text for {row_dict['id']} {row_dict['anotherTitle']}")
                else:
                    f.write(row_dict["text"])

            writer.writerow(list(row_dict.values())[:-2])
            row_dict["title"] = ""
            row_dict["anotherTitle"] = ""
            row_dict["path_to_file"] = ""
            row_dict["updated_at"] = ""
            row_dict["id"] = ""
            row_dict["text"] = ""
            got_text = False

        elem.clear()

print(pages)
