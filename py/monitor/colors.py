#!/usr/bin/python
print(f"\033[31m red\033[0m")
print(f"\033[32m green\033[0m")
print(f"\033[33m yellow\033[0m")

print(f"\033[34m blue\033[0m")
print(f"\033[35m violet\033[0m")
print(f"\033[36m lightblue\033[0m")

print(f"\033[31;47m red on white\033[0m")

# \033[<foreground_code>;<background_code>m
# background
# Black: 40
# Red: 41
# Green: 42
# Yellow: 43
# Blue: 44
# Magenta (Purple): 45
# Cyan: 46
# White: 47