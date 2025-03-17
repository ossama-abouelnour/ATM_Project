#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

string ClientsFileName = "Clients.txt";

struct sClient {
	string AccountNumber, PinCode, Name, Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

sClient CurrentClient;

enum enMainMenuOptions {
	QuickWithdraw = 1, NormalWithdraw = 2, Deposit = 3, CheckBalance = 4, Logout = 5
};

void ShowMainMenu();
void login();
void ShowQuickWithdrawScreen();
void ShowNormalWithdrawScreen();


vector<string> SplitString(string S1, string Delim = "#//#")
{
	short Pos = 0;
	vector<string> vString;
	string sWord;

	while ((Pos = S1.find(Delim)) != string::npos)
	{
		sWord = S1.substr(0, Pos);

		if (sWord != "") 
		{
			vString.push_back(sWord);
		}

		S1.erase(0, Pos +Delim.length());
	}

	if (S1 != "")
	{
		vString.push_back(S1);
	}

	return vString;
}

sClient ConvertLineToRecord(string Line, string Delim = "#//#")
{
	sClient Client;
	vector<string> vClientData = SplitString(Line, Delim);
	
	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);
	return Client;
}

vector<sClient> LoadClientsDataFromFile(string FileName)
{
	fstream MyFile;
	vector<sClient> vClients;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}

	
	return vClients;
}

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, sClient& Client)
{
	vector<sClient> vClient = LoadClientsDataFromFile(ClientsFileName);

	for (sClient& C : vClient)
	{
		if (AccountNumber == C.AccountNumber && PinCode == C.PinCode)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool LoadClientInfo(string AccountNumber, string PinCode)
{
	return FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient);
}

short ReadMainMenuOption()
{
	short Choice = 0;
	cout << "Please make a choice? [1 to 5]: ";
	cin >> Choice;
	return Choice;
}

void GoBackToMainMenue()
{
	cout << "Press any key to go back to main menu.....";
	system("pause>0");
	ShowMainMenu();
}

short ReadQuickWithdrawOption()
{
	short Choice = 0;
	while(Choice < 1 || Choice > 9)
	{
	cout << "Please make a choice? [1 to 9]: ";
	cin >> Choice;
	}
	
	return Choice;
}

short GetQuickWithDrawAmount(short QuickWithDrawOption)
{
	switch (QuickWithDrawOption)
	{
	case 1:
		return 20;
	case 2:
		return 50;
	case 3:
		return 100;
	case 4:
		return 200;
	case 5:
		return 400;
	case 6:
		return 600;
	case 7:
		return 800;
	case 8:
		return 1000;
	default:
		return 0;
	}
}

string ConvertRecordToLine(sClient Client, string Delim = "#//#")
{
	string DataLine = "";

	DataLine = Client.AccountNumber + Delim;
	DataLine += Client.PinCode + Delim;
	DataLine += Client.Name + Delim;
	DataLine += Client.Phone + Delim;
	DataLine += to_string(Client.AccountBalance);

	return DataLine;
}

vector<sClient> SaveClientsDataToFile(string FileName, vector<sClient>& vClients)
{
	fstream MyFile;

	MyFile.open(ClientsFileName, ios::out);

	if (MyFile.is_open())
	{
		for (sClient& C : vClients)
		{
			if (C.MarkForDelete = true)
			{
				string Line = ConvertRecordToLine(C);
				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient>& vClients)
{

	char Answer = 'n';
	cout << "\n\nAre you sure you want to perform this transaction? (y/n)" ;
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y')
	{
		for (sClient& C : vClients)
		{
			if (AccountNumber == C.AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveClientsDataToFile(ClientsFileName, vClients);
				cout << "\n\nTransaction Successfull. New Balance is: " << C.AccountBalance << endl;
				return true;
			}
		}
		return false;
	}
}

void PerformQuickWithdrawOption(short Option)
{
	if (Option == 9)
		return;

	short WithdrawnAmount = GetQuickWithDrawAmount(Option);

	if (CurrentClient.AccountBalance < WithdrawnAmount)
	{
		cout << "\n The amounts exceeds your balance, please chose an amount less than [" << CurrentClient.AccountBalance << "]\n";
		cout << "Press any key to continue...";
		system("pause>0");
		ShowQuickWithdrawScreen();
	}

	vector<sClient> vClient = LoadClientsDataFromFile(ClientsFileName);

	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawnAmount * -1, vClient);
	CurrentClient.AccountBalance -= WithdrawnAmount;
}

void ShowQuickWithdrawScreen()
{
	system("cls");

	cout << "===========================================\n";
	cout << "\t  Qucik Withdraw\n";
	cout << "===========================================\n";
	cout << "\t[1] 20\t\t[2] 50\n";
	cout << "\t[3] 100\t\t[4] 200\n";
	cout << "\t[5] 400\t\t[6] 600\n";
	cout << "\t[7] 800\t\t[8] 1000\n";
	cout << "\t[9] Exit\n";
	cout << "===========================================\n";
	cout << "Your Balance is " << CurrentClient.AccountBalance << endl;
	PerformQuickWithdrawOption(ReadQuickWithdrawOption());
}

int ReadWithdrawAmount()
{
	int Amount = 0;
	cout << "Please enter an amount in multiples of 5 ? ";
	cin >> Amount;

	while (Amount % 5 != 0)
	{
		cout << "\nWrong amount, Please enter an amount in multiples of 5 ? ";
		cin >> Amount;
	}
	return Amount;
}

void PerformNormalWithdrawOption()
{
	int WithdrawAmount = ReadWithdrawAmount();

	if (WithdrawAmount > CurrentClient.AccountBalance)
	{
		cout << "\nThe amount requested exceeds your balance, please make another choice.\n";
		cout << "\nPress Any Key To Continue...";
		system("pause>0");
		ShowNormalWithdrawScreen();
		return;
	}

	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawAmount * -1, vClients);
	CurrentClient.AccountBalance -= WithdrawAmount;
}

void ShowNormalWithdrawScreen()
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t  Normal Withdraw\n";
	cout << "===========================================\n";
	PerformNormalWithdrawOption();
}

double ReadDepositAmount()
{
	double DepositAmount = 0;

	cout << "\nPlease enter the amount you would like to deposit: ";
	cin >> DepositAmount;

	while (DepositAmount <= 0)
	{
		cout << "\nPlease enter a positive Deposit Amount? ";
		cin >> DepositAmount;
	}

	return DepositAmount;
}

void PerformDepositOption()
{
	double DepositAmount = ReadDepositAmount();

	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, DepositAmount, vClients);
	CurrentClient.AccountBalance += DepositAmount;

}

