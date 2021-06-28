#include "Elections.h"


namespace elections
{
	//constructor
	election:: election  (string _date)
	{
		isDateValid(_date);
		date = _date;
	}

	//destructor
	election:: ~election ()
	{
			for (int i = 0; i < voterArr.size(); i++)
				delete voterArr[i];
			for (int i = 0; i < partyArr.size(); i++)
				delete partyArr[i];
			for (int i = 0; i < provArr.size(); i++)
				delete provArr[i];
	}

	//setters
	void election:: set_Date (const string _date)
	{
		date = _date;
	}

	//Party Functions
	void      election:: addParty           (const string name, const int leaderID)  //add a party to partys array
	{
		party* a;
		isPartyValid(name,leaderID);
		try { a = new party(name, leaderID); } CHECK_BAD_ALLOC
		a->set_partyNum(givePartyANumber());
		partyArr.push_back(a);
		for (int i = 0; i < provArr.size(); i++) {
			a->addProvice(provArr[i]->getName(), provArr[i]->getNum());
			provArr[i]->addParty(a);
		}
	}
	const int election:: givePartyANumber   ()const
	{
		return partyArr.size();
	}
	void      election:: addNewPartyMember  (const int ID, const int partyNumber, const int provinceNum)
	{
		for (int i = 0; i < partyArr.size(); i++) {
			if (partyNumber == partyArr[i]->get_partyNum())
				for (int j = 0; j < partyArr[i]->get_logicSize(); j++)
					if (provinceNum == partyArr[i]->get_province(j).get_provNum())
						partyArr[i]->get_province(j).addToTail(ID);
		}
	}
	void      election:: printAllPartys     ()const   //print all partys in partys array
	{
		for (int i = 0; i < partyArr.size(); i++) {
			cout << *partyArr[i];
			cout << "\n";
		}
	}

	//Voter Functions
	void      election:: addVoter          (const string name, const int id, const string birthD, const int provNum, const bool electionType)
	{
		int idx = 0;
		isVoterValid(id, provNum, electionType, date, birthD);
		if (electionType == normal) {
			for (idx = 0; idx < provArr.size(); idx++) {     //get index of province in the array
				if (provArr[idx]->getNum() == provNum) {
					voter* a;
					try { a = new voter(name, id, birthD, provArr[idx]); } CHECK_BAD_ALLOC
					voterArr.push_back(a);
					provArr[idx]->addVoter(a);
				}
			}
		}
		else {
			voter* a;
			try { a = new voter(name, id, birthD, nullptr); } CHECK_BAD_ALLOC
			voterArr.push_back(a);
		}
	}
	void      election:: printAllVoters    ()const {  //printing all the voters inside the election voter array
		for (int i = 0; i < voterArr.size(); i++) {
			cout << *voterArr[i];
			cout << "voter's city number:" << voterArr[i]->get_provP()->getNum() << "\n";
			cout << "\n";
		}
	}
	const int election:: returnVoterIndex  (const int id)const{
		for (int i = 0; i < voterArr.size(); i++) {
			if (voterArr[i]->get_id() == id)
				return i;
		}
		return 0;
	}

	//Province Functions
	void      election:: addProvince          (const string name, const int senNum, const bool isseperated)   //add a province to the array
	{
		int num = 0;
		num = giveProvinceANumber();
		isProvinceValid(name);
		if (isseperated == false)
		{
			province* a;
			try { a = new province(name, senNum); } CHECK_BAD_ALLOC
			a->set_num(num);
			provArr.push_back(a);
			int y = provArr.size();
			for (int i = 0; i < partyArr.size(); i++) //add province to all party's "struct provinces"
				partyArr[i]->addProvice(name, num);
		}
		else
		{
			SeperatedProvince* a;
			try { a = new SeperatedProvince(name, senNum); } CHECK_BAD_ALLOC
			a->set_num(num);
			provArr.push_back(a);
			for (int i = 0; i < partyArr.size(); i++) //add province to all party's "struct provinces"
				partyArr[i]->addProvice(name, num);
		}
	}
	void      election:: printAllProvinces    ()const {   // printing all the province array data
		for (int i = 0; i < provArr.size(); i++) {
			cout << *provArr[i];
			cout << "\n";
		}
	}
	const int election:: giveProvinceANumber  ()const
	{
		return provArr.size();
	}

