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
}