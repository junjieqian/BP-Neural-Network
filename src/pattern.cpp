/* pattern.h
 * Junjie Qian, jqian.unl@gmail.com
 */

#include "pattern.h"

Pattern::Pattern(double in[], int m, double out[], int n) {
	/*** Constructor for a pattern, with input_array, output_array and numbers of input and output
	 * @param
	 */
    int i = 0;
    this->m = m;
    this->n = n;
    this->_in = (double *)malloc(m*sizeof(double));
    this->_out = (double *)malloc(n*sizeof(double));
    while (i < m) {
        *(this->_in + i) = *(in + i);
        ++i;
    }
    i = 0;
    while(i < n) {
        *(this->_out + i) = *(out + i);
        ++i;
    }
    this->_trained = false;
}

double * Pattern::getinput() {
	// @return the input of the pattern
    return this->_in;
}

double * Pattern::getoutput() {
	// @return the output of the pattern
    return this->_out;
}

int Pattern::getinputsize() {
	// @return the inputsize of the pattern
    return this->m;
}

int Pattern::getoutputsize() {
	// @return the output size of the pattern
    return this->n;
}

bool Pattern::isTrained() {
	// @return whether the pattern is trained or not
    return this->_trained;
}

void Pattern::setTrained(bool v) {
    this->_trained = v;
}

PatternList::PatternList(string filename) {
	/*** Constructor for PatternList, read from files, format is input_array, input_number, output_number, output_array
	 * @param ins,outs, the input_array and output_array in the file
	 * @param m,n, the input number and output number
	 */
    int m;
    int n;
    string ins, outs;
    std::ifstream fp(filename.c_str());
    while (fp >> ins >> m >> n>> outs) {
        double * in = (double *)malloc(m*sizeof(double));
        double * out = (double *)malloc(n*sizeof(double));
        std::stringstream ss(ins);
        int i = 0;
        double temp;
        while(ss >> temp) {
            if (ss.peek() == ',') ss.ignore();
            *(in + i) = temp;
            ++i;
        }
        i = 0;
        std::stringstream ss2(outs);
        while(ss2 >> temp) {
            if (ss2.peek() == ',') ss2.ignore();
            *(out + i) = temp;
            ++i;
        }

        Pattern p(in, m, out, n);
        patterns.push_back(p);
    }
    fp.close();
}

Pattern PatternList::get(int i) {
	// @return the 'i'th element in the vector
    return patterns[i];
}

int PatternList::getsize() {
	// @return the size of the vector
    return patterns.size();
}

void PatternList::write(string filename) {
    // TODO: shall we rewrite everything? or append? if append, need to clear previous contents
    // std::ofstream fp(filename.c_str(), std::ofstream::out | std::ofstream::app);
    std::ofstream fp(filename.c_str(), std::ofstream::out);
    for (size_t i=0; i<patterns.size(); ++i) {
    	int m = patterns[i].getinputsize();
    	int n = patterns[i].getoutputsize();
    	double * in = (double *)malloc(m * sizeof(double));
    	double * out = (double *)malloc(n * sizeof(double));
    	in = patterns[i].getinput();
    	out = patterns[i].getoutput();
    	for (int j=0; j<m; ++j) 
    		fp << in[j] << ',';
    	fp << ' ' << m << ' ' << n << ' ';
    	for (int j=0; j<n; ++j) 
    		fp << out[j] << ',';
    	fp << "\n";
    }
    fp.close();
}

void PatternList::add(Pattern p) {
	// append one new pattern to the vector
	patterns.push_back(p);
}