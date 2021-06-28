#pragma once
#include "Voter.h"


namespace elections
{
	//constructor
	voter:: voter(string _name, int _id, string _birthD, province* _provP)
	{
		isIDValid(_id);
		isDateValid(_birthD);
		name = _name;
		id = _id;
		birthD = _birthD;
		provP = _provP;
	}

	//setters:
	void voter:: set_votedParty   (int _partyNum)
	{
		if (_partyNum < 0)
			throw ALERT("Party number must be a positive number\n");
		votedParty = _partyNum;
	}
	void voter:: set_Name         (const string _name)
	{
		name = _name;
	}
	void voter:: setID            (const int _id)
	{
		if (_id <= 0)
			throw ALERT("ID must be a positive number\n");

		string ID = to_string(_id);
		if (ID.size() != 9)
			throw ALERT("ID must have exactly 9 digits\n");
		id = _id;
	}
	void voter:: set_BirthD       (const string _birthD)
	{
		if (_birthD.size() == 10) {
			for (int i = 0; i < _birthD.size(); i++) {
				if (i == 2 || i == 5) {
					if (_birthD[i] != '.' && _birthD[i] != '/')
						throw ALERT("Invalid date of birth, the only separators allowed are '.' or '/'\n");
				}
				else {
					if (!isdigit(_birthD[i]))
						throw ALERT("Invalid date of birth, year, month and days should contain only digits\n");
				}
			}
		}
		else throw ALERT("Invalid date of birth\n");
		birthD = _birthD;
	}
	void voter:: set_provP        (province* const _provP)
	{
		provP = _provP;
	}
	void voter:: setVoteIndecator (const int val)
	{
		if (val == 1 || val == 0) 
			voteIndecator = val;
	}

	//checkers
	void voter:: isDateValid(const string date)const
	{
		if (date.size() == 10) {
			for (int i = 0; i < date.size(); i++) {
				if (i == 2 || i == 5) {
					if (date[i] != '.' && date[i] != '/')
						throw ALERT("Invalid date, the only separators allowed are '.' or '/'\n");
				}
				else {
					if (!isdigit(date[i]))
						throw ALERT("Invalid date, year, month and days should contain only digits\n");
				}
			}
		}
		else throw ALERT("Invalid date\n");

		int days = stoi(date.substr(0, 2));
		int month = stoi(date.substr(3, 2));
		int year = stoi(date.substr(6, 4));

		if (year <= 0)
			throw ALERT("Invalid date, year must be a positive number\n");
		if (month <= 0 && month > 12)
			throw ALERT("Invalid date, month must be a number from 1 to 12\n");

		int i, j;
		for (i = JANUARY, j = 1; i <= DECEMBER; i++, j++) {
			if (j == month)
				if (days > i && days < 1)
					throw ALERT("Invalid date, the 'day' input is out of the range of days in this month\n");
		}
	}
	void voter::isIDValid(const int id)const
	{
		if (id <= 0)
			throw ALERT("ID must be a positive number\n");

		string ID = to_string(id);
		if (ID.size() != 9)
			throw ALERT("ID must have exactly 9 digits\n");
	}

	//operators
	ostream&             operator<< (ostream& os, const voter& voter)
	{
		os << "voter's id:" << voter.get_id() << "\n"  //print the voter ID number
			<< "voter's name:" << voter.getName() << "\n"  //print the voter name number
			<< "voter's date of birth:" << voter.get_birthD() << "\n";  //print the voter birth date 
		return os;
	};
	const voter& voter:: operator=  (const voter& other)
	{
		if (this != &other)
		{
			name = other.name;
			id = other.id;
			birthD = other.birthD;
			provP = other.provP;
			voteIndecator = other.voteIndecator;
			votedParty = other.votedParty;
		}
		return *this;
	}

	//save & load
	void voter:: save(ostream& out)const
	{
		int size = static_cast<int>(name.size());                   //get size of string
		out.write(rcastcc(&size), sizeof(int));
		out.write(rcastcc(&name[0]), size);

		if (!out.good()) throw ALERT("Error while writing file\n");

		out.write(rcastcc(&id), sizeof(id));
		size = static_cast<int>(birthD.size());                     //get size of string
		out.write(rcastcc(&size), sizeof(int));
		out.write(rcastcc(&birthD[0]), size);

		if (!out.good()) throw ALERT("Error while writing file\n");

		out.write(rcastcc(&voteIndecator), sizeof(int));
		out.write(rcastcc(&votedParty), sizeof(int));
	}
	void voter:: load(istream& in)
	{
		int size = 0;
		in.read(rcastc(&size), sizeof(size));                      //get size of string
		name.resize(size);                                         //dynamic allocate string
		in.read(rcastc(&name[0]), size);

		if (!in.good()) throw ALERT("Error while reading file\n");

		in.read(rcastc(&id), sizeof(id));
		in.read(rcastc(&size), sizeof(size));                      //get size of string
		birthD.resize(size);                                       //dynamic allocate string
		in.read(rcastc(&birthD[0]), size);

		if (!in.good()) throw ALERT("Error while reading file\n");

		in.read(rcastc(&voteIndecator), sizeof(int));
		in.read(rcastc(&votedParty), sizeof(int));

		if (!in.good()) throw ALERT("Error while reading file\n");
	}
}