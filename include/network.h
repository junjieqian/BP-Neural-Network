/* network.h
 * Junjie Qian, jqian.unl@gmail.com
 */

#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include "arc.h"
#include "node.h"

// for testing
#include <iostream>

// declare here for cross references
class Node;
class Arc;

using std::string;
using std::vector;

class NetWork {
private:
    vector<InNode> _inNode;
    vector<OutNode> _outNode;
    vector<HideNode> _hideNode;
    int bias;
    int insize;
    int outsize;
    int hidesize;
    vector<Arc *> _arc;
    double _rate;
    double _momentum;
public:
    NetWork(int input, int hide, int output, double rate, double momentum);
    ~NetWork();
    void runNetWork(double inputs[], double result[]);
    void trainNetWork(double correct[], int c_size, double result[]);
    void dumpNetWork(string filename);
    void printNetWork();
    void printvalues();
};

#endif
