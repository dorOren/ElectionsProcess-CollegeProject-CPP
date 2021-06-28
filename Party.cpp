#include "Party.h"

namespace elections
{
	//constructor
	party:: party(string _partyName, int _leaderID)
	{
		isIDValid(_leaderID);
		partyName = _partyName;
		leaderID = _leaderID;
	}

	//setters
	void party:: set_partyName  (const string _name)
	{
		partyName = _name;
	}
	void party:: set_precet     (const int provinceVotes)    
	{
		if (totalVotes <= 0 && arr.size() > 0) {
			arr[0]->set_precet(0);
		}
		else if (totalVotes > 0 && arr.size() > 0) {
			arr[0]->set_precet(provinceVotes);
		}
		return;
	}
	void party:: set_partyNum   (const int _num)
	{
		if (_num < 0)
			throw ALERT("Party number must be a positive number\n");
		num = _num;
	}
	void party:: set_leaderID   (const int _leaderID)
	{
		if (_leaderID <= 0)
			throw ALERT("ID must be a positive number\n");

		string ID = to_string(_leaderID);
		if (ID.size() != 9)
			throw ALERT("ID must have exactly 9 digits\n");
		leaderID = _leaderID;
	}
	void party:: set_totalVotes (const int _totalVotes)
	{
		if (_totalVotes < 0)
			throw ALERT("Total votes must be a positive number\n");
		totalVotes = _totalVotes;
	}
	void party:: set_electors   (const int _electors)
	{
		if (_electors < 0)
			throw ALERT("Number of electors must be a positive number\n");
		electors = _electors;
	}
	void party:: resetElectors  ()
	{
		electors = 0;
		for (int i = 0; i < arr.size(); i++)
			arr[i]->set_electorsSelected(0);
	}

	//Getters
	const int party:: get_ProvinceArrIdx (const int provNum)const {
		for (int i = 0; i < arr.size(); i++) {
			if (arr[i]->get_provNum() == provNum)
				return i;
		}
		return 0;
	}

	//adders
	void party:: addProviceTotalVote (const int val, const int idx)
	{
		if (val < 0)
			throw ALERT("Number of votes must be a positive number\n");
		if (idx<0 || idx>=arr.size())
			throw ALERT("Invalid index- out of array's range\n");
		arr[idx]->set_voteNumbers(arr[idx]->get_voteNumbers() + val);
		totalVotes += 1;
	}
	void party:: addProvice          (const string name, const int num)
	{
		provinces* newprovinces;
		try { newprovinces = new provinces(name, num); } CHECK_BAD_ALLOC
		arr.push_back(newprovinces);
	}
	void party:: addTotalVote        (const int val)
	{
		if (val < 0)
			throw ALERT("Number of votes must be a positive number\n");
		totalVotes += val;
	}
	void party:: addElectorsToTotal  (const int val)
	{
		if (val < 0)
			throw ALERT("Number of electors must be a positive number\n");
		electors += val;
	}

	//checkers
	void party:: isIDValid (const int id)const
	{
		if (id <= 0)
			throw ALERT("ID must be a positive number\n");

		string ID = to_string(id);
		if (ID.size() != 9)
			throw ALERT("ID must have exactly 9 digits\n");
	}

	//other methods
	void party:: sumPartyVotes (){
		totalVotes = 0;
		for (int i = 0; i < arr.size(); i++) 
			totalVotes += arr[i]->get_voteNumbers();
	}

	//operators
	ostream&             operator<< (ostream& os, const party& party) {
		{
			os << "party's number:" << party.num << "\n"
				<< "party's name:" << party.partyName << "\n"
				<< "ID of party's leader:" << party.leaderID << "\n";
			for (int i = 0; i < party.arr.size(); i++) {
				os << "The members of the party in province " << party.arr[i]->get_name().c_str() << " are:\n";
				for (int j = 0; j < party.arr[i]->get_memLogSize(); j++)
					os << j + 1 << ". " << party.arr[i]->get_memID(j) << "\n";
			}
			return os;
		};
	}
	const party& party:: operator=  (const party& other)
	{
		if (this != &other)
		{
			num = other.num;
			partyName = other.partyName;
			electors = other.electors;
			totalVotes = other.totalVotes;
			leaderID = other.leaderID;
			arr = other.arr;
		}
		return *this;
	}
	bool         party:: operator<  (const party& other) {
		if (this->electors < other.electors)
			return true;
		else
			return false;
	}
	bool         party:: operator>  (const party& other) {
		if (this->electors > other.electors)
			return true;
		else
			return false;
	}
	bool         party:: operator== (const party& other) {
		if (this->num == other.num)
			return true;
		return false;
	}

	//save & load
	void party:: save (ostream& out)const
	{
		out.write(rcastcc(&num), sizeof(int));
		out.write(rcastcc(&electors), sizeof(int));
		out.write(rcastcc(&totalVotes), sizeof(int));
		int size = static_cast<int>(partyName.size());

		out.write(rcastcc(&size), sizeof(int));
		out.write(rcastcc(&partyName[0]), size);
		out.write(rcastcc(&leaderID), sizeof(int));

		if (!out.good()) throw ALERT("Error while writing file\n");

		size = arr.size();
		out.write(rcastcc(&size), sizeof(size));
		if (size > 0) {
			for (int i = 0; i < size; i++)   //writing struct "provinces" array
				arr[i]->save(out);
			if (!out.good()) throw ALERT("Error while writing file\n");
		}
	}
	void party:: load (istream& in)
	{
		int size;
		in.read(rcastc(&num), sizeof(int));
		in.read(rcastc(&electors), sizeof(int));
		in.read(rcastc(&totalVotes), sizeof(int));
		in.read(rcastc(&size), sizeof(size));
		partyName.resize(size);
		in.read(rcastc(&partyName[0]), size);
		in.read(rcastc(&leaderID), sizeof(leaderID));

		if (!in.good()) throw ALERT("Error while reading file\n");

		in.read(rcastc(&size), sizeof(size));
		if (size > 0) {
			for (int i = 0; i < size; i++) {   //writing struct "provinces" array
				provinces* a;
				try { a = new provinces; } CHECK_BAD_ALLOC
				a->load(in);
				arr.push_back(a);
			}
		}
		if (!in.good()) throw ALERT("Error while reading file\n");
	}
}