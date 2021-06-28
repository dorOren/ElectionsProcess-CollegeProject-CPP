#pragma once
#include "simpleElections.h"

namespace elections
{
	class MainMenu
	{
	public:
		enum eMiniMenu
		{
			StartNewElection = 1,
			LOAD,
			QUIT
		};

		enum  eMenu
		{
			AddaNewProvince = 1,
			AddaNewVoter,
			AddaNewParty,
			MakeVoterPartyMember,
			PrintAllProvinces,
			PrintAllVoters,
			PrintAllPartys,
			InsertVote,
			ShowElectionResults,
			Exit,
			Save,
			Load
		};

		//menus interfaces
		void show_Mini_Menu();
		void show_Menu(election* elect, string date, bool electionType);
		void print_Menu();
		void print_Mini_Menu();

		//handle user's mini menu choices
		void StartNewElection_(election*& elect, bool& electionType, string& date, bool& valid);
		void Load_(election*& elect, string& date, bool& valid);

		//handle user's menu choices
		void AddaNewProvince_(election*& elect, bool electionType);
		void AddaNewVoter_(election*& elect, bool electionType);
		void AddaNewParty_(election*& elect);
		void MakeVoterPartyMember_(election*& elect);
		void InsertVote_(election*& elect, bool electionType);
		void ShowElectionResults_(election*& elect);
		void Save_(election*& elect);
		void Load_(election*& elect, string& date);

	};
}

