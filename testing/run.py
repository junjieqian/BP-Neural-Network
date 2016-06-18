#!/usr/bin/python

import os
import string
import subprocess

def changerate(v):
    fp = open("config")
    instr = ""
    for line in fp:
        if line.find("LearningRate:") >= 0:
            instr += "LearningRate: " + str(v) + '\n'
        else:
            instr += line
    fp.close()
    fo = open("config", 'w')
    fo.write(instr)
    fo.close()

def main():
    fp = open("rate_runs", 'w', 0)
    i = 0.01
    while i<0.2:
        cnt = 1
        changerate(i)
        while cnt < 3:
            os.system("/home/junjieq/project/bPNN/bpnn/BPNN.exe")
      #      process = subprocess.Popen("python cmp_ret.py results /home/jqian/datasets/bpnn_format/result".split(), stdout = subprocess.PIPE)
            process = subprocess.Popen("python /home/junjieq/project/bPNN/bpnn/testing/cmp_ret.py".split(), stdout = subprocess.PIPE)
            out,err = process.communicate()
            word = out.split('\n')
            fp.write("run with rate: " + str(i) + ", run index: " + str(cnt) + ", \t")
            for line in word:
                if line.find("prediction rate:") >= 0:
                    fp.write(line.split()[-1] + ', ')
                if line.find("false alarm rate:") >= 0:
                    fp.write(line.split()[-1] + ', \n')
            cnt += 1
        i += 0.01
    fp.close()

if __name__ == "__main__":
    main()
