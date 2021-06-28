#include "Province.h"

namespace elections
{
	//constructor
	province:: province(string _name, int _senNum)
	{
		if (_senNum < 0)
			throw ALERT("Number of delegators must be a positive number\n");

		name = _name;
		senNum = _senNum;
	}

	//setters
	void province:: set_Name    (const string _name)
	{ 
		name = _name;
	}
	void province:: set_num     (const int _num) 
	{
		if (_num < 0)
			throw ALERT("Province number must be a positive number\n");
		num = _num;
	}
	void province:: set_senNum  (const int _senNum) 
	{
		if (_senNum < 0)
			throw ALERT("Number of delegators must be a positive number\n");
		senNum = _senNum;
	}

	//adders
	void province:: addVote   ()
	{
		totalVotes += 1;
	};
	void province:: addVoter  (voter* const newVoter)
	{
		voterArr.push_back(newVoter);
	}
	void province:: addParty  (party* const newParty)
	{
		partyArr.push_back(newParty);
	}

	//operators
	province const& province::  operator=   (province const& other)
	{
		if (this != &other)
		{
			name = other.name;
			num = other.num;
			senNum = other.senNum;
			totalVotes = other.totalVotes;
			voterArr = other.voterArr;
			partyArr = other.partyArr;
		}
		return *this;
	}
	ostream&                    operator<<  (ostream& os, const province& prov)
	{
		return prov.Print(os);
	}
	ostream&        province::  Print       (ostream& os) const {

		cout << "Provinces's number:" << num << "\n"
			<< "Provinces's name:" << name.c_str() << "\n"
			<< "Number of delegates:" << senNum << "\n"
			<< "This is a normal province." << "\n";
		return os;

	}

	//other methods:
	const float province:: returnPercent  ()const
	{
		if (voterArr.size() == 0)
			throw ALERT("Devision by zero\n");
		else if (totalVotes < 0)
			throw ALERT("Number of province votes must be a positive number\n");
		else if (voterArr.size() < totalVotes)
			throw ALERT("Percentage of votes can't be greater than 100\n");
		else
			return  (static_cast<float>(totalVotes) / static_cast<float>(voterArr.size()) * 100);
	}
	void        province:: chooseElectors ()const {
		int totalElectors = senNum;
		DynamicArray<float>tempArr;
		int index = num;
		int index1 = 0;
		float biggest = 0;

		for (int i = 0; i < partyArr.size(); i++) {
			tempArr.push_back(partyArr[i]->get_province(index).get_perecent() * static_cast<float>(senNum) / 100);
			partyArr[i]->get_province(index).set_electorsSelected(static_cast<int>(tempArr[i]));  //will put the lower value of the if its 7.6 it wil put 7
			if (tempArr[i] > biggest) {
				biggest = tempArr[i];
				index1 = i;
			}
			totalElectors -= static_cast<int>(tempArr[i]);
			tempArr[i] -= static_cast<int>(tempArr[i]);
		}
		partyArr[index1]->addElectorsToTotal(senNum);
		while (totalElectors > 0)
		{
			biggest = 0;
			index1 = 0;
			for (int j = 0; j < partyArr.size(); j++) {
				if (static_cast<float>(tempArr[j]) > biggest) {
					biggest = tempArr[j];
					index1 = j;
				}
			}
			partyArr[index]->get_province(index1).add_elector(1);

			tempArr[index1] -= 1;
			totalElectors -= 1;
		}
	}
	const int   province:: returnType     ()const { return 0; }

	//save & load
	 void province:: save(ostream& out)const
	 {
		 out.write(rcastcc(&totalVotes), sizeof(int));
		 out.write(rcastcc(&num), sizeof(int));
		 out.write(rcastcc(&senNum), sizeof(int));

		 if (!out.good()) throw ALERT("Error while writing file\n");

		 int size = static_cast<int>(name.size());                                                        //get size of string
		 out.write(rcastcc(&size), sizeof(size));                                       //write size to make loading easier
		 out.write(rcastcc(&name[0]), size);
		 if (!out.good()) throw ALERT("Error while writing file\n");
	 }
	 void province:: load(istream& in)
	 {
		 in.read(rcastc(&totalVotes), sizeof(int));
		 in.read(rcastc(&num), sizeof(int));
		 in.read(rcastc(&senNum), sizeof(int));

		 if (!in.good()) throw ALERT("Error while reading file\n");

		 int size = 0;
		 in.read(rcastc(&size), sizeof(int));                                           //get size of string
		 in.read(rcastc(&name[0]), size);
		 if (!in.good()) throw ALERT("Error while reading file\n");
	 }
}
