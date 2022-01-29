"""O(n log n)"""
# expect WA

n = int(input())
ar = [int(x) for x in input().split()]

s = 0
ans = 0
for i in ar:  # no sort
  s += i
  ans += s
print(ans)
