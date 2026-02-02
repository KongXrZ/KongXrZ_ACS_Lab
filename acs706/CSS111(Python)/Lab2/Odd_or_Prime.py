n = int(input())
isprime = True
lst = []
for i in range(0,n):
  num = int(input())
  lst.append(num)
for num in lst:
  if num < 2:
    isprime = False
  elif num == 2:
    isprime = True
  elif num % 2 == 0:
    isprime = False
  else:
    j = 3
    for j in range(3,num,2):
      if num % j == 0 :
        isprime = False
        break
  if isprime or num % 2 != 0:
    print("T")
  else:
    print("F")