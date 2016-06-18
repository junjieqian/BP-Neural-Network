/* arc.h
 * Junjie Qian, jqian.unl@gmail.com
 */

#ifndef _ARC_H_
#define _ARC_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <math.h>
#include "node.h"

class Node;

class Arc{
private:
    double _weight;
    double _delta;
    Node *_in;
    Node *_out;
public:
    Arc();
    double getinput();
    void setInNode(Node *node);
    void setOutNode(Node *node);
    double getWeightInVal();
    double getWeightOutErr();
    void updateweight(double val, double rate);
    double getweight();
    void setweight(double w);
};

#endif