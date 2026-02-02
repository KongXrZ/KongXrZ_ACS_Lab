dic = {1:25,2:30,3:35}
discount = 0
menu_lst=[]
cup_lst=[]
while True:
  menu = int(input())
  if 0 < menu <= 3:
    count = int(input())
    if count <= 0:
      break

    price = dic[menu]*count
    menu_lst.append(price)
    cup_lst.append(count)
  else:
    break

total_price = sum(menu_lst)
total_cup = sum(cup_lst)

if total_price >= 300:
  discount = total_price * 0.05
if total_cup >= 10:
  discount = total_price * 0.1

total_price -= discount
f_total = int(total_price)
if total_price - f_total >= 0.5:
  f_total += 1
print(f_total)