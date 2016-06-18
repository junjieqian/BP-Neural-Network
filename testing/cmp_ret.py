#!/usr/bin/python

import sys
import string

def main():
#    if (len(sys.argv)) < 3:
#        sys.exit("Usage: %s test-result expected-result"%sys.argv[0])

    testfile = open("/home/junjieq/project/bPNN/bpnn/result_noVoting")
    testresult = []
    for line in testfile:
        testresult.append(line.split(',')[0])

    testfile.close()
    expectfile = open("/home/junjieq/datasets/bpnn_format/result")
    i = 0
    fail_correct = 0
    fail = 0
    good = 0
    good_false = 0
    for line in expectfile:
        word = line.split()
        if word[-1].find(',') > 0:
            res = word[-1].split(',')[0]
        else:
            res = word[-1].split('\n')[0]
        if int(res) == -1:
            fail += 1
            if testresult[i] == '-1':
                fail_correct += 1
        if int(res) == 1:
            good += 1
            if testresult[i] == '-1':
                good_false += 1
        i += 1
    expectfile.close()
#    print "correctly predicted: " + str(fail_correct) + ", total failed: " + str(fail)
#    print "false predicted: " + str(good_false) + ", total good: " + str(good)
    print "prediction rate: " + str(float(float(fail_correct)/float(fail)))
    print "false alarm rate: " + str(float(float(good_false)/float(good)))

if __name__ == "__main__":
    main()
