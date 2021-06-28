#include "simpleElections.h"

namespace elections
{
	//constructor
	simpleElections:: simpleElections (string _date, int _senNum) : election(_date)
	{
		if (_senNum < 0)
			throw ALERT("Number of delegators must be a positive number\n");

		senNum = _senNum;
	}

	//adders
	void simpleElections:: addParty          (const string name, const int leaderID)  //add a party to partys array
	{
		isPartyValid(name, leaderID);                                //if the party is invalid this function throws an exception
		party* a;
		try { a = new party(name, leaderID); } CHECK_BAD_ALLOC
		a->addProvice("country", 0);
		a->set_partyNum(givePartyANumber());
		partyArr.push_back(a);
	}
	void simpleElections:: addNewPartyMember (const int ID, const int partyNumber, const int provinceNum) {
		for (int i = 0; i < partyArr.size(); i++) {
			if (partyNumber == partyArr[i]->get_partyNum())
				partyArr[i]->get_province(0).addToTail(ID);
		}
	}

	//print methodes
	void simpleElections:: printAllProvinces ()const {
		cout << "There are are no provinces" << endl;
	}
	void simpleElections:: printAllVoters    ()const {  //printing all the voters inside the election voter array
		for (int i = 0; i < voterArr.size(); i++) {
			cout << *voterArr[i];
			cout << "\n";
		}

	}
	void simpleElections:: printAllPartys    ()const {
		for (int i = 0; i < partyArr.size(); i++) {
			cout << "\nparty's number:" << partyArr[i]->get_partyNum() << "\n"
				<< "party's name:" << partyArr[i]->get_partyName() << "\n"
				<< "ID of party's leader:" << partyArr[i]->get_leaderID() << "\n";
			if (partyArr[i]->get_logicSize() > 0) {                   //if there is at least 1 ID to print
				cout << "The members of the party are: \n";
				for (int j = 0; j < partyArr[i]->get_memLogSize(0); j++)
					cout << j + 1 << ". " << partyArr[i]->get_province(0).get_memID(j) << endl;
			}
		}
	};

	//Result methods
	void simpleElections:: whatsTheResult        ()const
	{
		printDate(date);
		updatePartyPercentage();
		chooseElectors();
		printTheResult(partyArr, 1, totalVotes, voterArr.size());
	}
	void simpleElections:: chooseElectors        ()const {
		DynamicArray<float>tempArr;    //create array that will hold the data
		for (int i = 0; i < partyArr.size(); i++)
			partyArr[i]->resetElectors();

		int index = 0;
		float biggest = 0.00f;
		int totalElectors = senNum;
		for (int i = 0; i < partyArr.size(); i++) {
			tempArr.push_back(static_cast<float>(((partyArr[i]->get_province(0).get_perecent()) * static_cast<float>(senNum) / 100)));
			partyArr[i]->addElectorsToTotal(static_cast<int>(tempArr[i]));//will put the lower value of the if its 7.6 it wil put 7
			totalElectors -= static_cast<int>(tempArr[i]);
			tempArr[i] -= static_cast<int>(tempArr[i]);
		}
		while (totalElectors > 0) {
			biggest = 0.00f;
			index = 0;
			for (int j = 0; j < partyArr.size(); j++) {
				if (tempArr[j] > biggest) {
					biggest = tempArr[j];
					index = j;
				}
			}
			partyArr[index]->addElectorsToTotal(1);
			tempArr[index] -= 1;
			totalElectors -= 1;
		}
	}
	void simpleElections:: updatePartyPercentage ()const {

		for (int i = 0; i < partyArr.size(); i++)
			partyArr[i]->set_precet(totalVotes);
	}

	//operators
	const simpleElections& simpleElections:: operator= (const simpleElections& other) {
		if (this != &other)
		{
			election::operator=(other);
			senNum = other.senNum;
		}
		return *this;
	}

	//save & load
	void simpleElections:: save (ostream& out)const
	{
		//save country
		int type = 1;
		out.write(rcastcc(&type), sizeof(int));
		int size = static_cast<int>(date.size());                                           //get size of string
		out.write(rcastcc(&size), sizeof(int));
		out.write(rcastcc(&date[0]), size);
		out.write(rcastcc(&senNum), sizeof(int));
		out.write(rcastcc(&totalVotes), sizeof(int));
		if (!out.good()) throw ALERT("Error while writing file\n");

		//save voters
		size = voterArr.size();
		out.write(rcastcc(&size), sizeof(int));                           //write sizes of voterArr
		for (int i = 0; i < size; i++)                                    //write all voters
			voterArr[i]->save(out);
		if (!out.good()) throw ALERT("Error while writing file\n");

		//save partys
		size = partyArr.size();
		out.write(rcastcc(&size), sizeof(int));                           //write sizes of partyArr
		for (int i = 0; i < size; i++)                                    //write all parties
			partyArr[i]->save(out);
		if (!out.good()) throw ALERT("Error while writing file\n");
	}
	void simpleElections:: load       (istream& in)
	{
		//load country
		int size;
		in.read(rcastc(&totalVotes), sizeof(int));
		if (!in.good()) throw ALERT("Error while reading file\n");

		//load voters
		in.read(rcastc(&size), sizeof(int));                               //get sizes of voterArr
		for (int i = 0; i < size; i++) {                                   //load all voters
			voter* a;
			try { a = new voter; } CHECK_BAD_ALLOC
			a->load(in);
			voterArr.push_back(a);
		}
		if (!in.good()) throw ALERT("Error while reading file\n");

		//load partys
		in.read(rcastc(&size), sizeof(int));                               //get sizes of partyArr
		for (int i = 0; i < size; i++) {                                   //load all parties
			party* a;
			try { a = new party; } CHECK_BAD_ALLOC
			a->load(in);
			partyArr.push_back(a);
		}
		if (!in.good()) throw ALERT("Error while reading file\n");
	}
}