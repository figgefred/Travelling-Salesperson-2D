#!/usr/bin/python

import runtest, sys
from os import walk

'''
Runs all tests found in the tests folder.
'''

testdir = "tests/"


if len(sys.argv) < 2:
	print """
	USAGE: runalltests.py <path_to_executable>
	"""
	exit(1)

f = []
for (dirpath, dirnames, filenames) in walk(testdir):
    f.extend(filenames)
    
if len(f) == 0:
	print "No tests found! Please run mktests.py"
	exit(1)

print "Found", len(f), "tests."	

distances = list()
times = list()
for test in f:
	if test == ".gitignore":
		continue
	print "Running test:", test	
	try:
		distance, time = runtest.runtest(sys.argv[1], testdir+test)
		distances.append(distance)
		times.append(time)
	except Exception as ex:
		print ex
		

print 
print "Average distance: ", sum(distances) / len(distances)
print "Average time: ", sum(times) / len(times)


	
	
