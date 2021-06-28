#pragma once
#include "SeperatedProvince.h"

namespace elections {

	void printTheChosenElectors (DynamicArray < province*> provArr, DynamicArray < party*> partyArr);
	void printChosenElecAtProv  (const party& a,const int provinceArrIdx);
	void printTheResult         (DynamicArray < party*> partyArr, bool electionType, const int totalVotes=0, const int voterArrSize=0);
	void printDate              (const string& date);


}
