#!/usr/bin/python

'''
Runs all tests found in the tests folder.
'''

import runtest, sys, time
from os import walk
from threading import Thread
from Queue import Queue

num_threads = 2
testdir = "tests/"

if len(sys.argv) < 2:
	print """
	USAGE: runalltests.py <path_to_executable>
	"""
	exit(1)

q = Queue()
for (dirpath, dirnames, filenames) in walk(testdir):
	for test in filenames:
		if test != ".gitignore":
			q.put(test)
    
if q.empty():
	print "No tests found! Please run mktests.py"
	exit(1)
	
print "Found", q.qsize(), "tests."
distances = [0] * (q.qsize())
times = [0] * (q.qsize())
errors = list()

def Work():
	while not q.empty():
		test = q.get()		
		#print "Running test:", test	
		try:		
			t = int(test)
			distance, time = runtest.runtest(sys.argv[1], testdir+str(t))
			distances[t] = distance
			times[t] = time		
		except Exception as ex:
			errors.append(test + ": " + str(ex))
		q.task_done()
		
for _ in range(num_threads):
	t = Thread(target=Work)
	t.daemon = True
	t.start()
	
while not q.empty():
	time.sleep(1) # yield
	print "Queue left: ", q.qsize()


			

#for i in range(len(times)):
#	print str(i)+","+str(distances[i])+","+str(times[i])

if len(errors) > 0:
	print "Errors occured on the following tests: " 
	for err in errors:
		print err

print
print "Average distance: ", sum(distances) / len(distances)
print "Average time: ", sum(times) / len(times)


	
	
