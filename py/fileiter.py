import glob
import os

includes = ['cpp', 'bash']
files = set(glob.glob('*.*'))
for include in includes:
    for f in (os.path.join(p, f)
              for (p, _, fs) in os.walk(include) for f in fs):
        files.add(f)

print(files)
# for walk in walks:
#  print(walk)
# for p, d, f in os.walk(walk):
#     print(p)
