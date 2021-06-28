#include "Provinces.h"

namespace elections
{
	//constructor
	provinces:: provinces (string _name, int _provNum)
	{
		if (_provNum < 0)
			throw ALERT("Province number must be a positive number\n");

		name = _name;
		provNum = _provNum;
	}

	//setters
	void provinces:: set_Name             (const string _name)
	{
	    name = _name;
	}
	void provinces:: set_provNum          (const int num)
	{
		if (num < 0)
			throw ALERT("Province number must be a positive number\n");
		provNum = num;
	}
	void provinces:: set_electorsSelected (const int val)
	{
		if (val < 0)
			throw ALERT("Number of electors must be a positive number\n");
		electorsSelected = val;
	}
	void provinces:: set_voteNumbers      (const int votes)
	{
		if (votes < 0)
			throw ALERT("Total votes must be a positive number\n");
		voteNumbers = votes;
	}
	void provinces:: add_vote             (const int val)
	{
		if (val < 0)
			throw ALERT("Number of votes must be a positive number\n");
		voteNumbers += val;
	}
	void provinces:: addToTail            (const int _id)
	{
		if (_id <= 0)
			throw ALERT("ID must be a positive number\n");

		string ID = to_string(_id);
		if (ID.size() != 9)
			throw ALERT("ID must have exactly 9 digits\n");

		memArr.push_back(_id);
	}
	void provinces::set_precet(const int provinceVotes)
	{
		if (provinceVotes == 0)
			throw ALERT("Devision by zero\n");
		else if (provinceVotes < 0)
			throw ALERT("Number of province votes must be a positive number\n");
		else if (provinceVotes < voteNumbers)
			throw ALERT("Percentage of votes can't be greater than 100\n");
		else
			perecent = (static_cast<float>(voteNumbers) / static_cast<float>(provinceVotes)) * 100;
	}
	void provinces:: add_elector          (const int val)
	{
		if (val < 0)
			throw ALERT("Number of electors must be a positive number\n");
		electorsSelected += val;
	}

	//operators
	const provinces& provinces:: operator= (const provinces& other)
	{
		if (this != &other)
		{
			name = other.name;
			provNum = other.provNum;
			perecent = other.perecent;
			electorsSelected = other.electorsSelected;
			voteNumbers = other.voteNumbers;
			memArr = other.memArr;
		}
		return *this;
	}

	//save & load
	void provinces:: save (ostream& out) const {
		int size = static_cast<int>(name.size());
		out.write(rcastcc(&size), sizeof(int));
		out << name.c_str();
		out.write(rcastcc(&provNum), sizeof(int));
		out.write(rcastcc(&perecent), sizeof(float));
		out.write(rcastcc(&electorsSelected), sizeof(int));
		out.write(rcastcc(&voteNumbers), sizeof(int));
		size = memArr.size();
		out.write(rcastcc(&size), sizeof(int));
		for (int i = 0; i < memArr.size(); i++) {
			out.write(rcastcc(&memArr[i]), sizeof(int));
		}
		if (!out.good()) throw ALERT("Error while writing file\n");
	}
	void provinces:: load (istream& in)
	{
		int nameLen, size, ID;
		in.read(rcastc(&nameLen), sizeof(int));
		name.resize(nameLen);
		in.read(rcastc(&name[0]), nameLen);
		in.read(rcastc(&provNum), sizeof(int));
		in.read(rcastc(&perecent), sizeof(float));
		in.read(rcastc(&electorsSelected), sizeof(int));
		in.read(rcastc(&voteNumbers), sizeof(int));
		in.read(rcastc(&size), sizeof(int));
		for (int i = 0; i < size; i++) {
			in.read(rcastc(&ID), sizeof(int));
			memArr.push_back(ID);
		}
		if (!in.good()) throw ALERT("Error while reading file\n");
	}
}