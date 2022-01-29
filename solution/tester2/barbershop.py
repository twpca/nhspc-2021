"""O(n log n)"""

n = int(input())
ar = [int(x) for x in input().split()]

s = 0
ans = 0
for i in sorted(ar):
  s += i
  ans += s
print(ans)
