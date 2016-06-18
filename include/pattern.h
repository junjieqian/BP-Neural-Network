/* pattern.h
 * Junjie Qian, jqian.unl@gmail.com
 */

#ifndef _PATTERN_H_
#define _PATTERN_H_

#include <vector>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;

class Pattern {
private:
    double *_in;
    double *_out;
    bool _trained;
    int m;
    int n;
public:
    Pattern(double in[], int m, double out[], int n);
    double *getinput();
    double *getoutput();
    int getinputsize();
    int getoutputsize();
    bool isTrained();
    void setTrained(bool v);
};

class PatternList {
private:
    vector<Pattern> patterns;
public:
    PatternList(string filename);
    Pattern get(int i);
    int getsize();
    void write(string filename);
    void add(Pattern p);
};

#endif