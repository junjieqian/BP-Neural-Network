/* backprop.cpp
 * Junjie Qian, jqian.unl@gmail.com
 */

#include "backprop.h"

BackProp::BackProp(int input, int hide, int output, double rate, double momentum,int iter) {
    /* Constructor for back propagation algorithm
     * @param this.*, the private objects/values used in the object "BackProp".
     */
    this->input_node  = input;
    this->hide_node   = hide;
    this->output_node = output;
    this->learning_rate = rate;
    this->momentum = momentum;
    this->iteration = iter;
    this->_network = new NetWork(this->input_node, this->hide_node, this->output_node, this->learning_rate, this->momentum);
}

void BackProp::runNetWork(double in[], double ret[]) {
    this->_network->runNetWork(in, ret);
}

void BackProp::trainNetWork(PatternList patterns, int max_match, double threshold) {
    /*** Back propagation algorithm to train the network
     * @param counter, count how many iterations
     * @param success, count how many successful nodes
     * @param limit, the size of patterns
     * @return value, the success nodes number
     */

    int limit = patterns.getsize();
    int counter = 0;
    // int success = 0;
    bool flag = true;

    std::cout << "Total pattern number: " << limit << std::endl;
    while (flag) {

        std::cout << " . " << std::flush; // show the progress

        // success = 0;
        for (int i=0; i<limit; ++i) {
            Pattern pattern = patterns.get(i);

            // run the network 
            int size = pattern.getinputsize();
            double *ret = (double *)malloc(size * sizeof(double));
            this->_network->runNetWork(pattern.getinput(), ret);

            // train the network
            size = pattern.getoutputsize();
            double * rawret = (double *)malloc(size * sizeof(double));
            double * rets = (double *)malloc(size * sizeof(double));
            double * truth = (double *)malloc(size * sizeof(double));

            this->_network->trainNetWork(pattern.getoutput(), size, rawret);

            // TODO: the first element is the threshold value, NEED to adjust in future.
            // thresholdTransfer(threshold, pattern.getoutput(), size, truth);
            // thresholdTransfer(threshold, rawret, size, rets);

            // pattern.setTrained(true);

            // for(int j=0; j<size; ++j) {
            //     if (rets[j] != truth[j]) {
            //         pattern.setTrained(false);
            //         break;
            //     }
            // }

            // // if pattern shown as expected, increase the successful node
            // if (pattern.isTrained())
            //     ++success;

            free (ret);
            free (rawret);
            free (rets);
            free (truth);
        }

        //     // make sure all nodes are successful
        // if (success < limit) 
        //     flag = true;
        // else 
        //     flag = false;

        // // donot want the infinite loop, set the maximum iteration number
        if (counter > this->iteration)
            flag = false;

        ++counter;
    }
    std::cout << std::endl;

    // following is for test purpose
    // for (int i=0; i<limit; ++i) {
    //     Pattern pattern = patterns.get(i);
    //     int size = pattern.getinputsize();
    //     double *ret = (double *)malloc(sizeof(double));
    //     this->_network->runNetWork(pattern.getinput(), ret);
    //     for (int j=0; j<size; ++j) std::cout << pattern.getinput()[j] << ", ";
    //     std::cout << ret[0] << "\n";
    //     free (ret);
    // }
    // this->_network->printvalues();
    // std::cout << "======\n";
    // testing ends

    return;
}

void BackProp::dumpnetwork(string filename) {
    // this->_network->printNetWork();
    this->_network->dumpNetWork(filename);
}

void thresholdTransfer(double threshold, double value[], int size, double *result) {
    /* convert a double array to a thresholed array
     * @param 0 or 1 for predicted, -1 means not in the threshold_range
     */
    double upper = 1.00 - threshold;
    double lower = threshold;

    for (int i=0; i<size; ++i) {
        if (value[i] > upper)
            *(result+i) = 1.0;
        else if (value[i] < lower) 
            *(result+i) = 0.0;
        else 
            *(result+i) = -1.0;
    }
}
