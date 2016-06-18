/* arc.c
 * Junjie Qian, jqian.unl@gmail.com
 */

#include "arc.h"

/******* Arc, used to connect nodes between layers *****/
Arc::Arc() {
    /*** Constructor starts with random values
     * @param _weight, weight of the arc, starts with random value between -0.5/0.5
     * @param _delta, the updated weight of last iteration
     */
//    srand(time(NULL));
//    this->_weight = (rand()%2000)/1000.0 - 1.00;
    this->_delta = 0;
}

void Arc::setInNode(Node *node) {
    /* @function, set the input node of the arc
     */
    this->_in = node;
}

void Arc::setweight(double weight) {
    /* @function, set the weight of the arc
     */
    this->_weight = weight;
}

void Arc::setOutNode(Node *node) {
    /* @function, set the output node of the arc
     */
    this->_out = node;
}

double Arc::getinput() {
    /* @return, the input node's value of the arc
     */
    return this->_in->getval();
}

double Arc::getWeightInVal() {
    /* @return the inNode value and weight
     */
    return (this->_in->getval() * this->_weight);
}

double Arc::getWeightOutErr() {
    /* @return, the output weight err value of the arc
     * @param, this->_out->getdelta, the sigmoid activation value of the output node
     */
    return (this->_out->getdelta() * this->_weight);
}

void Arc::updateweight(double val, double rate) {
    /* @function, update the weight function, a momentum value added to improve the process
     */
    _weight += val * rate + this->_out->getmomentum() * _delta;
    _delta = val;
}

double Arc::getweight() {
    /* @return, the weight of the arc
     * this may not be accessed directly.
     */
    return this->_weight;
}