	//checkers
	void      election:: isVoterValidToJoinParty  (const int id, const int partyNum, const int provinceNum, const bool electionType)const
	{
		bool registered = false;

		if (electionType == normal)
			if (provinceNum >= provArr.size() || provinceNum < 0)
				throw ALERT("Province's number must exist\n");

		if (partyNum >= partyArr.size() || partyNum < 0)
			throw ALERT("Party's number must exist\n");

		for (int i = 0; i < voterArr.size(); i++)
			if (voterArr[i]->get_id() == id) {
				registered = true;
				break;
			}
		if (registered) return;
		else throw ALERT("Voter must be registered\n");
	}
	void      election:: isPartyValid             (const string name, const int leaderID)const
	{
		for (int i = 0; i < partyArr.size(); i++)                          
		{
			if (leaderID == partyArr[i]->get_leaderID())                   //checks that the partyleader isnt leading another party
				throw ALERT("leader already leading another party\n");

			if (name == partyArr[i]->get_partyName())                      //checks that the party name doesnt exist
				throw ALERT("party name already exist\n");
		}
		for (int j = 0; j < voterArr.size(); j++)                          //checks that the leader exists in voters array
			if (leaderID == voterArr[j]->get_id())
				return;
		throw ALERT("leader must be a registered voter\n");
	}
	void      election:: isProvinceValid          (const string name)const
	{
		for (int i = 0; i < provArr.size() && provArr.size() < provArr.capacity(); i++)
			if (name == provArr[i]->getName())                                          //check if the the province name exist
				throw ALERT("This province name is taken\n");
	}
	void      election:: isTheVoteValid           (const int partyNum, const int voterID)
	{
		bool registered = false;

		if (partyNum >= partyArr.size() || partyNum < 0)
			throw ALERT("party's number must exist\n");

		for (int i = 0; i < voterArr.size(); i++) {
			if (voterArr[i]->get_id() == voterID) {
				if (voterArr[i]->get_voteIndecator() == 1)
					throw ALERT("Voter already voted\n");
				registered = true;
				break;
			}
		}
		if (registered) return;
		else throw ALERT("Voter must be registered\n");
	}
	void      election:: isVoterValid             (const int id, const int provNum, const bool electionType, const string date, const string birthD)const
	{
		isOver18(date, birthD);                                                     //check that the voter is over 18

		if (electionType == normal) {
			if (provNum >= provArr.size() || provNum < 0)                           //check that the province number exist
				throw ALERT("Province number must be registered\n");

			for (int i = 0; i < voterArr.size(); i++) {                             //check that the voter's id doesnt exist
				if (voterArr[i]->get_id() == id)
					throw ALERT("Voter's id is already registered\n");

			}
		}
	}
	void      election:: isOver18                 (const string date, const string birthD)const
	{
		isDateValid(birthD);
		int PersonDays = calcDateInDays(birthD);
		int DateDays = calcDateInDays(date);
		if ((DateDays - PersonDays) < 18 * 365)
			throw ALERT("This citizen is under 18, hence can't take part in the election\n");
	}
	const int election:: calcDateInDays           (const string date)const
	{
		int days = stoi(date.substr(0, 2));
		int month = stoi(date.substr(3, 2));
		int year = stoi(date.substr(6, 4));
		int i, j;
		for (i = JANUARY, j = 1; i <= DECEMBER; i++, j++)
			if (j == month)
				month = i;
		return year * 365 + month + days;
	}
	void      election:: isDateValid              (const string date)const
	{
		if (date.size() == 10) {
			for (int i = 0; i < date.size(); i++) {
				if (i == 2 || i == 5) {
					if (date[i] != '.' && date[i] != '/')
						throw ALERT("Invalid date, the only separators allowed are '.' or '/'\n");
				}
				else {
					if (!isdigit(date[i]))
						throw ALERT("Invalid date, year, month and days should contain only digits\n");
				}
			}
		}
		else throw ALERT("Invalid date\n");

		int days = stoi(date.substr(0, 2));
		int month = stoi(date.substr(3, 2));
		int year = stoi(date.substr(6, 4));

		if (year <= 0)
			throw ALERT("Invalid date, year must be a positive number\n");
		if (month <= 0 && month > 12)
			throw ALERT("Invalid date, month must be a number from 1 to 12\n");

		int i, j;
		for (i = JANUARY, j = 1; i <= DECEMBER; i++, j++) {
			if (j == month)
				if (days > i && days < 1)
					throw ALERT("Invalid date, the 'day' input is out of the range of days in this month\n");
		}
	}

	//vote process methods
	void election:: addVote (const int partyNum, const int voterID, const bool electionType) {

		int index = returnVoterIndex(voterID);
		isTheVoteValid(partyNum, voterID);

		if (electionType == normal) {
			int provinceNum = voterArr[index]->get_provP()->getNum();
			partyArr[partyNum]->get_province(provinceNum).add_vote(1);
			provArr[provinceNum]->addVote();
		}
		else {
			//enter ONLY if its a simple election
			partyArr[partyNum]->addTotalVote(1);
			voterArr[index]->setVoteIndecator(1);
			partyArr[partyNum]->get_province(0).add_vote(1);
		}
		totalVotes += 1;
		voterArr[index]->setVoteIndecator(1);
	}

