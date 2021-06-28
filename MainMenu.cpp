#include "MainMenu.h"
#include <thread>

namespace elections
{
	int inputA = 0, inputB = 0, inputC = 0, type = 5;
	string buffer1, buffer2;
	bool isseperated = 0, valid = false;

	void MainMenu::show_Mini_Menu()
	{
		bool electionType = 0;                                     //0=normal, 1=simple;
		bool valid = false;
		int optionChosen = 0;
		string date;
		election* elect = nullptr;

		while (!valid) {
			std::this_thread::sleep_for(1000ms);
			system("CLS");
			print_Mini_Menu();
			cin >> optionChosen;
			if (optionChosen == StartNewElection)
				StartNewElection_(elect, electionType, date, valid);

			else if (optionChosen == LOAD)
				Load_(elect, date, valid);

			else if (optionChosen == QUIT)
				exit(1);

			else valid = false;
		}
		show_Menu(elect, date, electionType);
	}

	void MainMenu::show_Menu(election* elect, string date, bool electionType)
	{
		int optionChosen = 0;

		if (elect != nullptr) {
			while (optionChosen != Exit) {
				std::this_thread::sleep_for(1000ms);
				system("CLS");
				print_Menu();
				cin >> optionChosen;

				if (optionChosen == AddaNewProvince)
					AddaNewProvince_(elect, electionType);

				else if (optionChosen == AddaNewVoter)
					AddaNewVoter_(elect, electionType);

				else if (optionChosen == AddaNewParty)
					AddaNewParty_(elect);

				else if (optionChosen == MakeVoterPartyMember)
					MakeVoterPartyMember_(elect);

				else if (optionChosen == PrintAllProvinces)
					elect->printAllProvinces();

				else if (optionChosen == PrintAllVoters)
					elect->printAllVoters();

				else if (optionChosen == PrintAllPartys)
					elect->printAllPartys();

				else if (optionChosen == InsertVote)
					InsertVote_(elect, electionType);

				else if (optionChosen == ShowElectionResults)
					ShowElectionResults_(elect);

				else if (optionChosen == Exit)
					delete elect;

				else if (optionChosen == Save)
					Save_(elect);

				else if (optionChosen == Load)
					Load_(elect, date);
			}
		}
	}

	//print menu interface
	void MainMenu::print_Menu()
	{
		cout << "\nChoose which action u wish to do:\n"
			" 1. Add a new province\n"
			" 2. Add a new voter\n"
			" 3. Add a new patry\n"
			" 4. Make a voter a party member\n"
			" 5. Print all provinces\n"
			" 6. Print all voters\n"
			" 7. Print all partys\n"
			" 8. Insert voter vote\n"
			" 9. Print elections results\n"
			"10. Exit program\n"
			"11. Save election to file\n"
			"12. Load an election from file\n";
	}
	void MainMenu::print_Mini_Menu()
	{
		cout << "Enter what you want to do:\n" <<
			"1.start new election.\n" <<
			"2.load an existing election \n" <<
			"3.exit the program \n";
	}

	//handle user's mini menu choices
	void MainMenu::StartNewElection_ (election*& elect, bool& electionType, string& date, bool& valid)
	{
		valid = true;
		cout << "Enter elections date, and '0' for normal election or '1' for simple election" << endl;
		cin >> buffer1 >> electionType;
		date = buffer1;
		try {
			if (electionType == normal)
				elect = new election(date);
			else {
				cout << "Enter the number of senators" << endl;
				cin >> inputA;
				elect = new simpleElections(date, inputA);
			}
		}
		CATCH CATCH_ALL{ cout << "Error: Couldn't start this election\n" << endl; valid = false; }
	}
	void MainMenu::Load_             (election*& elect, string& date, bool& valid)
	{
		valid = true;
		cout << "Enter the name of file that you want to load" << endl;
		cin >> buffer1;
		ifstream infile(buffer1, ios::binary);

		try {
			if (!infile)
				throw ALERT("Failed to open file\n");
		} CATCH_EXIT

		infile.read(rcastc(&type), sizeof(int));
		infile.read(rcastc(&inputA), sizeof(int));   //get size of string
		date.resize(inputA);                        //dynamic allocate string
		infile.read(rcastc(&date[0]), inputA);

		try {
			if (type == 0)
				elect = new election();
			else if (type == 1) {
				infile.read(rcastc(&inputA), sizeof(int));
				elect = new simpleElections();
			}
			else throw ALERT("Error while reading file\n");
		}
		CATCH_ALL{ cout << "Error: error while reading file\n" << endl; valid = false; }

			try { elect->load(infile); }
			CATCH_ALL{ cout << "Error: error while reading file\n" << endl; valid = false; }
			infile.close();
	}

