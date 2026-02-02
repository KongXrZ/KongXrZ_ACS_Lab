max_val = None

while True:
    x = int(input())
    if x == 0:
        break
    if (max_val is None) or (x > max_val):
        max_val = x

print(f"The highest weigh is: {max_val}")