void ShowDepositScreen()
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t  Make a Deposit\n";
	cout << "===========================================\n";
	PerformDepositOption();
}

void ShowCheckBalanceScreen()
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t  Account Balance\n";
	cout << "===========================================\n";
	cout << "Your Balance is " << CurrentClient.AccountBalance << "\n";
}

void PerformMainMenuOptions(enMainMenuOptions MainMenuOption)
{
	switch (MainMenuOption)
	{
	case QuickWithdraw:
		system("cls");
		ShowQuickWithdrawScreen();
		GoBackToMainMenue();
		break;
	case NormalWithdraw:
		system("cls");
		ShowNormalWithdrawScreen();
		GoBackToMainMenue();
		break;
	case Deposit:
		system("cls");
		ShowDepositScreen();
		GoBackToMainMenue();
		break;
	case CheckBalance:
		system("cls");
		ShowCheckBalanceScreen();
		GoBackToMainMenue();
		break;
	case Logout:
		system("cls");
		login();
		break;
	}
}

void ShowMainMenu()
{
	system("cls");
	cout << "\n";
	cout << "\t  Hi, " << CurrentClient.Name << "\n\n";

	cout << "===========================================\n";
	cout << "\t  ATM Main Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "===========================================\n";
	PerformMainMenuOptions((enMainMenuOptions)ReadMainMenuOption());
}

void login()
{
	bool LoginFailed = false;
	string AccountNumber, PinCode;

	do
	{
		system("cls");
		cout << "----------------------------------------\n";
		cout << "\t\tLogin Screen\n";
		cout << "----------------------------------------\n";
		if (LoginFailed)
		{
			cout << "Wrong Account Number/Pin Code\nTry Again....\n";
		}
		cout << "Username: ";
		getline(cin >> ws, AccountNumber);
		cout << "\nPinCode: ";
		getline(cin >> ws, PinCode);

		LoginFailed = !LoadClientInfo(AccountNumber, PinCode);

	} while (LoginFailed);
	ShowMainMenu();
}


int main()
{
	login();

	system("pause>0");
	return 0;
}