	//handle user's main menu choices
	void MainMenu::AddaNewProvince_      (election*& elect, bool electionType)
	{
		if (electionType == simple) cout << "Error. This is a simple election, there are no provinces" << endl;
		else {
			cout << "Enter province's name, number of delegators and 1 for seperated (0 otherwise):" << endl;
			cin >> buffer1 >> inputA >> isseperated;
			try { elect->addProvince(buffer1, inputA, isseperated); }
			CATCH CATCH_ALL{ cout << "Error: error while trying to add a new province\n" << endl; }
		}
	}
	void MainMenu::AddaNewVoter_         (election*& elect, bool electionType)
	{
		if (electionType == simple) {
			cout << "Enter voter's name, id, date of birth\n";
			cin >> buffer1 >> inputA >> buffer2;
			try { elect->addVoter(buffer1, inputA, buffer2, 0, electionType); }
			CATCH CATCH_ALL{ cout << "Error: error while trying to add a new voter\n" << endl; }
		}
		else {
			cout << "Enter voter's name, id, date of birth and the number of province they live at" << endl;
			cin >> buffer1 >> inputA >> buffer2 >> inputB;
			try { elect->addVoter(buffer1, inputA, buffer2, inputB, electionType); }
			CATCH CATCH_ALL{ cout << "Error: error while trying to add a new voter\n" << endl; }
		}
	}
	void MainMenu::AddaNewParty_         (election*& elect)
	{
		cout << "Insert party name and party leader ID by this order\n";
		cin >> buffer1 >> inputA;
		try { elect->addParty(buffer1, inputA); }
		CATCH CATCH_ALL{ cout << "Error: error while trying to add a new party\n" << endl; }
	}
	void MainMenu::MakeVoterPartyMember_ (election*& elect)
	{
		cout << "Enter the voter ID, party number, province number\n";
		cin >> inputA >> inputB >> inputC;
		try { elect->addNewPartyMember(inputA, inputB, inputC); }
		CATCH CATCH_ALL{ cout << "Error: error while trying to add a new party member\n" << endl; }
	}
	void MainMenu::InsertVote_           (election*& elect, bool electionType)
	{
		cout << "Enter the voter ID, party number\n";
		cin >> inputA >> inputB;
		try { elect->addVote(inputB, inputA, electionType); }
		CATCH CATCH_ALL{ cout << "Error: error while trying to add a new vote\n" << endl; }
	}
	void MainMenu::ShowElectionResults_  (election*& elect)
	{
		try { elect->whatsTheResult(); }
		CATCH_ALL{ cout << "Error: error while trying to calculate the results\n" << endl; }
	}
	void MainMenu::Save_                 (election*& elect)
	{
		cout << "Enter the name of file that the data will be saved to" << endl;
		cin >> buffer1;
		ofstream outfile(buffer1, ios::binary | ios::trunc);

		try {
			if (!outfile)
				throw ALERT("Failed to open file\n");
		}
		CATCH

		try { elect->save(outfile); }
		CATCH_ALL{ cout << "Error: error while writing file\n" << endl; }

		outfile.close();
	}
	void MainMenu::Load_                 (election*& elect, string& date)
	{
		cout << "Enter the name of file that you want to load" << endl;
		cin >> buffer1;
		ifstream infile(buffer1, ios::binary);

		try {
			if (!infile)
				throw ALERT("Failed to open file\n");
		}
		CATCH_EXIT

		infile.read(rcastc(&type), sizeof(int));
		infile.read(rcastc(&inputA), sizeof(int));   //get size of string
		date.resize(inputA);                        //dynamic allocate string
		infile.read(rcastc(&date[0]), inputA);

		try {
			if (type == 0)
				elect = new election(date);
			else if (type == 1) {
				infile.read(rcastc(&inputA), sizeof(int));
				elect = new simpleElections(date, inputA);
			}
			else throw ALERT("Error while reading file\n");
		}
		CATCH CATCH_ALL{ cout << "Error: error while reading file\n" << endl; }

		try { elect->load(infile); }
		CATCH_ALL{ cout << "Error: error while reading file\n" << endl; }

		infile.close();
	}
}