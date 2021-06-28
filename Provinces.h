#pragma once
#include "dynamicArrTemplate.h"

namespace elections {

	class provinces {
	private:
		string             name;                             //The name of the represented province
		int                provNum = 0;                      //holds the number of the represented province
		float              perecent = 0;                     //holds vote precentage in province specifically to the party that contain the class
		int                electorsSelected = 0;             //number of selected electors to the party in this province
		int                voteNumbers = 0;                  //The number of votes for this party in this province
		DynamicArray<int>  memArr;                           //holds all the members of the party in this province

	public:
		provinces (string _name = "\0", int _provNum = 0);             //constructor
		~provinces() {}                                               //destructor
		provinces (const provinces& other) { *this = other; }        //copy construct

		//getters
		const string  get_name             ()const               { return name             ; }
		const int     get_provNum          ()const               { return provNum          ; }
		const float   get_perecent         ()const               { return perecent         ; }
		const int     get_electorsSelected ()const               { return electorsSelected ; }
		const int     get_voteNumbers      ()const               { return voteNumbers      ; }
		const int     get_memPhySize       ()const               { return memArr.capacity(); }
		const int     get_memLogSize       ()const               { return memArr.size()    ; }
		const int     get_memID            (const int idx)const  { return memArr[idx]      ; }

		//setters
		void set_Name              (const string _name);
		void set_provNum           (const int num);
		void set_electorsSelected  (const int val);
		void add_elector           (const int val);
		void set_voteNumbers       (const int votes);
		void set_precet            (const int provinceVotes);
		void addToTail             (const int _id);
		void add_vote              (const int val);

		//operators
		const provinces& operator=(const provinces& other);

		//save & load
		void save(ostream& out)const;
		void load(istream& in);
	};
}
