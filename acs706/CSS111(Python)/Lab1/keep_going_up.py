n = int(input())
is_safe = True
rock = []
while len(rock) < n:
    rock.extend(map(int,input().split()))
rock = rock[:n]
for i in range(1,n):
    if rock[i] < rock[i-1]:
        is_safe = False
        break
if is_safe == True:
    print("safe")
else:
    print("dangerous")

