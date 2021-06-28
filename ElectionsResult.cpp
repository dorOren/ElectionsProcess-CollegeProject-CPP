#include "ElectionsResult.h"

namespace elections {

	void printTheChosenElectors (DynamicArray < province*> provArr, DynamicArray < party*> partyArr)
	{
		for (int i = 0; i < provArr.size(); i++) {
			cout << "The province name is : " << provArr[i]->getName().c_str() << "\n";
			cout << "The number of senastors at this province is : " << provArr[i]->getSenNum() << "\n";
			cout << "The precentage of voting is : " << provArr[i]->returnPercent() << "%\n";
			for (int j = 0; j < partyArr.size(); j++) {
				printChosenElecAtProv(*partyArr[j], i);
			}
		}
	}
	void printChosenElecAtProv  (const party& a, const int provinceArrIdx)
	{
		cout << "party leader ID: " << a.get_leaderID() << "\n";
		cout << "party perecent of the votes:  " << a.get_province(provinceArrIdx).get_perecent() << "%" << "\n";
		cout << "Chosen senator ID: "<<endl;
		for (int i = 0; i < a.get_province(provinceArrIdx).get_electorsSelected() && 
			            i < a.get_province(provinceArrIdx).get_memLogSize(); i++) {
			cout << i + 1 << "." << a.get_province(provinceArrIdx).get_memID(i) << endl;
		}
		cout << "\n\n";
	}
	void printTheResult         (DynamicArray < party*> partyArr, bool electionType, const int totalVotes, const int voterArrSize)
	{
		if (electionType == normal) {
			DynamicArray<party*> arr = partyArr;
			arr.pointersSort();
			if (partyArr.size() > 0) {
				arr[0]->sumPartyVotes();
				cout << "The winner is: " << arr[0]->get_leaderID() << "\n";
				cout << "ID: " << arr[0]->get_leaderID() << "\n";
				cout << "Num of electors: " << arr[0]->get_partyElectors() << "\n";
				cout << "The sum of votes: " << arr[0]->get_totalVotes() << "\n\n";
			}
			for (int i = 1; i < partyArr.size(); i++) {
				arr[i]->sumPartyVotes();
				cout << "ID: " << arr[i]->get_leaderID() << "\n";
				cout << "Num of electors: " << arr[i]->get_partyElectors() << "\n";
				cout << "The sum of votes: " << arr[i]->get_totalVotes() << "\n\n";

			}
		}
		else {
			DynamicArray<party*>arr;
			for (int j = 0; j < partyArr.size(); j++) {
				arr.push_back(partyArr[j]);
			}
			arr.pointersSort();
			cout << "\nThe votes at the country are : " << (static_cast<float>(totalVotes) / static_cast<float>(voterArrSize) * 100) << "%\n" << endl;
			for (int i = 0; i < partyArr.size(); i++) {
				cout << "Party: " << arr[i]->get_partyName() << "\n";
				cout << "Leader's ID: " << arr[i]->get_leaderID() << "\n";
				cout << "Number of electors: " << arr[i]->get_partyElectors() << "\n";
				cout << "Number of votes: " << arr[i]->get_totalVotes() << "\n";
				cout << "The party has: " << (static_cast<float>(arr[i]->get_totalVotes()) / static_cast<float>(totalVotes) * 100) << "% votes" << endl;
				if (arr[i]->get_memLogSize(0) > 0) {
					cout << "The Chosen electors are: \n";
					for (int j = 0; j < arr[i]->get_memLogSize(0); j++) {
						cout << (j + 1) << "." << arr[i]->get_province(0).get_memID(j) << endl;
					}
				}
				cout << endl;
			}
		}
	}
	void printDate              (const string& date)
	{
		cout << date << endl;
	}
}