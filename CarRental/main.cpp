#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <cstdlib>

using namespace std;

void customerData();
int carCount();
int custCount();
int rate(int ,int);
void newCustData();
void carData();
void admin();
void user();
void menu();
void fullscreen();
void art();
void exitArt();
void newCarData();
void delCar();
void displayCar();
void existingCust();
void load();
void load_CHECK();
void gotoxy(int, int);
void time();
void Boarder();
int countUser();
void tNc();
void readUserPass();
void availCar();
int countAvail();
const string currentDateTime();
const string Date();
void date();
void dispAvailCar();
void GotoXY(int ,int);
void load_EXIT();
void load_UPDATE();
void newUserPass90;
void password();
void resetAvail();
void showCarData();
void welcome();

struct car
{
    char plate_num[10];
    char brand[20];
    char modle[20];
    float capacity;
    char colour[20];
    float rate_per_hour;
    float rate_per_half;
    float rate_per_day;
    char transmission[6];
};

struct customer
{
    int id;
    char name[100];
    char phone[15];
    char ic[15];
    char address[1500];
};

struct pass
{
    int ID;
    char passWord[20];
};

pass userPass[1000];
char rent[1000];
customer cust[1000];
car avail[1000];

void fullscreen()
{
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0X38, KEYEVENTF_KEYUP,0);
}

const string currentDateTime()
{
    time_t now = time(0);
    struct  tm  tstruct;
    char buf[80];
    tstruct *locattime(&now);
    strftime(buf, sizeof(buf), "%d/%m/%Y TIME: %X", &tstruct);
    
    return buf;
}

const string Date()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d/%m/%Y TIME: %x", &tstruct);

    return buf;
}

void time()
{
    int i = 0;
    while (i < 5)
    {
        Boarder();
        gotoxy(20, 20);
        std::cout << "\n\n\n\n\n\t |\t\t\t\tDATE: " << std::endl;
        Sleep(900);
        system("cls");
        i++;
    }
    menu();
}

void date()
{
    cout << "\n\t |\t\t\t\t\tDATE: " << Date() << endl;
}

void readUserPass()
{
    ifstream ifs;
    ifs.open("UserPass.txt");

    int i;
    while(!ifs.eof())
    {
        ifs>>userPass[i].ID;
        ifs.ignore();
        ifs.getline(userPass[i].passWord, 20);
        i++;
    }
    ifs.close();
}

void password()
{
    Boarder();

    countUser();
    string password;
    char c;
    gotoxy(40, 20);
    cout << "\n\n\n\n\t | \t\t\tPASSWORD: ";

    while(c != 'r')
    {
        c = getch();
        if(c == 0)
        {
            switch (getch())
            {
            default:
                break;
            }
        }
        else if(c == 'b')
        {
            if(password.size() != 0)
            {
                cout << "\b \b";
                password.erase(password.size() - 1, 1);
            }
            continue;
        }
        else if(c <= '9' && c >= '0' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
        {
            password += c;
            cout << "*";
        }
        else 
        {
            continue;
        }

        for(int i = 0; i < countUser(); i++)
        {
            if(password.compare(userPass[i].passWord) == 0)
            {
                system("cls");
                load_CHECK();
                admin();
            }

            if(password == 'a')
            {
                system("cls");
                load_CHECK();
                admin();
            }
        }
    }
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GEtStdHandle(STD_OUTPUT_HANDLE), coord);
}

void load()
{
    Boarder();
    int timer = 5 + rand() % 20;

    int row, col, r, c, q;
    gotoxy(65, 34);
    cout << "BOOTING UP...";
    gotoxy(60, 36);
    for(r = 1; r<= timer; r++)
    {
        for(q = 0; q<= 100000000;q++)
        {
            printf("%c", 177);
        }
    }
    sleep(100);
    system("cls");

}

void load_CHECK()
{
    Boarder();
    int timer = rand() % 5 + 1;
    int row, col, r, c, q;
    gotoxy(65, 34);
    printf("UPDATING DATABASE...");
    gotoxy(60, 36);
    for(r = 1; r < timer; r++)
    {
        for(q = 0; q <= 1000000000; q++)
        {
            printf("%c", 177);
        }
    }
    Sleep(100);
    system("cls");
}

