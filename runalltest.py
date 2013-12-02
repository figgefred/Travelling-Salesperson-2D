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

print "Found", len(f)-1, "tests."	

distances = [0] * (len(f)-1)
times = [0] * (len(f)-1)
errors = list()
for test in f:
	if test == ".gitignore":
		continue
	print "Running test:", test	
	try:		
		t = int(test)
		distance, time = runtest.runtest(sys.argv[1], testdir+str(t))
		distances[t] = distance
		times[t] = time		
	except Exception as ex:
		errors.append(test + ": " + ex)
		

for i in range(len(times)):
	print str(i)+","+str(distances[i])+","+str(times[i])

if len(errors) > 0:
	print "Errors occured on the following tests: " 
	for err in errors:
		print err

print
print "Average distance: ", sum(distances) / len(distances)
print "Average time: ", sum(times) / len(times)


	
	
