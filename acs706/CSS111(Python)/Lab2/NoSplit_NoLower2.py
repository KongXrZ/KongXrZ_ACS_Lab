#sentence = input()
sentence = "It's suggested to walk, study, and sleep everyday; for a great health"

new_sentence = ""
for ch in sentence:
    if 'A' <= ch <= 'Z':
        new_sentence += chr(ord(ch) + 32)
    else:
        new_sentence += ch

word_lst = []
word = ""
for ch in new_sentence:
    if ch == " " or ch == "." or ch == "," or ch == ";" or ch == ":":
        if word != "":
            word_lst.append(word)
            word = ""
    else:
        word += ch
if word != "":
    word_lst.append(word)

print("List of words:", word_lst)
print("Number of words:", len(word_lst))