	//result methods
	void election:: whatsTheResult        ()const {
		printDate(date);
		updatePartyPercentage();
		chooseElectors();
		printTheChosenElectors(provArr, partyArr);
		printTheResult(partyArr, 0);
	}
	void election:: updatePartyPercentage ()const {        //will update the percentage of votes in any party in ANY province
		for (int i = 0; i < partyArr.size(); i++) {
			for (int j = 0; j < provArr.size(); j++) {
				partyArr[i]->get_province(j).set_precet(provArr[j]->get_totalVotes());
			}
		}
	}
	void election:: chooseElectors        ()const
	{ 
		for (int i = 0; i < partyArr.size(); i++)
			partyArr[i]->resetElectors();
		for (int i = 0; i < provArr.size(); i++)
			provArr[i]->chooseElectors();
	}

	//operators
	const election& election:: operator= (const election& other) {
		if (this != &other)
		{
			date = other.date;
			totalVotes = other.totalVotes;
			voterArr = other.voterArr;
			partyArr = other.partyArr;
			provArr = other.provArr;
		}
		return *this;
	}

	//save & load
	void election:: save       (ostream& out)const
	{
		int type = 0, arrSize = 0;
		out.write(rcastcc(&type), sizeof(int));
		int size = 0;
		size = static_cast<int>(date.size());                                  //get size of string
		out.write(rcastcc(&size), sizeof(int));
		out.write(rcastcc(&date[0]), size);
		if (!out.good()) throw ALERT("Error while writing file\n");

		//save provinces
		arrSize = provArr.size();
		out.write(rcastcc(&arrSize), sizeof(int));                             //write sizes of provArr
		for (int i = 0; i < arrSize; i++) {                                    //write all provinces
			int x = provArr[i]->returnType();
			out.write(rcastcc(&x), sizeof(int));
			provArr[i]->save(out);
		}
		out.write(rcastcc(&totalVotes), sizeof(int));
		if (!out.good()) throw ALERT("Error while writing file\n");

		//save voters
		arrSize = voterArr.size();
		out.write(rcastcc(&arrSize), sizeof(int));                             //write sizes of voterArr
		for (int i = 0; i < arrSize; i++) {                                    //write all voters
			size = voterArr[i]->get_provP()->getNum();
			out.write(rcastcc(&size), sizeof(int));
			voterArr[i]->save(out);
		}
		if (!out.good()) throw ALERT("Error while writing file\n");

		//save partys
		size = partyArr.size();
		out.write(rcastcc(&size), sizeof(int));                                //write sizes of partyArr
		for (int i = 0; i < size; i++)                                         //write all parties
			partyArr[i]->save(out);
		if (!out.good()) throw ALERT("Error while writing file\n");
	}
	void election:: load             (istream& in)
	{
		int size, idx;

		//load provinces
		int type;
		in.read(rcastc(&size), sizeof(int));                                   //get sizes of partyArr
		for (int i = 0; i < size; i++) {                                       //load all parties
			province* a;
			try { a = new province(); } CHECK_BAD_ALLOC
			in.read(rcastc(&type), sizeof(int));
			if (type == 0)
				try { a = new province(); } CHECK_BAD_ALLOC
			if (type == 1)
				try { a = new SeperatedProvince(); } CHECK_BAD_ALLOC
			a->load(in);
			provArr.push_back(a);
		}
		in.read(rcastc(&totalVotes), sizeof(int));
		if (!in.good()) throw ALERT("Error while reading file\n");

		//load voters
		int voterSize;
		in.read(rcastc(&voterSize), sizeof(int));                              //get sizes of voterArr
		for (int i = 0; i < voterSize; i++) {                                  //load all voters
			in.read(rcastc(&idx), sizeof(int));
			voter* a;
			try { a = new voter; } CHECK_BAD_ALLOC
			provArr[idx]->addVoter(a);
			a->set_provP(provArr[idx]);
			a->load(in);
			voterArr.push_back(a);
		}
		if (!in.good()) throw ALERT("Error while reading file\n");

		//load partys
		in.read(rcastc(&size), sizeof(int));                                    //get sizes of partyArr
		for (int i = 0; i < size; i++) {                                        //load all parties
			party* a;
			try { a = new party; } CHECK_BAD_ALLOC
			a->load(in);
			partyArr.push_back(a);
		}
		if (!in.good()) throw ALERT("Error while reading file\n");

		syncProvinceData();
	}
	void election:: syncProvinceData            () {                                         //add the pointers to the provinces
		for (int i = 0; i < provArr.size(); i++) {                              //sync the partys
			for (int j = 0; j < partyArr.size(); j++)
				provArr[i]->addParty(partyArr[j]);
		}
	}
}

