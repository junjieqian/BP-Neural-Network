/* node.cpp
 * Junjie Qian, jqian.unl@gmail.com
 */

#include "node.h"

/************* Abstract Node object ******************/
/** use default constructor and destructor */
Node::Node() {
    /* @constructor, default value should be random set later
     */
    this->_val = 1.0;
    this->_err = 1.0;
}

void Node::seterr(double err) {
    /** set error function is not really define the error value
     * @param _err, the expected value of the output
     * @error function, err = Execute*(1-execute)*(expected - executed)
     */
    this->_err = err;
}

double Node::getval() {
    /* @return, the value of the node
     */
    return this->_val;
}

void Node::setval(double val) {
    /* @function, set the value of the node
     */
    this->_val = val;
}

void Node::connect(Node *des, Arc *arc) {
    /* @function, set the input and output nodes of the arc
     * 
     */
    arc->setInNode(this);
    arc->setOutNode(des);
    this->outArcs.push_back(arc);
    des->inArcs.push_back(arc);
}

double Node::getmomentum() {
    /* @return, the momentum of the node
     * virtual function, declared for output/hide nodes only
     */
    return this->_momentum;
}

double Node::geterr() {
    /* @return, the err value of the node
     */
    return this->_err;
}

double Node::getdelta() {
    /* @return, the sigmoid activation value of the node
     */
    return ((1.0 - this->_val * this->_val) * (this->_err - this->_val));
}

/**************** InNode object *******************/
/* redefine the virtual functions */
void InNode::setval(double value) {
    this->_val = value;
}

double InNode::getval() {
    return this->_val;
}

/***************** OutNode object ***************/
OutNode::OutNode(double rate, double momentum) {
    this->_rate = rate;
    this->_momentum = momentum;
}

void OutNode::runNode() {
    /** get the cumulative weight values of the node
     * using "tanh" instead of sigmoid function
     */
    double total = 0.0;
    for (size_t i=0; i<inArcs.size(); ++i)
        total += inArcs[i]->getWeightInVal();
    this->_val = tanh(total); //(1.0/(1.0 + exp(-total)));
}

double OutNode::getdelta() {
    /* @return, the sigmoid activation value of the node
     * Redefine virtual functions, needed?
     */
    return ((1.0 - this->_val * this->_val) * (this->_err - this->_val));
}

void OutNode::trainNode() {
    /** update the weight of the node value
     */
    for (size_t i=0; i<inArcs.size(); ++i)
        inArcs[i]->updateweight(this->getdelta()* inArcs[i]->getinput(), this->_rate);
}

void OutNode::seterr(double err) {
    this->_err = err;
}

double OutNode::geterr() {
    return this->_err;
}

double OutNode::getmomentum() {
    return this->_momentum;
}

/***************** HideNode object ***********/
HideNode::HideNode(double rate, double momentum) {
    this->_rate = rate;
    this->_momentum = momentum;
}

void HideNode::runNode() {
    /** get the cumulative weight values of the node
    */
    double total = 0.0;
    for (size_t i=0; i<inArcs.size(); ++i) {
        total += inArcs[i]->getWeightInVal();
    }
    this->_val = tanh(total); //(1.0/(1.0 + exp(-total)));
}

void HideNode::trainNode() {
    double total = 0.0;
    for (size_t i=0; i<outArcs.size(); ++i)
        total += outArcs[i]->getWeightOutErr();
    this->_err = (1.0 - this->_val * this->_val) * total;
    for (size_t i=0; i<inArcs.size(); ++i)
        inArcs[i]->updateweight(this->_err * inArcs[i]->getinput(), this->_rate);        
}