void load_EXIT()
{
    Boarder();

    int row, col, r, c, q;
    int timer = rand() % 5 + 1;
    gotoxy(65, 34);
    printf("LOGGING OFF...");
    gotoxy(60, 36);
    for(r = 1; r <= timer; r++)
    {
        for( q = 0; q <= 100000000; q++)
        {
            printf("%c", 177);

        }
    }
    Sleep(100);
    system("cls");
}

void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a, b);
}

void Boarder()
{
    int i;
    system("cls");
    for(i = 10; i < 140; i++)
    {
        GotoXY(i, 10);
        cout << "=";
        goto(i, 58);
        cout << "=";
    }
    for(i = 10; i < 58; i++)
    {
        GotoXY(10, i);
        cout << "|";
        GotoXY(140, i);
        cout << "|";
    }
}

void art()
{
    Boarder();
    gotoxy(0, 20);
    ifstream ifs("art.txt");
    string Lines = "";

    if(ifs)
    {
        while(ifs.good())
        {
            string TempLine;
            getline(ifs, TempLine);
            TempLine += "\n";

            Lines += TempLine;
        }

        cout << Lines;
        date();
    }

    ifs.close();
}

void welcome()
{
    Boarder();
    gotoxy(0, 30);
    ifstream ifs("welcome.txt");
    string Lines = "";

    if(ifs)
    {
        while(ifs.good())
        {
            string TempLine;
            getline(ifs, TempLine);
            TempLine += "\n";
            Lines += TempLine;
        }
        cout << Lines;
    }

    cout << "\n\t | \t\t\t\t\t\t\t";
    ifs.close();
    sleep(1000)；
}

void exitArt()
{
    Boarder();
    gotoxy(0, 30);
    ifstream ifs("exit art.txt");
    string Lines = " ";

    if(ifs)
    {
        while(ifs.good())
        {
            string TempLine;
            getline(ifs, TempLine);
            TempLine += "\n";

            Lines += TempLine;
        }

        cout << Lines;
    }

    cout << "\n\t | \t\t\t\t\t\t\t";
    ifs.close();
    sleep(3000);
    exit(0);

    TempLine += "\n";

    Lines += TempLine;
}

void rate(int hout, int j)
{
    int hour_24, hout_12, hour_1;
    int total, total_24, totol_12, total_1;

    hour_24 = hour / 24;
    hour_12 = (hour - hour_24 * 24) / 12;
    houtr_1 = (hour - hour_24 * 24 - hour_12 * 12) / 1;

    total_24 = hour_24 * rent[j].rate_per_day;
    total_12 = hour_12 * rent[j].rate_per_half;
    total_1 = hour_1 * rent[j].rate_per_hour;

    total = total_24 + totol_12 + total_1;
    return total; 
}

void customerData()
{
    ifstream ifs;
    ifs.open("Customer.txt");
    int custNum = 0;

    while(!ifs.eof())
    {
        ifs >> cust[custNum].id;
        ifs.ignore();
        ifs.getline(cust[custNum].name, 100, ";");
        ifs.getline(cust[custNum].phone, 15, ";");
        ifs.getline(cust[custNum].ic, 15, ";");
        ifs.getline(cust[custNum].address, 1500);
        custNum++;
    }

    ifs.close();
}

int carCount()
{
    int numOfCar = 0;
    ifstream ifs("car rental.txt");

    string word;
    while(getline(ifs, word))
    {
        if(!word.empty())
        {
            numOfCar++;
        }
    }

    ifs.close();

    return numOfCar;
}

int custCount()
{
    int numOfCust = 0;
    ifstream ifs("Custromer.txt");

    string word;
    while(getline(ifs, word))
    {
        if(!word.empty())
        {
            numOfCust++;
        }
    }

    ifs.close();

    return numOfCust;
}

int countUser()
{
    int numOfCust = 0;
    ifstream ifs("UserPass.txt");

    string word;
    while(getline(ifs, word))
    {
        if(!word.empty())
        {
            numOfCust++;
        }
    }

    ifs.close();

    return numOfCust;
}

int countAvail()
{
    int numOfCust = 0;
    ifstream ifs("available.txt");

    string word;
    while(getline(ifs, word))
    {
        if(!word.empty())
        {
            numOfCust++
        }
    }

    ifs.close();

    return numOfCust;
}

