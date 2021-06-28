#pragma once
#include "Provinces.h"

using namespace std;

namespace elections {

	class party {
		
	private:
		int                       num = 0;                    //party number
		int                       electors = 0;               //will be used for the result option
		int                       totalVotes = 0;             //holds all votes for this party
		string                    partyName;                  //the party's name
		int                       leaderID = 0;               //the party leader ID
		DynamicArray<provinces*>  arr;                        //array of structs that holds all provinces int he country

	public:
		party  (string _partyName = "\0", int _leaderID = 100000000);        //constructor
		~party () {}                                                        //destructor
		party  (const party& other) { *this = other; }                     //copy constructor

		//Getters:
		const int       get_partyNum       ()const                   { return num                        ; }
		const int       get_partyElectors  ()const                   { return electors                   ; }
		const int       get_totalVotes     ()const                   { return totalVotes                 ; }
		const string    get_partyName      ()const                   { return partyName                  ; }
		const int       get_leaderID       ()const                   { return leaderID                   ; }
		const int       get_logicSize      ()const                   { return arr.size()                 ; }
		const int       get_physicSize     ()const                   { return arr.capacity()             ; }
		const int       get_memLogSize     (const int idx)const      { return arr[idx]->get_memLogSize() ; }
		const int       get_memPhySize     (const int idx)const      { return arr[idx]->get_memPhySize() ; }
		provinces&      get_province       (const int idx)const      { return *arr[idx]                  ; }
		template <class T>
		DynamicArray<T> get_memArr         (const int provIdx)const  { return arr[provIdx].memArr        ; }
		const int       get_ProvinceArrIdx (const int provNum)const;

		//Setters:
		void set_precet     (const int    provinceVotes);
		void set_partyNum   (const int    _num);
		void set_totalVotes (const int    _totalVotes);
		void set_partyName  (const string _name);
		void set_leaderID   (const int    _leaderID);
		void set_electors   (const int    _electors);
		void resetElectors  ();

		//adders
		void addProvice           (const string name, const int num);
		void addProviceTotalVote  (const int val, const int idx);
		void addTotalVote         (const int val);
		void addElectorsToTotal   (const int val);

		//checkers
		void isIDValid (const int id)const;

		//other Methods
		void sumPartyVotes ();

		//operators
		friend ostream& operator<<  (ostream& os, party const& party);
		const party&    operator=   (const party& other);
		bool            operator<   (const party& other);
		bool            operator>   (const party& other);
		bool            operator==  (const party& other);

		//save & load
		void save (ostream& out)const;
		void load (istream& in);
	};
}

