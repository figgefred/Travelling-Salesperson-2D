#!/usr/bin/python
import os, sys, subprocess, math, time

timeout = 2000

def runtest(executable, test):		
	starttime = time.time()
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
	if stderr or stdout == "":
		raise Exception(stderr)
		
		
	endtime = time.time() - starttime
	path = [int(l) for l in stdout.split("\n") if l != ""]
	dist = getPathDistance(positions, path)
	if endtime >= 2.0:
		raise Exception("Time limit exceeded " + str(endtime) + "s. \n" + "Answer was still valid: " + str(dist) + " "+ str(endtime));		
	return dist, endtime
	
def getPathDistance(positions, path):
	distance = 0.0
	prevPos = positions[path[0]]
	visited = set()
	visited.add(path[0])
	for next in path[1:]:		
		if next in visited:
			raise Exception("Validation failed. Revisited the same node!")
			
		visited.add(next)
		nextPos = positions[next]
		distance += math.sqrt(abs(prevPos[0] - nextPos[0])**2 + abs(prevPos[1] - nextPos[1])**2)
		#print nextPos
		prevPos = nextPos
	
	# check so all nodes were visited.
	if len(visited) != len(positions):
		raise Exception("Validation failed. Did not visit all nodes!")
		
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
	#print time.time()
	testTheTest()
	print runtest(sys.argv[1], sys.argv[2])
	#print time.time()
	
	
	

