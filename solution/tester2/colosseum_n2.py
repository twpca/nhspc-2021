"""colosseum_n2: O(n^2)"""

n = 0
m = 0
vx = [-1]
vy = [-1]
t = [-1]
w = [-1]
ans = 0
dp = []


def dedup(ar):
  """dedup"""
  res = []
  for d in sorted(ar):
    p = (-1, -1)
    if res:
      p = res[-1]
    if d[1] <= p[1]:
      continue
    res.append(d)
  return res


def insert(x, y):
  """insert"""
  global dp
  dp.append((x, y))


def debug_print(i):
  """debug_print"""
  print('\n===== i=%d =====' % i)
  for d in dp:
    print(d[0], d[1])


n, m = [int(x) for x in input().split()]
for i in range(0, n):
  a, b, c, d = [int(x) for x in input().split()]
  vx.append(a)
  vy.append(b)
  t.append(c)
  w.append(d)

for i in range(1, n + 1):
  insert(0, 0)
  mxv = -1
  for d in dp:
    if d[0] < vx[i] and d[1] >= vy[i]:
      mxv = max(mxv, d[1])

  for idx in range(0, len(dp)):
    if dp[idx][0] >= vx[i] and dp[idx][1] >= vy[i]:
      dp[idx] = (dp[idx][0] + t[i], dp[idx][1] + w[i])

  if mxv != -1:
    insert(vx[i] + t[i], mxv + w[i])
  dp = dedup(dp)

  for d in dp:
    if d[0] <= m:
      ans = max(ans, d[1])
  #debug_print(i)

print(ans)
