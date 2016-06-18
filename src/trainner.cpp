/* trainner.cpp
 * Junjie Qian, jqian.unl@gmail.com
 */

#include "trainner.h"

Trainner::Trainner(int in, int hide, int out, double rate, double momentum, int ite) {
    bp = new BackProp(in, hide, out, rate, momentum, ite);
}

void Trainner::train(string filename, int max_match, double threshold) {
    /* @function, training the network
     */
    PatternList patterns(filename);
    this->bp->trainNetWork(patterns, max_match, threshold);
}

void Trainner::dumpNetWork(string filename) {
    /*** dump the network
     */
    this->bp->dumpnetwork(filename);
}