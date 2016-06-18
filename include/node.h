/* node.h
 * Junjie Qian, jqian.unl@gmail.com
 */

#ifndef _NODE_H_
#define _NODE_H_

#include <stdio.h>
#include <vector>
#include <math.h>
#include "arc.h"

using std::vector;

class Arc;

// abstract node object
// this is generalized object, and inheritenced by in/out/hide nodes
class Node {
protected:
        double _val;
        double _err;
        vector<Arc *> outArcs;
        vector<Arc *> inArcs;
        double _rate;
        double _momentum;
public:
        Node();
        virtual void seterr(double err);
        virtual double getval();
        virtual void setval(double val);
        virtual void connect(Node *des, Arc *arc);
        virtual double geterr();
        virtual double getmomentum();
        virtual double getdelta();
};

// in node object
class InNode: public Node {
private:
public:
        void setval(double val);
        double getval();
};

// out node object
class OutNode: public Node {
private:
        // double _rate;
        // double _momentum;
public:
        OutNode(double rate, double momentum);
        void runNode();
        void seterr(double err);
        void trainNode();
        double getdelta();
        double geterr();
        double getmomentum();
};

// hide node object
class HideNode: public Node {
private:
        // double _rate;
        // double _momentum;
public:
        HideNode(double rate, double momentum);
        void trainNode();
        void runNode();
};

#endif