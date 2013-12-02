#!/usr/bin/python

import random
import sys

max_bound = 10e6
test_dir = "tests/"
number_of_cities = 1000

def createTest(filename):
	f = open(filename, 'w+')
	f.write(str(number_of_cities) + "\n")
	for i in range(number_of_cities):
		f.write(str(random.random() * max_bound) + " " + str(random.random() * max_bound)+"\n")
	f.close()

if len(sys.argv) < 2:
	print """
	USAGE: mktests.py <number of tests>
	"""
	exit(1)
	
number_of_tests = int(sys.argv[1])
for i in range(number_of_tests):
	filename = test_dir + str(i)
	createTest(filename)
	print "["+str(i)+"] Test created."
	
print "Done! :)"
	
	