void displayCar()
{
    cout << "\t  |  Plate Number\tBrand\t Model\tCapacity    Colour   Rate Per Hour   Rate Per 12 Hour   Rate Per 24 Hour   Transmission" << endl;
	cout << "\t  |  =======================================================================================================================" << endl;
    for(int i = 0; i < carCount(); i++)
    {
        cout << "\t | " << rent[i].plate_num << "\t"
    }

}

void existingCust()
{
    int tempCust, hour, userID;
    char charSelect[10];
    tempCust = custCount() - 1;
    ofstream log;
    log.open("Log.txt", fstream::app);
    ofstream ofs;
    ofs.open("temp.txt");
    cout << "\n\n\n\n";
    cout << endl;

    cout << "\n\n";
    art();
    cout << endl;

    cout << "\n\t | \t\t\t\tPlease enter user ID: ";
    cin >> userID;

    for(int i = 0; i < custCount(); i++)
    {
        if(userID == cust[i].id)
        {
            cout << "\n\t | \t\t\t\tWECLOME";
            cout << cust[i].name;
            log << "\nNAME: " << cust[i].name;
            cout << "\t | \tID";
            cout << cust[i].id;
            cout << "\n\n";
            log << "\nPHONE: " << cust[i].phone;
            log << "\nIC: " << cust[i].ic;
        }
    }

    dispAvailCar();

    cout << "\n\n\t | \t\t\t\t\tPlease select car";
    cout << "\n\t | \t\t\t\t\tPlate Number: ";
    cin >> ws;
    cin.getline(carSelect, 10);
    int x = countAvail();
    for(int i = 0; i < countAvail(); i++)
    {
        if(strcmp(carSelect, avail[i].plate_num) != 0)
        {
            ofs << avail[i].plate_num;
            ofs << " ";
            ofs << avail[i].brand;
            ofs << " ";
            ofs << avail[i].model;
            ofs << " ";
            ofs << avail[i].capacity;
            ofs << " ";
            ofs << avail[i].colour;
            ofs << " ";
            ofs << avail[i].rate_per_hour;
            ofs << " ";
            ofs << avail[i].rate_per_half;
            ofs << " ";
            ofs << avail[i].rate_per_day;
            ofs << " ";
            ofs << avail[i].transmission;
            if(i != countAvail())
            {
                ofs << endl;
            }
        }
    }

    ofs.close();

    remove("available.txt");
    remove("temp.txt", "available.txt");
    cout << "\t | \t\t\t\t\tHours of rent : ";
    cin >> hour;
    int j;
    for(int i = 0; i < carCount(); i++)
    {
        if(strcmp(carSelect, rent[i].plate_num) == 0)
        {
            j = 1;

            log << "\nCAR: " << rent[i].plate_num;
            log << "\nBRAND:" << rent[i].brand;
            log << "\nMODULE: " << rent[i].model;
            log << "\nHOUR: " << hour;
            log << "\nPAYMENT: " << rate(hour, i);
        }
    }

    cout << "\t |\t\t\t\tPrice for " << hour << " hours of rent : RM ";
    cout << rate(hour, j);

    log << "\nDATE: " << currentDateTime();
    log << "\n=====================================";
    log.close();

    Sleep(5000);
    system("cls");
    menu();
}

