#pragma once
#include "ElectionsResult.h"

namespace elections {

	class election {

	private:
		DynamicArray < province*> provArr;                   //holds all provinces

	protected:
		string                    date;                      //date of election
		int                       totalVotes = 0;            //how many voted in the entire election process
		DynamicArray<voter*>      voterArr;                  //holds all voters
		DynamicArray < party*>    partyArr;                  //holds all participating parties

	public:
		election (string _date = "01.01.0101");                        //constructor
		virtual ~election();                                          //destructor
		election (const election& other) { *this = other; }          //copy constructor

		//setters:
		void set_Date (const string _date);

		//getters:
		const int       get_provArrPhysic  ()const               { return provArr.capacity() ; }
		const int       get_partyLogicSize ()const               { return partyArr.size()    ; }
		const int       get_voterLogicSize ()const               { return voterArr.size()    ; }
		const int       get_provArrLogic   ()const               { return provArr.size()     ; }
		const party*    getPartyCell       (const int idx)const  { return partyArr[idx]      ; }
		const province* get_provCell       (const int idx)const  { return provArr[idx]       ; }
		const voter*    get_voterCell      (const int idx)const  { return voterArr[idx]      ; }

		//ProvinceArr
		virtual void       addProvince          (const string name, const int senNum, const bool isseperated);
		virtual void       printAllProvinces    ()const;
		virtual const int  giveProvinceANumber  ()const;

		//VoterArr
		virtual void printAllVoters    ()const;
		void         addVoter          (const string name, const int id, const string birthD, const int provNum, const bool electionType);
		const int    returnVoterIndex  (const int id)const;

		//PartyArr
		virtual void        addNewPartyMember  (const int ID, const int partyNumber, const int provinceNum);
		virtual void        addParty           (const string name, const int leaderID);
		virtual void        printAllPartys     ()const;
		virtual const int   givePartyANumber   ()const;

		//checkers
		void       isVoterValidToJoinParty  (const int id, const int partyNum, const int provinceNum, const bool electionType)const;
		void       isPartyValid             (const string name, const int leaderID)const;
		void       isVoterValid             (const int id, const int provNum, const bool electionType, const string date, const string birthD)const;
		void       isProvinceValid          (const string name)const;
		void       isOver18                 (const string date, const string birthD)const;
		const int  calcDateInDays           (const string date)const;
		void       isTheVoteValid           (const int partyNum, const int voterID);
		void       isDateValid              (const string date)const;

		//vote process methods
		void addVote (const int partyNum, const int voterID, const bool electionType);

	    //Result methods
		virtual void whatsTheResult        ()const;
		virtual void chooseElectors        ()const;
		virtual void updatePartyPercentage ()const;

		//operators
		virtual const election& operator= (const election& other);

		//save & load
		virtual void save (ostream& out)const;
		virtual void load (istream& in);
		virtual void syncProvinceData();
	};
}
