/* trainner.h
 * Junjie Qian, jqian.unl@gmail.com
 */

#ifndef _TRAINNER_H_
#define _TRAINNER_H_

#include <string>
#include "backprop.h"
using std::string;

class BackProp;

class Trainner {
private:
    BackProp * bp;
public:
    Trainner(int in, int hide, int out, double rate, double momemtum, int ite);
    void train(string filename, int max_match, double threshold);
    void dumpNetWork(string filename);
};

#endif