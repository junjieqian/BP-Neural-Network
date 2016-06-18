/* network.cpp
 * Junjie Qian, jqian.unl@gmail.com
 */
#include "network.h"

/****************** NetWork object *******************/
NetWork::NetWork(int input, int hide, int output, double rate, double momentum) {
    /*** constructor of the network
     * @param _inNode, _hideNode, _outNode define the nodes in the network as array
     * @param bias, the number of bias nodes
     */
    this->bias = 2;
    this->insize = input + bias;
    for (int i=0; i<this->insize; ++i) {
        InNode temp;
        this->_inNode.push_back(temp);
    }

    this->outsize = output;
    for (int i=0; i<this->outsize; ++i) {
        OutNode temp(rate, momentum);
        this->_outNode.push_back(temp);
    }

    this->hidesize = hide;
    for (int i=0; i<this->hidesize; ++i) {
        HideNode temp(rate, momentum);
        this->_hideNode.push_back(temp);
    }

    this->_rate = rate;
    this->_momentum = momentum;

    srand(time(NULL));
    // connect the in nodes and hide nodes
    for (int j=0; j<this->insize; ++j) {
        for (int k=0; k<hide; ++k) {
            Arc * a = new Arc;
            a->setweight((rand()%1000)/1000.0 - 0.50);
            this->_inNode[j].connect(&(this->_hideNode[k]), a);
            this->_arc.push_back(a);
        }
    }

    // connect the hide nodes and out nodes
    for (int j=0; j<hide; ++j) {
        for (int k=0; k<output; ++k) {
            Arc * a = new Arc;
            a->setweight((rand()%2000)/1000.0 - 1.00);
            this->_hideNode[j].connect(&(this->_outNode[k]), a);
            this->_arc.push_back(a);
        }
    }
}

NetWork::~NetWork() {
    /*** Destructor, clear all patterns.
     * TODO: is this needed?
     */
    this->_inNode.clear();
    this->_hideNode.clear();
    this->_outNode.clear();
    this->_arc.clear();
}

void NetWork::runNetWork(double inputs[], double result[]) {
    /*** run the network function
     * set the values of the in nodes
     */
    for (int i=0; i<this->insize - this->bias; ++i)
        this->_inNode[i].setval(inputs[i]);
    for (int i=0; i<this->hidesize; ++i)
        this->_hideNode[i].runNode();
    for (int i=0; i<this->outsize; ++i)
        this->_outNode[i].runNode();
    for (int i=0; i<this->outsize; ++i)
        result[i] = this->_outNode[i].getval();
    return;
}

void NetWork::trainNetWork(double correct[], int c_size, double result[]) {
    /* train the network
     * correct array is for the network
     */
    for (int i=0; i<c_size; ++i)
        this->_outNode[i].seterr(correct[i]);
    for (int i=this->outsize-1; i>=0; --i)
        this->_outNode[i].trainNode();
    for (int i=this->hidesize-1; i>=0; --i)
        this->_hideNode[i].trainNode();

    for (int i=0; i<this->outsize; ++i)
        result[i] = this->_outNode[i].getval();
    return;
}

void NetWork::dumpNetWork(string filename) {
    /* dump the network
     * the key of the network is the weight of the arcs
     */
    /** dump the object directly, #TODO Debug the arc mem loc */
    std::ofstream fp(filename.c_str(), std::ofstream::out);
    fp.write(reinterpret_cast<char *>(this), sizeof(*this));
    fp.close();
}

void NetWork::printNetWork() {
    /*** print the attributes of the network
     * For testing purpose only
     */
    std::cout << this->insize << ' ' << this->hidesize << ' ' << this->outsize << ' ' << this->_rate << ' ' << this->_momentum << std::endl;
    std::cout << "Arc values " << this->_arc.size() << std::endl;
    for (size_t i=0; i<this->_arc.size(); ++i) {
        std::cout << this->_arc[i]->getweight() << ' ';
    }
    std::cout << std::endl;
}

void NetWork::printvalues() {
    /*** this is for test purpose */
    for (size_t i=0; i<_arc.size(); ++i)
        std::cout << _arc[i]->getweight() << ", ";
    std::cout << "\n";
}
