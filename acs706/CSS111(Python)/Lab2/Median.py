n = int(input())
if 1 <= n <= 1000:
  lst = input().split()
  lst = [int(i) for i in lst]
  lst.sort()
  lst = lst[:n]

  if n % 2 == 0:
    med_index = n//2
    med = (lst[med_index-1] + lst[med_index])/2
  else:
    med_index = n//2
    med = lst[med_index]
  print("{:.2f}".format(float(med)))
  