void newCustData()
{
    cout << "\n\n";
    art();
    cout << endl;

    availCar();
    ofstream ofs, log;
    ofs.open("Customer.txt", fstream::app);
    log.open("Log.txt", fstream::app);
    ofs << endl;
    ofstream  availTemp;
    availTemp.open("availtemp.txt");
    cout << "\n\n\n\n";
    cout << endl;

    cust[custCount].id = custCount() + 1001;
    ofs << cust[custCount()].id;
    ofs << ";";

    cout << "\n\n";
    cout <<  "\m\t | \t\t\t\t\t Please enter the data below: " << endl;

    cout << "\n\t |\t\t\t\t\t Name : ";
    cin >> ws;
    cin.getline(cust[custCount()].name, 100);
    ofs << Cust[custCount()].name<< ";";
    log << "\nNAME: " << cust[custCount()].name;

    cout << "\t | \t\t\t\t\t Phone NUmber : ";
    cin.getline(cust[custCount()].phone, 15);
    ofs << cust[custCount()].phone;
    ofs << ";";
    log << "\nPHONE: " << cust[custCount()].phone;

    cout << "\t | \t\t\t\t\t IC : ";
    cin.getline(cust[custCount()].ic, 15);
    ofs << cust[custCount()].ic;
    ofs << ";";
    log << "\nIC: " << cust[custCount()].ic;

    cout << "\t | \t\t\t\t\t Address : ";
    cin.getline(cust[custCount()].address, 1500);
    ofs << cust[custCount()].address;
    

    ofs.close();

    system("cls");

    int tempCust, hour;
    char carSelect[10];
    tempCust = custCount() - 1;

    cout << "\n\n\n\n";
    art();
    cout << endl;

    cout << "\n\t |\t\t\tWELCOME ";
    cout << cust[tempCust].name;
    cout << "\t | \tID";
    cout << cust[tempCust].id;
    cout << "\n\n";

    dispAvailCar();

    cout << "\n\n\t | \tPlease select car");
    cout << "\n\t |\tPleate Number: ";
    cint >> ws;
    cin.getline(carSelect, 10);

    int x = countAvail();

	for(int i = 0; i < countAvail(); i++)
	{
		if (strcmp(carSelect,avail[i].plate_num) != 0)
		{
			availTemp << avail[i].plate_num;
			availTemp << " ";
			availTemp << avail[i].brand;
			availTemp << " ";
			availTemp << avail[i].model;
			availTemp << " ";
			availTemp << avail[i].capacity;
			availTemp << " ";
			availTemp << avail[i].colour;
			availTemp << " ";
			availTemp << avail[i].rate_per_hour;
			availTemp << " ";
			availTemp << avail[i].rate_per_half;
			availTemp << " ";
			availTemp << avail[i].rate_per_day;
			availTemp << " ";
			availTemp << avail[i].transmission;
			if(i != countAvail())
			{
				availTemp<<endl;
			}
			
			
		}
	}

    ofs.close();

    remote("available.txt");

    rename("availtemp.txt", "available.txt");

    cout << "\t | \tHousrs of rent: ";
    cint >> hour;
    int j;
    for(int i = 0; i < carCount(); i++)
    {
        if(strcmp(carSelect, rent[i].plate_num) == 0)
        {
            j = i;
            rate(hour, j);
            log<< "\nCAR: " < rent[i].plate_num;
            log << "\nBRAND: " << rent[i].brand;
            log << "\nMODEL: " << rent[i].model;
            log << "\nHOUR: " << hour;
            log << "\nPAYMENT: " << rate(hour, j);
        }
    }

    cout << "\n\t | \tPrice for" << hour << "hours of rent: RM";
    cout << rate(hour, j);

    log << "\nDATE: " << currentDateTime();
    log << "\n====================================";
    log.close();
    availTemp.close();
    availCar();

    Sleep(5000);
    system("cls");
    menu();

}

void newCarData()
{
    cout << "\n\n";
    art();
    cout << endl;

    ofstream ofs;
    ofs.open("car rental.txt", fstream::app);
    ofs<< endl;

    int newCar = carCount(); + 1;
    cout << "\n\n";
    cout << "\n\t |\t\t\t\t\t Please enter the car data below: "<< endl;
    cout << "\n\t |\t\t\t\t\t Plate Number : ";
    cin >> ws;
    cin.getline(rent[newCar].plate_num, 10);
    ofs << rent[newCar].plate_nmu;
    ofs << "";

    cout << "\t |\t\t\t\t\t Brand : ";
    cin.getline(rent[newCar].brand, 20);
    ofs << rent[newCar].brand;
    ofs << " ";

    cout << "\t |\t\t\t\t\t Model : ";
    cin.getline(rent[newCar].model, 20);
    ofs << rent[newCar].model;
    ofs << " ";

    cout << "\t |\t\t\t\t\t Capacity : ";
    cin  >> rent[newCar].capacity;
    ofs << rent[newCar].capacity;
    ofs << " ";

    cout << "\t |\t\t\t\t\t Colour : ";
    cin >> ws;
    cin.getline(rent[newCar].colour, 20);
    ofs << rent[newCar].colour;
    ofs << " ";
    

    cout << "\t |\t\t\t\t\t Rate Per Hour : ";
    cin >> rent[newCar].rate_per_hour;
    ofs << rent[newCar].rate_per_hour;
    ofs << " ";

    cout << "\t |\t\t\t\t\t Rate Per 12 Hour : ";
    cin >> rent[newCar].rate_per_half;
    ofs  << rent[newCar].rate_per_half;
    ofs << " ";

    cout << "\t |\t\t\t\t\t Rate Per 24 Hour: ";
    cin >> rent[newCar].rate_per_day;
    ofs << rent[newCar].rate_per_day;
    ofs << " ";

    cout << "\t |\t\t\t\t\t Tranmission (A/M) : ";
    cin >> ws;
    cin.getline(rent[newCar].transmission, 6);
    ofs << rent[newCar].transmission;

    ofs.close();
    system("cls");

    carData();
    admin();
}

