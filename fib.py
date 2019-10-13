import sys
import time

def fib1(n):
	if n == 0:
		return 0
	if n == 1:
		return 1
	return fib1(n-1)+fib1(n-2)

def fib2(n):
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
	start = time.time()
	nth = fib1(int(sys.argv[1]))
	end = time.time()
	print(nth,end - start)

	start = time.time()
	nth = fib2(int(sys.argv[1]))
	end = time.time()
	print(nth,end - start)