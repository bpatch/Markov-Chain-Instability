#include <random>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;



int main(int argc, char** argv){

	double ell = atof(argv[1]); // L = (0, ell);
	double N = atof(argv[2]); // Length of sample path
	int CurrentQueueState = atoi(argv[3]); // Initial Length of Queue
	double sample = atof(argv[4]);

	random_device rd;
	mt19937_64 mt(rd());

	std::uniform_real_distribution<double> U(0,1);

	std::ofstream outputFile1;
	std::ofstream outputFile2;
	std::ofstream outputFile3;

	outputFile1.open("Y_global_SamplePath_ell="+std::to_string(ell)+"_sample="+to_string(sample)+".csv");
	outputFile2.open("p_global_SamplePath_ell="+std::to_string(ell)+"_sample="+to_string(sample)+".csv");
	outputFile3.open("T_global_SamplePath_ell="+std::to_string(ell)+"_sample="+to_string(sample)+".csv");

	// Required objects
	int ProposedQueueState;
	double ProposedArrivalRate;
	double CurrentArrivalRate;
	double r;
	double NextTime;
	double CumulativeTime = 0;
	int ServiceIndicator;

	outputFile2 << ell*U(mt) << ',';

	for (double j=0; j<=(N-1); ++j)
	{
		std::cout << 100.0*(j/(N-1)) << '%' << std::endl;
		ProposedQueueState = CurrentQueueState;
		ProposedArrivalRate = ell*U(mt);
		NextTime = ceil(CurrentQueueState*0.5+1);
		for (int i = 1; i <= NextTime; i++)
	{
		if (U(mt) < ProposedArrivalRate)
		{
			ProposedQueueState = ProposedQueueState + 1;
		}
		if ( (U(mt) < 0.5) && (ProposedQueueState > 0))
		{
			ProposedQueueState = ProposedQueueState-1;
		}
	}
	if (ProposedQueueState >= CurrentQueueState)
	{
		CurrentQueueState = ProposedQueueState;
		CurrentArrivalRate = ProposedArrivalRate;
	}
	else if( U(mt) <= exp(ProposedQueueState-CurrentQueueState) )
	{
		CurrentQueueState = ProposedQueueState;
		CurrentArrivalRate = ProposedArrivalRate;
	}

		CumulativeTime = CumulativeTime + NextTime;

		outputFile1 << CurrentQueueState << ',';
		outputFile2 << CurrentArrivalRate << ',';
		outputFile3 << CumulativeTime << ',';
	}


	outputFile1.close();
	outputFile2.close();
	outputFile3.close();

	return 0;
}
