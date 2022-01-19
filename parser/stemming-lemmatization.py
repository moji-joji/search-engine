from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.stem import PorterStemmer
import nltk

nltk.download('punkt')

porter=PorterStemmer()

def stemSentence(sentence):
    token_words = word_tokenize(sentence)
    stem_sentence=[]
    for word in token_words:
        stem_sentence.append(porter.stem(word))
        stem_sentence.append(" ")
    return "".join(stem_sentence)

x=stemSentence(input("Enter a sentence: "))
print(x)
