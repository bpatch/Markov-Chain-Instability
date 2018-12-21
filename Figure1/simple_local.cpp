#include <random>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;



int main(int argc, char** argv){

	double ell = atof(argv[1]); // L = (0, ell);
	double epsilon = atof(argv[2]); //
	double N = atof(argv[3]); // Length of sample path
	int CurrentQueueState = atoi(argv[4]); // Initial Length of Queue
	double sample = atof(argv[5]);
	double MaxAllowedTime = atof(argv[6]);

	random_device rd;
	mt19937_64 mt(rd());

	std::uniform_real_distribution<double> U(0,1);

	std::ofstream outputFile1;
	std::ofstream outputFile2;
	std::ofstream outputFile3;

	outputFile1.open("Y_local_SamplePath_ell="+std::to_string(ell)+"_sample="+to_string(sample)+".csv");
	outputFile2.open("p_local_SamplePath_ell="+std::to_string(ell)+"_sample="+to_string(sample)+".csv");
	outputFile3.open("T_local_SamplePath_ell="+std::to_string(ell)+"_sample="+to_string(sample)+".csv");

	// Required objects
	int ProposedQueueState1;
	int ProposedQueueState2;
	double ProposedArrivalRate;
	double CurrentArrivalRate = epsilon*U(mt);
	double NextTime;
	double CumulativeTime = 0;
	int ServiceIndicator;

	outputFile2 << CurrentArrivalRate << ',';

	for (double j=0; j<=(N-1); ++j)
	{
		std::cout << 100.0*(j/(N-1)) << '%' << std::endl;
		ProposedQueueState1 = CurrentQueueState;
		NextTime = ceil(CurrentQueueState*0.5+1);
		// Obtain sample for current arrival rate
		for (int i = 1; i <= NextTime; i++)
	{
		if (U(mt) < CurrentArrivalRate)
		{
			ProposedQueueState1 = ProposedQueueState1 + 1;
		}
		if ( (U(mt) < 0.5) && (ProposedQueueState1 > 0))
		{
			ProposedQueueState1 = ProposedQueueState1-1;
		}
	}
	// Obtain sample for new arrival rate
	ProposedQueueState2 = CurrentQueueState;
	ProposedArrivalRate = (CurrentArrivalRate-epsilon) + 2*epsilon*U(mt);
	while ((ProposedArrivalRate > ell) || (ProposedArrivalRate < 0))
	{
		ProposedArrivalRate = (CurrentArrivalRate-epsilon)+2*epsilon*U(mt);
	}
	for (int i = 1; i <= NextTime; i++)
{
	if (U(mt) < ProposedArrivalRate)
	{
		ProposedQueueState2 = ProposedQueueState2 + 1;
	}
	if ( (U(mt) < 0.5) && (ProposedQueueState2 > 0))
	{
		ProposedQueueState2 = ProposedQueueState2 - 1;
	}
}
	// Compare samples
	if (ProposedQueueState2 >= ProposedQueueState1)
	{
		CurrentQueueState = ProposedQueueState2;
		CurrentArrivalRate = ProposedArrivalRate;
	}
	else if( U(mt) <= exp(ProposedQueueState2-ProposedQueueState1) )
	{
		CurrentQueueState = ProposedQueueState2;
		CurrentArrivalRate = ProposedArrivalRate;
	}
	else
	{
		CurrentQueueState = ProposedQueueState1;
	}

		CumulativeTime = CumulativeTime + NextTime;

		outputFile1 << CurrentQueueState << ',';
		outputFile2 << CurrentArrivalRate << ',';
		outputFile3 << CumulativeTime << ',';

	if (CumulativeTime > MaxAllowedTime)
	{
		j = N;
	}

	}


	outputFile1.close();
	outputFile2.close();
	outputFile3.close();

	return 0;
}