void availCar()
{
    ifstream ifs;
    ifs.open("available.txt");
    int carNum = 0;

    while(!ifs.eof())
    {
        ifs.getline(avail[carNum].plate_num, 10, " ");
        ifs.getline(avail[carNum].brand, 20, '');
        ifs.getline(avail[carNum].model, 20, ' ');
        ifs >> avail[carNum].capacity;
        ifs.ignore();
        ifs.getline(avail[carNum].colour, 20, '');
        ifs >> avail[carNum].rate_per_hour;
        ifs.ignore();
        ifs>>avail[carNum].rate_per_half;
        ifs.ignore();
        ifs >> avail[carNum].rate_per_day;
        ifs.ignore();
        ifs.getline(avail[carNum].transmission, 6);
        carNum++;
        ifs>>ws;
    }

    ifs.close();
}

void resetAvail()
{
    Boarder();
    ofstream ofs;
    osf.open("temp2.txt");

    for(int i = 0; i < carCount(); i++)
    {
        ofs << rent[i].plate_num;
        ofs << " ";
        ofs << rent[i].brand;
        ofs << " ";
        ofs << rent[i].model;
        ofs << " ";
        ofs << rent[i].capacity;
        ofs << " ";
        ofs << rent[i].colour;
        ofs << " ";
        ofs << rent[i].rate_per_hour;
        ofs << " ";
        ofs << rent[i].rate_per_day;
        ofs << " ";
        ofs << rent[i].transmission;
        if(i != carCount())
        {
            ofs << endl;
        }
    }

    ofs.close();

    remove("available.txt");
    rename("temp2.txt"."available.txt");

    admin();
}

void newUserPass()
{
    Boarder();
    ofstream ofs;
    ofs.open("UserPass.txt", fstream::app);

    userPass[countUser()].ID = countUser() + 1;

    string passowrd;
    char c;
    gotoxy(40, 20);
    cout << "\n\n\n\n\t |\t\t\tID(DEFAULT): " << userPass[countUser()].ID;
    cout << "\n\t |\t\t\tADD PASSWORD: ";
    while(c != '\r')
    {
        c = getch();
        if(c == 0)
        {
            switch(getch())
            {
                default:
                    break;
            }
        }
        else if(c == '\b')
        {
            if(passowrd.size() != 0)
            {
                password.erase(password.size() - 1, 1);
            }
        }
        continue;
    }

    strcpy(userPass[countUser()].passWord, password.c_str());

    ofs << userPass[countUser()].ID;
    ofs << ";";
    ofs << userPass[countUser()].passWord;
    ofs << endl;

    system("cls");
    admin();
}

