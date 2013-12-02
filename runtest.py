#!/usr/bin/python
import os, sys, subprocess, math, time

timeout = 2000

def runtest(executable, test):		
	starttime = time.clock()
	p = subprocess.Popen([executable], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)	
	f = open(test)
	data = ""
	positions = list()
	for line in f:
		data += line
		w = line.split(" ")
		if len(w) < 2:
			continue
		pos = float(w[0]), float(w[1])
		positions.append(pos)
		
	stdout, stderr = p.communicate(input=data)
	# validate answer
	path = [int(l) for l in stdout.split("\n") if l != ""]
	return getPathDistance(positions, path), time.clock() - starttime
	
def getPathDistance(positions, path):
	distance = 0.0
	prevPos = positions[path[0]]
	for next in path[1:]:		
		nextPos = positions[next]
		distance += math.sqrt(abs(prevPos[0] - nextPos[0])**2 + abs(prevPos[1] - nextPos[1])**2)
		#print nextPos
		prevPos = nextPos
		
	distance += math.sqrt(abs(prevPos[0] - positions[path[0]][0])**2 + abs(prevPos[1] - positions[path[0]][1])**2)
	return distance
	
def testTheTest():
	p = 0, 0
	p2 = 0, 1
	p3 = 2, 2	
	assert(2.0 == getPathDistance([p, p2], [0, 1]))	
	assert(math.sqrt(8.0)*2 == getPathDistance([p, p3], [0, 1]))
	assert(math.sqrt(1) + math.sqrt(5) + math.sqrt(8.0) == getPathDistance([p, p2, p3], [0, 1, 2]))
	
	


if __name__ == '__main__':
	if len(sys.argv) < 3:
		print """
		USAGE: runtest.py <executable_file> <test_file>
		
		Will run given TSP test using executable and print distance of
		the path found and time taken.
		"""
		exit(1)
	testTheTest()
	print runtest(sys.argv[1], sys.argv[2])
	
	
	

