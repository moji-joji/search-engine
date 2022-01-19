import re
import os
import sys

dirname = os.path.abspath(os.path.dirname(__file__))
in_filename = sys.argv[1]
out_filename = sys.argv[2]


with open(in_filename, 'r') as f:
    text = f.read()
    text_cleaned = re.split(r'\W|\d', text)

    with open(out_filename, 'w') as f_out:
        f_out.write(' '.join(text_cleaned))
