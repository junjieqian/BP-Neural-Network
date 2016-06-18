/* backprop.h
 * Junjie Qian, jqian.unl@gmail.com
 */

#ifndef _BACKPROP_H_
#define _BACKPROP_H_

#include <iostream>
#include <string>
#include "node.h"
#include "arc.h"
#include "pattern.h"
#include "network.h"

using std::string;

class NetWork;
class Node;
class Arc;
class Pattern;
class PatternList;

void thresholdTransfer(double threshold, double value[], int size, double *result);

class BackProp {
/* back propagation network constructor
 * @param input_node, hide_node, output_node, the nodes of 3 layers
 * @param learning_rate, learning rate to use in error calculation
 * @param iteration, the max number runs
 */
private:
    int input_node;
    int hide_node;
    int output_node;
    double learning_rate;
    double momentum;
    int iteration;
    NetWork * _network;
public:
    BackProp(int input, int hide, int output, double rate, double momentum,int iter);
    void trainNetWork(PatternList patterns, int max_match, double threshold);
    void runNetWork(double in[], double ret[]);
    void dumpnetwork(string filename);
};

#endif
