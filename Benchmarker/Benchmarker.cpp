#include "Benchmarker.h"
#include <Windows.h>

using namespace std;


// some function
void Foo() {
    Sleep(1);
}


int main()
{
    cout << "Hello World!\n";

    
    /*************************************
    * Performing a singular benchmarking without repetition
    **************************************/
    
    Benchmarker bench1;
    bench1.begin();
    Foo();
    bench1.terminate();

    cout.precision(20);
    cout << "Single benchmarking suration was: " << fixed << bench1.getSingleDur(MICROSEC) << endl;

    bench1.report();

    /*************************************
    * Performing a repetitive benchmarking with a high number of repetitions
    **************************************/
    
    cout << endl << "Press Enter to commence benchmarking ...\n";
    cin.get();

    // Defining number of repetitions for the benchmarking
    unsigned numRepetitions = 1000;

    Benchmarker bench2(numRepetitions);
    bench2.begin();
    for (unsigned i = 0;i < numRepetitions;i++) {

        // some code
        
        // Benchmarking ---------------------
        bench2.tic();
        Foo();
        bench2.toc();
        // ----------------------------------

        // some other code
    }
    bench2.terminate();

    cout << endl << "Running getDurations() ...\n";
    vector<double> results = bench2.getDurations(MICROSEC);

    cout << "Acquired variables are:\n";
    cout << "Min: " << fixed << results[0] << endl;
    cout << "Avg: " << fixed << results[1] << endl;
    cout << "Max: " << fixed << results[2] << endl;
    cout << "Tot: " << fixed << results[3] << endl;

    cout << endl << "Running report() ...\n";
    bench2.report(MICROSEC);

    cout << endl << "Running print() ...\n";
    bench2.print();

}

