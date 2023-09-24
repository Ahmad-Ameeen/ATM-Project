

#include <iostream>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<iomanip>
using namespace std;
const string FileName = "Clint.text";
struct stClint
{
    string AccountNumber;
    string Pincode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;

};
stClint ClintInfo;
enum enQuickWithDrowOptions
{
    WithDrow20 = 1,
    WithDrow50 = 2,
    WithDrow100 = 3,
    WithDrow200 = 4,
    WithDrow400 = 5,
    WithDrow600 = 6,
    WithDrow800 = 7,
    WithDrow1000 = 8,
};
enum enMainMenueOptions
{
    QWithDrow = 1,
    NWithDrow = 2,
    Deposit = 3,
    echeckBalance = 4,
    eLogout = 5
};

vector <string>  SplitString(string s1, string delim)
{
    vector <string> WordAfterSplit;
    string sWord = "";
    short Pos = 0;
    while ((Pos = s1.find(delim)) != string::npos)
    {

        sWord = s1.substr(0, Pos);//store the sword
        if (sWord != "")
        {
            WordAfterSplit.push_back(sWord);
        }
        s1.erase(0, (Pos + delim.length()));
    }
    if (s1 != "")
    {
        WordAfterSplit.push_back(s1);
    }

    return WordAfterSplit;
}
string ConvertClintToLine(stClint Clint, string Seperatoer = "#//#")// Defult Data
{

    string stLine = "";
    stLine += Clint.AccountNumber + Seperatoer;
    stLine += Clint.Pincode + Seperatoer;
    stLine += Clint.Name + Seperatoer;
    stLine += Clint.Phone + Seperatoer;
    stLine += to_string(Clint.AccountBalance);
    return stLine;

}
stClint ConvertLineToRecord(string Line, string Seperatoer = "#//#")// Defult Data
{
    stClint Clint;
    vector <string> vClintData;
    vClintData = SplitString(Line, "#//#");
    Clint.AccountNumber = vClintData[0];
    Clint.Pincode = vClintData[1];
    Clint.Name = vClintData[2];
    Clint.Phone = vClintData[3];
    Clint.AccountBalance = stoi(vClintData[4]);
    return Clint;

}
vector <stClint> LoadClintsDataFromFile(string FileName)
{
    stClint Clint;
    string Line;
    fstream WriteRecord;
    vector <stClint> vClint;
    WriteRecord.open(FileName,ios::in);
    if (WriteRecord.is_open())
    {

        while (getline(WriteRecord, Line))
        {
            Clint = ConvertLineToRecord(Line);
            vClint.push_back(Clint);

        }
        WriteRecord.close();

    }

    return vClint;
}
bool FindClintByAccountNumber(string AccountNumbre,string PinCode ,stClint& ClintInfo)
{
    vector <stClint> vClints = LoadClintsDataFromFile(FileName);
    for (stClint C : vClints)
    {
        if (C.AccountNumber == AccountNumbre && C.Pincode==PinCode)
        {
            ClintInfo = C;
            return true;
        }

    }

    return false;
}
bool LoudClintInfo(string AccountNumber, string PinCode)
{
    if (FindClintByAccountNumber(AccountNumber,PinCode,ClintInfo))
        return true;
    else
    {
        return false;
    }

}
enMainMenueOptions ReadMainMenueOption()
{
    short ChooseNumber = 0;
    cout << "Choose What Do You Want To Do? [1 To 5]? ";
    cin >> ChooseNumber;
    return enMainMenueOptions(ChooseNumber);
}
short ReadQuickWithDrowOption()
{
    short ChooseNumber = 0;
    while (ChooseNumber<1 || ChooseNumber>9)
    {
        cout << "Choose What To WithDrow From [1] to [9]?";
        cin >> ChooseNumber;
    }
    return ChooseNumber;
}
void ShowATMMainMenue();
void Login();
void PerformMainMenueOption(enMainMenueOptions MainMenueOptions);
void GoBackToATMMainMenue()
{
    cout << "\nPress Any Key To Go Back To Main Menue....";
    system("Pause>0");
    ShowATMMainMenue();
}
void SaveDataFromVectorToFile(vector <stClint> vClint)
{
    string Line;
    fstream FileContentVector;
    FileContentVector.open(FileName, ios::out);// Write mode 
    if (FileContentVector.is_open())
    {
        for (stClint& Clint : vClint)
        {
            if (Clint.MarkForDelete != true)
            {
                Line = ConvertClintToLine(Clint);
                FileContentVector << Line << endl;
            }
        }
        FileContentVector.close();

    }
}
void SaveUpdatedData()
{
    vector <stClint> vClint = LoadClintsDataFromFile(FileName);
    for (stClint& C : vClint)
    {
        if (C.AccountNumber == ClintInfo.AccountNumber)
        {
            C.AccountBalance = ClintInfo.AccountBalance;
            break;
        }
    }
    SaveDataFromVectorToFile(vClint);
}
bool DepositBalanceToClintByAccountNumber(string AccountNumber, double DepositAmount, vector <stClint> vClints)
{
    char Answer = 'N';
    cout << "Are You Sure You Want To Perform This Transaction? y/n?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        for (stClint& C : vClints)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += DepositAmount;
                SaveDataFromVectorToFile(vClints);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
                return true;
            }
        }

    }
    return false;
}
bool checkWithDrowAmountExceedOrNot(int WithDrowAmount)
{
    return (WithDrowAmount <= ClintInfo.AccountBalance) ? true : false;

}
void ShowQuickWithDrowScreen();
void AmountExceedYourBalance()
{
    cout << "The Amount Exceeds Your Balance , Make Another Choice.\n";
    cout << "Press Any Key To Continue...";
    system("pause>0");
   ShowQuickWithDrowScreen();

}
short GetQuickWithDrowAmount(short  QuickWithDrowOption)
{
    switch (QuickWithDrowOption)
    {
    case 1:
        return 20;
        break;
    case 2:
        return 50;
        break;
    case 3:
        return 100;
        break;
    case 4:
        return 200;
        break;
    case 5:
        return 400;
        break;
    case 6:
        return 600;
        break;
    case 7:
        return 800;
        break;
    case 8:
        return 1000;
        break;
    default:

        break;
    }
}
 void PerformQuickWithDrowOption(short  QuickWithDrowOption)
 {
     if (QuickWithDrowOption == 9)
         return;
     short WithDrowAmount = 0;
     WithDrowAmount = GetQuickWithDrowAmount(QuickWithDrowOption);
     if (WithDrowAmount > ClintInfo.AccountBalance)
     {
         AmountExceedYourBalance();
         return;
     }
   
     vector <stClint> vClint = LoadClintsDataFromFile(FileName);
     DepositBalanceToClintByAccountNumber(ClintInfo.AccountNumber, WithDrowAmount * -1, vClint);
     ClintInfo.AccountBalance -= WithDrowAmount;


   
 }
