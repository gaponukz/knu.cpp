def number(n: int) -> int:
    return 1 if (n == 1 or n == 2) else n * number(n - 2)

print(number(21))