#include "SeperatedProvince.h"

namespace elections
{
	//constructor
	SeperatedProvince:: SeperatedProvince (string _name, int _senNum) : province(_name, _senNum) {}

	//other methods
	const int  SeperatedProvince:: returnType      ()const { return 1; }
	void       SeperatedProvince:: chooseElectors  ()const {
		int totalElectors = senNum;
		DynamicArray<float>tempArr;
		int index = partyArr[0]->get_ProvinceArrIdx(num);
		int index1 = 0;
		float biggest = 0;
		for (int i = 0; i < partyArr.size(); i++) {
			if (partyArr[i]->get_province(index).get_voteNumbers() > 0) {     //no point to check if there are no 
				tempArr.push_back(partyArr[i]->get_province(index).get_perecent() * totalElectors / 100);
				partyArr[i]->addElectorsToTotal(static_cast<int>(tempArr[i]));    //will put the lower value of the if its 7.6 it wil put 7
			}
			if (tempArr[i] > biggest) {
				biggest = tempArr[i];
				index1 = i;
			}
			totalElectors -= static_cast<int>(tempArr[i]);
			tempArr[i] -= static_cast<int>(tempArr[i]);

		}
		while (totalElectors > 0) {
			biggest = 0;
			index1 = 0;
			for (int j = 0; j < partyArr.size(); j++) {
				if (tempArr[j] > biggest) {
					biggest = tempArr[j];
					index1 = j;
				}
			}
			partyArr[index1]->addElectorsToTotal(1);
			tempArr[index1] -= 1;
			totalElectors -= 1;
		}
	}

	//operators
	SeperatedProvince const& SeperatedProvince:: operator= (SeperatedProvince const& other)
	{
		if (this != &other)
			province::operator=(other);
		return *this;
	}
	ostream&                 SeperatedProvince:: Print     (ostream& os) const
	{
		cout << "Provinces's number:" << num << "\n"
			<< "Provinces's name:" << name << "\n"
			<< "Number of delegates:" << senNum << "\n"
			<< "This is a seperated province." << "\n";
		return os;
	}

	//save & load
	void SeperatedProvince:: save (ostream& out)const
	{
		out.write(rcastcc(&totalVotes), sizeof(int));
		out.write(rcastcc(&num), sizeof(int));
		out.write(rcastcc(&senNum), sizeof(int));

		if (!out.good()) throw ALERT("Error while writing file\n");

		int size = static_cast<int>(name.size());   //get size of string
		out.write(rcastcc(&size), sizeof(int));   //write size to make loading easier
		out.write(rcastcc(&name[0]), size);

		if (!out.good()) throw ALERT("Error while writing file\n");
	}
	void SeperatedProvince:: load (istream& in)
	{
		in.read(rcastc(&totalVotes), sizeof(int));
		in.read(rcastc(&num), sizeof(int));
		in.read(rcastc(&(senNum)), sizeof(int));

		if (!in.good()) throw ALERT("Error while reading file\n");

		int size;
		in.read(rcastc(&size), sizeof(int));   //get size of string
		name.resize(size);
		in.read(rcastc(&name[0]), size);

		if (!in.good()) throw ALERT("Error while reading file\n");
	}
}