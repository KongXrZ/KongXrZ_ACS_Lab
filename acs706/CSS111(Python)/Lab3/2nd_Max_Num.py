nums=[4,9,3,0,2]
if len(nums) < 2:
  print(None)
else:
  max_num = float('-inf')
  max_num2 = float('-inf')

  for i in nums:
    if  i > max_num:
      max_num2 = max_num
      max_num = i
    elif i > max_num2 and i != max_num:
      max_num2 = i
  print(max_num2)