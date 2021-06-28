#pragma once
#include "Party.h"



namespace elections {

	class province;

	class voter {
	private: 
	
		string     name;                           // the voter's name
		int        id;                             // holds the voter ID
		string     birthD;                         // holds birthday
		province*  provP = nullptr;                // a pointer to the province the voter lives in
		int        voteIndecator = 0;              // 0= hasnt voted yet, 1= otherwise
		int        votedParty = 0;                 // The party number the voter voted for

	public:
		voter (string _name   = "\0"        , int       _id    = 100000000,
			   string _birthD = "01.01.0101", province* _provP = nullptr );          //constructor
		~voter () {}                                                                //destructor
		voter  (const voter& other) { *this = other; }                             //copy constructor

		//getters
		const int        get_votedParty    ()const  { return votedParty   ; }
		const string     getName           ()const  { return name         ; }
		const int        get_id            ()const  { return id           ; }
		const string     get_birthD        ()const  { return birthD       ; }
		const province*  get_provP         ()const  { return provP        ; }
		const int        get_voteIndecator ()const  { return voteIndecator; }

		//setters:
		void set_votedParty   (const int       _partyNum);
		void set_Name         (const string    _name);
		void setID            (const int       _id);
		void set_BirthD       (const string    _birthD);
		void setVoteIndecator (const int       val);
		void set_provP        (province* const _provP);

		//checkers
		void isDateValid (const string date)const;
		void isIDValid   (const int id)const;

		//operators
		friend ostream&  operator<< (ostream& os, const voter& voter);
		const voter&     operator=  (const voter& other);

		//save & load
		void  save (ostream& out) const;
		void  load (istream& in);
	};
}
