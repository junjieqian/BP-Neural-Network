/* tester.cpp
 * Junjie Qian, jqian.unl@gmail.com
 */

#include "tester.h"

Tester::Tester(string filename) {
    /*** Constructor, read the network implementation from the model file
     */
    
    std::ifstream fp (filename.c_str());
    network = (NetWork *)malloc(sizeof(NetWork));
    fp.read(reinterpret_cast<char *>(network), sizeof(NetWork));
    fp.close();
    // testing for the network implementation
    // this->network->printNetWork();
}

void Tester::test(string filename, int innode, string resfile) {
    /*** test function, test all the records in the testfile
     */
    std::ifstream fp(filename.c_str());
    string line = "";
    //TODO: suppose there is only one output node.
    vector<double> bpret;

    while(fp >> line) {
        double *in = (double *)malloc(innode * sizeof(double));
        double *out = (double *)malloc(sizeof(double));
        std::stringstream ss(line);
        double temp;
        int i = 0;
        while(ss >> temp) {
            if (ss.peek() == ',')
                ss.ignore();
            *(in + i) = temp;
            ++i;
        }
        this->network->runNetWork(in, out);
        double val = *out;
        bpret.push_back(val);

        free (in);
        free (out);
    }
    fp.close();

    std::cout << "Dumping raw results\n";
    // testing/comparison purpose
    std::ofstream ftemp("result_noVoting", std::ofstream::out);
    for(size_t i=0; i<bpret.size(); ++i) {
        double val = bpret[i];
//        std::cout << bpret[i] << std::endl;
//        ftemp << bpret[i] << std::endl;

        if (val < 0.5)
            ftemp << "-1, " << val << "\n";
        else
            ftemp << "1, " << val << "\n";

    }
    ftemp.close();
/*
    // TODO, the 'n' needs to be passed in, current set as 13 /
    // TODO, what the ret fail number is? /
    vector<int> ret;
    for (size_t i=0; i<bpret.size(); ++i) {
        if (bpret[i] > 0.499)
            ret.push_back(1);
        else
            ret.push_back(voting(bpret, 13));
    }

    std::cout << "Dumping voting results\n";

    std::ofstream fout(resfile.c_str(), std::ofstream::out);
    for (size_t i=0; i<ret.size(); ++i)
        fout << ret[i] << "\n";
    fout.close();
*/
}

// this is the voting
// N number future is changing
/* voting algorithm may need to be redefine
 * voting is from the history data of the record, instead of the neighbor data of the record
 */
double sum(vector<double> c) {
    double ret = 0.0;
    for (size_t i=0; i<c.size(); ++i)
        ret += c[i];
    return ret;
}

int voting(vector<double> in, int n) {
    /*** voting algorithm
     * @param n, the voting array size
     */
    int insize = in.size();
    vector<double> c;
    // initialization, use memset instead later
    for (int i=0; i<n; ++i) c.push_back(0.0);
    for (int i=0; i<insize; ++i) {
        c[(i-1)%n+1] = in[i];
        if (sum(c) > n/2.0) {
            return -1;
        }
    }
    return 1;
}
