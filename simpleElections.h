#pragma once
#include "Elections.h"

namespace elections {

	class simpleElections :virtual public election{

	private:
		int senNum;                   //number of electors in the country
	public:
		simpleElections (string _date = "01.01.0101", int _senNum = 0);  	        //constructor
		virtual ~simpleElections() {}                                              //destructor
		simpleElections (const simpleElections& other) { *this = other; }         //copy constructor

		//adders
		virtual void addParty          (const string name, const int leaderID);
		virtual void addNewPartyMember (const int ID, const int partyNumber, const int provinceNum = 0);

		//print methods
		virtual void printAllProvinces ()const override;
		virtual void printAllPartys    ()const override;
		virtual void printAllVoters    ()const override;

		//result methods
		virtual void whatsTheResult        ()const override;
		virtual void chooseElectors        ()const override;
		virtual void updatePartyPercentage ()const override;

		//operators
		virtual const simpleElections& operator= (const simpleElections& other);

		//save & load
		virtual void save (ostream& out)const;
		virtual void load (istream& in);
	};
}