void showCarData()
{
    int x;
    cout << "\n\n";
    cout << endl;

    cout << "\t | Plate Number \tBrand\t Model\tCapacity Colour Rate Per Hour Rate Per 12 Hour Rate Per 24 Hour Transmission" << endl;
    cout << "\t ============================================================================================================" << endl;
	for (int i = 0; i < carCount(); i++)
	{
		cout << "\t  |  " << rent[i].plate_num << "\t\t" << rent[i].brand << "\t " << rent[i].model << "\t   " << rent[i].capacity << "\t     "
			 << rent[i].colour << "\t  " <<rent[i].rate_per_hour << "\t\t    " << rent[i].rate_per_half << "\t\t    " << rent[i].rate_per_day 
			 << "\t\t       " << rent[i].transmission << endl;
	}
	cout << "\n\n";
	cout<<"\n\t  |\t\t\t\t\t  1. BACK";
	cout<<"\n\t  |\t\t\t\t\t  2. MAIN MENU"<<endl<<"\n\n";
	cout<<"\t  |\t\t\t\t\tINPUT :";
	cin >> x;

    system("cls");
    if (x == 1)
    {
        admin();
    }

    if( x ==2)
    {
        menu();
    }
}

void carData()
{
    ifstream ifs;
    ifs.open("car rental.txt");
    int carNum = 0;

    while(!ifs.eof())
    {
        ifs.getline(rent[carNum].plate_num, 10, "");
        ifs.getline(rent[carNum].brand, 20, "");
        ifs.getline(rent[carNum].model, 20, " ");
        ifs >> rent[carNum].capacity;
        ifs.ignore();
        ifs.getline(rent[carNum].colour, 20, " ");
        ifs >> rent[carNum],rate_per_hour;
        ifs.ignore();
        ifs >> rent[carNum].rate_per_half;
        ifs.ignore();
        ifs >> rent[carNum].rate_per_day;
        ifs.ignore();
        ifs.getline(rent[carNum].transmission, 6);
        carNum++;
        ifs >> ws;
    }

    ifs.close();
}

void admin()
{
    int x;
    cout << "\n\n\n\n";
    art();
    cout << endl;

	cout<<"\n\t  |\t\t\t\t\t\t\t  1. ADD ADMIN";
	cout<<"\n\t  |\t\t\t\t\t\t\t  2. SHOW DATA";
	cout<<"\n\t  |\t\t\t\t\t\t\t  3. ADD CAR";
	cout<<"\n\t  |\t\t\t\t\t\t\t  4. DELETE CAR";
	cout<<"\n\t  |\t\t\t\t\t\t\t  5. RESET AVAILABLE CAR";
	cout<<"\n\t  |\t\t\t\t\t\t\t  6. LOG OFF"<<endl<<"\n";
	cout<<"\t  |\t\t\t\t\t\t\tINPUT :";
	cin>>x;

    system("cls");

    if(x == 6)
    {
        load_EXIT();
        menu();
    }

    else if(x == 2)
    {
        showCarData();
    }

    else if(x == 3)
    {
        newCarData();
    }

    else if(x == 4)
    {
        delCar();
    }
    else if(x == 1)
    {
        newUserPass();
    }

    else if(x ==5)
    {
        system("cls");
    }
    resetAvail();
}

void user()
{
    int x;
    art();
    cout << endl;

    cout << "\n\t |\t\t\t\t\t\t\t 1.NEW";
    cout << "\n\t |\t\t\t\t\t\t\t 2.EXISTING";
    cout << "\t\t |\t\t\t\t\t\t\t 3.MAIN MENU";
    cout << "\n\n\t |\t\t\t\t\t\t\tINPUT: ";
    cin >> x;

    system("cls");
    if(x == 1)
    {
        newCustData();
    }
    else if(x == 2)
    {
        system("cls");
        load_UPDATE();
        existingCust();
    }
    else if(x == 3)
    {
        menu();
    }
}

void menu()
{
    int x;
    art();
    
    cout << endl;

    cout << "\n\t |\t\t\t\t\t\t\t 1.ADMIN";
    cout << "\n\t |\t\t\t\t\t\t\t 2. USER";
    cout << "\n\t |\t\t\t\t\t\t\t 3.T%c";
    cout << "\n\t |\t\t\t\t\t\t\tINPUT: ";
    cin >> x;

    system("cls");
    if(x == 2)
    {
        user();
    }
    else if(x == 1)
    {
        password();
    }

    if(x == 3)
    {
        tNc();
        getch();
    }

    if(x == 5)
    {
        time();
    }
    else if(x == 4)
    {
        cout << "\n\n\n\n";
        exitArt();
        Sleep(1000);
        exit(0);
    }
    else if(x == 6)
    {
        fullscreen();
        menu();
    }
}