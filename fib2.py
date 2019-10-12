import sys
def fib(n):
	if n == 0:
		return 0
	a = [0]*(n+1)
	a[0] = 0
	a[1] = 1
	for i in range(2,n+1):
		a[i] = a[i-1] + a[i-2]
	return a[n]

if len(sys.argv) != 2:
	print("Usage: %s n"%sys.argv[0])
else:
	nth = fib(int(sys.argv[1]))
	print(nth)