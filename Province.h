#pragma once
#include "Voter.h"

namespace elections {

	class province {
	
	protected:
		DynamicArray<voter*> voterArr;                  //holds all voters that live at the province
		int                  totalVotes = 0;            //how many voted in this province
		string               name;                      //province name
		int                  num = 0;                   //province number
		int                  senNum = 0;                //the number of the presentors in the current province
		DynamicArray<party*> partyArr;                  //holds all partys that ran in the election

	public:
		province (string _name = "\0", int _senNum = 0);  	      //constructor
		virtual ~province() {}                                   //destructor
		province (const province& other) { *this = other; }     //copy constructor

	//getters
		const string  getName          ()const              { return name                ; }
		const int     getNum           ()const              { return num                 ; }
		const int     getSenNum        ()const              { return senNum              ; }
		const int     getVoterLogic    ()const              { return voterArr.size()     ; }
		const int     getPartyLogic    ()const              { return partyArr.size()     ; }
		const int     getVoterPhysical ()const              { return voterArr.capacity() ; }
		const int     getPartyPhysical ()const              { return partyArr.capacity() ; }
		const voter*  getVoter         (const int idx)const { return voterArr[idx]       ; }
		const int     get_totalVotes   ()const              { return totalVotes          ; }

		//setters
		void set_Name    (const string _name);
		void set_num     (const int _num);
		void set_senNum  (const int _senNum);

		//adders
		void addParty (party* const newParty);
		void addVoter (voter* const newVoter);
		void addVote  ();

		//operators
		virtual province const& operator=  (const province& other);
		virtual void            operator=  (const province* other) { *this = other; }
		friend ostream&         operator<< (ostream& os, const province& prov);
		virtual ostream&        Print      (ostream& os) const;

		//other methods:
		virtual void      chooseElectors ()const;
		virtual const int returnType     ()const;
		const float       returnPercent  ()const ;

		//save & load
		virtual void save (ostream& out)const;
		virtual void load (istream& in);
	};
}

