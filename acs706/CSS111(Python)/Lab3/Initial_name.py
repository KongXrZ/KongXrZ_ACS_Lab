names = input("")
lst = []
if not(1 <= len(names) <=100):
  exit()
for ch in names:
  if not(ch.isalpha() or ch == ' '):
    exit()
name = names.upper().split()

for i in name:
  if i[0] not in lst:
    lst.append(i[0])
for j in lst:
  print(j,end=".")