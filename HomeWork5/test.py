def number(n):
    if n == 1:
        return 0.5
    
    return (n / (n + 1))  * number(n - 2)

index = 0
for i in range(1, 5):
    _number = number(i + index)
    index += 1
    print(_number)

# print(number(1)) # 1 = 0
# print(number(3)) # 2 = 1
# print(number(5)) # 3 = 2
# print(number(7)) # 4 = 3
