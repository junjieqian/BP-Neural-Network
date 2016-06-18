/* tester.h
 * Junjie Qian, jqian.unl@gmail.com
 */

#ifndef _TESTER_H_
#define _TESTER_H_

#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include "network.h"
using std::string;
using std::vector;

//for testing
#include <iostream>

class NetWork;

double sum(vector<double> c);
int voting(vector<double> in, int n);

class Tester {
private:
    NetWork *network;
public:
    Tester(string filename);
    void run(double in[], double ret[]);
    void test(string filename, int innode, string resfile);
};

#endif