void ShowQuickWithDrowScreen()
{
    cout << "==================================================================\n";
    cout << "\t\t\tQuick WithDrow \t\t\t\t\t\n";
    cout << "==================================================================\n";
    cout << "\t\t [1] 20" << setw(10) << "[2] 50\n";
    cout << "\t\t [3] 100" << setw(10) << "[4] 200\n";
    cout << "\t\t [5] 400" << setw(10) << "[6] 600\n";
    cout << "\t\t [7] 800" << setw(10) << "  [8] 1000\n";
    cout << "\t\t [9] Exit.\n";
    cout << "==================================================================\n";
    cout << "Your Balance Is " << ClintInfo.AccountBalance << endl;
    PerformQuickWithDrowOption(ReadQuickWithDrowOption());
}
void ShowCheckBalanceScreen()
{
    cout << "==================================================================\n";
    cout << "\t\t\tCheck Balance Screen \t\t\t\t\t\n";
    cout << "==================================================================\n";
    cout << "Your Balance Is:" << ClintInfo.AccountBalance << endl;
}
int ReadAmountNumberMultipleOf5()
{
    int Amount=0;
    do
    {
        cout << "Enter An Amount Multiple Of 5's? ";
        cin >> Amount;

    } while (Amount%5!=0);
    return Amount;
}
void ShowNormadWithDrowScreen();
void PerformNormalWithDrow()
{
    int WithDrowAmount = ReadAmountNumberMultipleOf5();
    if (WithDrowAmount > ClintInfo.AccountBalance)
    {
        cout << "The Amount Exceeds Your Balance , Make Another Choice.\n";
        cout << "Press Any Key To Continue...";
        system("pause>0");
        ShowNormadWithDrowScreen();
    }
    vector <stClint> vClint = LoadClintsDataFromFile(FileName);
    DepositBalanceToClintByAccountNumber(ClintInfo.AccountNumber, WithDrowAmount * -1, vClint);
    ClintInfo.AccountBalance -= WithDrowAmount;
}
void ShowNormadWithDrowScreen()
{
    cout << "==================================================================\n";
    cout << "\t\t\tNormal WithDrow screen \t\t\t\t\t\n";
    cout << "==================================================================\n";
    PerformNormalWithDrow();
}
double ReadDepositAmount()
{
    int Amount = 0;
    cout << "Please Enter a Positive Deposit Amount? ";
    cin >> Amount;
    while (Amount<=0)
    {
        cout << "Please Enter a Positive Deposit Amount? ";
        cin >> Amount;
    }
    return Amount;
}
void PerformDepositOption()
{
    double DepositAmount = ReadDepositAmount();
    vector <stClint> vClint = LoadClintsDataFromFile(FileName);
    DepositBalanceToClintByAccountNumber(ClintInfo.AccountNumber, DepositAmount , vClint);
    ClintInfo.AccountBalance += DepositAmount;
}
void showDepositScreen()
{
      cout << "==================================================================\n";
      cout << "\t\t\tDeposit screen \t\t\t\t\t\n";
      cout << "==================================================================\n";
      PerformDepositOption();

}
void PerformMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case QWithDrow:
        system("cls");
        ShowQuickWithDrowScreen();
        GoBackToATMMainMenue();
        break;
    case NWithDrow:
        system("cls");
        ShowNormadWithDrowScreen();
        GoBackToATMMainMenue();

        break;
    case Deposit:
        system("cls");
        showDepositScreen();
        GoBackToATMMainMenue();
        break;
    case echeckBalance:
        system("cls");
        ShowCheckBalanceScreen();
        GoBackToATMMainMenue();
        break;
    case eLogout:
        Login();
        break;
    default:
        break;
    }
}
void ShowATMMainMenue()
{
    system("cls");
    cout << "==================================================================\n";
    cout << "\t\t\tATM Main Menue Screen \t\t\t\t\t\n";
    cout << "==================================================================\n";
    cout << "\t\t[1] Quick WithDrow.\n";
    cout << "\t\t[2] Normal WithDrow.\n";
    cout << "\t\t[3] Deposit.\n";
    cout << "\t\t[4] Check Balance.\n";
    cout << "\t\t[5] Logout.\n";
    cout << "==================================================================\n";
    PerformMainMenueOption(ReadMainMenueOption());
}
void Login()
{

    string AccountNumber = "", PinCode = "";
    bool LoginFaild = false;
    do
    {
        system("cls");
        cout << "==================================================================\n";
        cout << "\t\t\tLogin Screen \t\t\t\t\t\n";
        cout << "==================================================================\n";
        if (LoginFaild)
        {
            cout << "Invlaid AccountNumber / PinCode!\n";
        }
        cout << "Enter AccountNumber? ";
        cin >> AccountNumber;
        cout << "Enter PinCode? ";
        cin >> PinCode;

        LoginFaild = !LoudClintInfo(AccountNumber, PinCode);

    } while (LoginFaild);


    ShowATMMainMenue();
}
int main()
{
    Login();
}

