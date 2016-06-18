/* main.cpp
 * This is taken as demo main function
 * Junjie Qian, jqian.unl@gmail.com
 */

#include <fstream> // std::fstream
//#include <stdio.h>
#include <stdlib.h> // atoi
#include <iostream> // std::cout
#include <string> // std::string
#include <sstream>

#include "trainner.h"
#include "tester.h"

using namespace std;

// everything starts from here
int main(int argc, char ** argv) {
    if (argc>1) {
        printf("No arguments taken, modify the config file instead\n");
        return 0;
    }

    ifstream fp("config");
    string line;
    string trainfile = "";
    string testfile = "";
    string trainset = "model";
    string resfile = "results";
    int inNode = 19;
    int hideNode = 30;
    int outNode = 1;
    double threshold = 0.9;
    int iterations = 400;
    double learningRate = 0.2;
    double momentum = 0.2;
    if (fp) {
        while(getline(fp, line)) {
            stringstream ss(line);
            string a, b;
            ss >> a >> b;
            if (a == "TrainDataset:") trainfile = b;
            else if (a == "TestDataset:") testfile = b;
            else if (a == "TrainModel: ") trainset = b;
            else if (a == "TestingResults: ") resfile = b;
            else if (a == "InputNodeNumber:") inNode = atoi(b.c_str());
            else if (a == "HideNodeNumber:") hideNode = atoi(b.c_str());
            else if (a == "OutputNodeNumber:") outNode = atoi(b.c_str());
            else if (a == "Iterations:") iterations = atoi(b.c_str());
            else if (a == "LearningRate:") learningRate = atof(b.c_str());
            else if (a == "Threshold:") threshold = atof(b.c_str());
            else if (a == "Momentum:") momentum = atof(b.c_str());
            else cout << "Attention: argument " << a << " not recognized\n";
        }
    } else {
        printf("Config file needed\n");
        return 0;
    }
    cout << "========Defined parameters include: ========\n\tDataSet name: " << trainfile 
    	<< "\n\tInput node number: " << inNode << "\n\tHide node number: " 
    	<< hideNode << "\n\tOutput node number: " << outNode << "\n\tMax Iterations: " 
        << iterations << "\n\tLearning Rate: " << learningRate << "\n\tThreshold: " 
        << threshold << "\n\tMomentum: " << momentum << endl;
    /******************** Parameters set ***********************/

    Trainner tr(inNode, hideNode, outNode, learningRate, momentum, iterations);
    int max_match = 300000;
    cout << "============Trainning=================\n";
    tr.train(trainfile, max_match, threshold);
    cout << "===== Train finished, dumping models ===== \n";
    tr.dumpNetWork(trainset);

    cout << "============Testing=================\n";
    cout << "\tTrainning model file is: " << trainset << "\n\tTesting file is: " 
        << testfile << "\n\tResults file is: " << resfile << endl;
    Tester te(trainset);
    te.test(testfile, inNode, resfile);

    return 0;
}