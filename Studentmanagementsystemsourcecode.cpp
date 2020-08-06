//Student management system through file handling:
#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<string.h>
#define ENTER 13
#define TAB 9
#define BKSP 8
#define SPACE 32


using namespace std;
//Class declare student
class Student
{
 string user;//Admin name
 string sessionid,pass;//Admin id,password
 int admno,std;
 char name[20],gender,Email[100];
 string Department;
 string currentid;
 float marks;
 float percentage;
 string username;//temporary variable for holding username
 public:
  //function declaration:
  void accountinfo();//Admin accountinfo
  void regis();//registrtation for each admin
  void loginscreen(); //mainscreen
  void project(string,string);//menu
  void getData();
  void showData();
  void check(int);
  void checksession(string);
  void admin();    
  int getAdmno(){return admno;}
  string getsessionid(){return sessionid;}
  string getpass(){return pass;}
}s;
//function definition:
void Student::loginscreen()//Main screen declaration after loading:
{
  int n;
  cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\n*****************************-:WELCOME TO STUDENT MANAGEMENT SYSTEM:-****************************";
  cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\n1>LOGIN";
  cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n2>REGISTER";
  cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n3>EXIT";
  cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\n***************************************************************************************************";
  cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\nEnter your chocie:";
  cin>>n;
  switch(n)
  {

  case 1:admin();
         break;
  case 2:regis();
         break;
  case 3:system("cls");
         cout<<"\n Thankx for using this program:)";
         exit(0);

    default:cout<<"\n Wrong input";
  }
}

void Student::admin()//Login validation userlogin page:-
{ 
  int login=0,i=0;
  int count=0;
  string temp;
  string temppass;
  string username;
  char password[100],ch;
 do
 {  
  system("cls");
  cout<<"\t\t\t\t************************** User Login****************************************\n";
  cout<<"\t\t\t\t Enter your userid:";
  cin>>temp;
  cout<<"\t\t\t\t Enter your password:";
  while(1)//using password encryption
 {
   ch=getch();
   if(ch==ENTER)
   {
       password[i]='\0';
       break;
   }
   else if(ch==BKSP)
  {
   if(i>0)
   {
       i--;
       cout<<"\b\b";
   }
 }
  else if(ch==TAB || ch==SPACE)
  {
   continue;
  }
  else
  {
     password[i]=ch;
     i++;
     cout<<"*";
  }
}
  temppass=string(password);
  cout<<"\n \tWait some moments validating......";
  Sleep(500);
  int  flag=0;
  ifstream fin;
  fin.open("Admin.dat",ios::in|ios::binary);
  while(fin.read((char*)&s,sizeof(s)))
  { 
   if(temp==sessionid && temppass==pass)
   {
    username=user;
    flag++;
   }
  }
  fin.close();
  if(flag>0)
   {
    system("cls"); 
    cout<<"\n \n \n .........You are redirected to main menu Wait:.........................";
    cout<<"\n\n";
    for(int i=0;i<=50;i++)
    {
      Sleep(100);
      cout<<char(219);
    }
    system("cls"); 
    project(temp,username);
   }
  else
  {
    cout<<"\n \tInvalid username and password";
    cout<<"\n \t Try again";
    login++;
    if(login==2)
   {
     int n;
     cout<<"\n\n \t if you not register press 1 for register:";
     cin>>n;
      if(n==1)
     {
       regis();
     }
     
   }
   if(login>=5)
   {
     system("cls");
     cout<<"\n You have too many attempts now the program terminate:";
     exit(0); 
   }
  
 }
 }
 while(1);
}

void Student::regis()//Registration page code:
{
 system("cls");
 cout<<" \n Redirected to Registration page:";
 cout<<"\n \n";
 for(int i=0;i<=50;i++)
 {
   Sleep(100);
   system("color 49");
   cout<<char(219);
 } 
 system("cls");
 system("color 1F");
 string local;
 int press;
 cout<<"\n Press 1 for main menu:";
 cout<<"\n Press 2 Continue for registration page:";
 cin>>press;
 if(press==1)
 { 
   loginscreen(); 
 }
else if(press==2)
  {
  cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n*************************REGISTRATION********************************";
  cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\nEnter your Session id:";
  cin>>sessionid;
  local=sessionid;
  checksession(local);
  sessionid=local;
  cout<<"\t\t\t\t\t\t\t\t\nEnter your name:";
  cin>>user;
  cout<<"\t\t\t\t\t\t\t\t\nEnter your gender(M/F):";
  cin>>gender;
  cout<<"\t\t\t\t\t\t\t\t\nEnter your Department:";
  cin>>Department;
  cout<<"\t\t\t\t\t\t\t\t\nEnter your Email(Excluded spaces):";
  cin>>Email;
  cout<<"\t\t\t\t\t\t\t\t\nEnter your password:";
  cin>>pass;
  ofstream fout;
  fout.open("Admin.dat",ios::binary|ios::out|ios::app);
  fout.write((char*)&s,sizeof(s));
  fout.close();
  cout<<"\n\nRegistration Successfull....\n";
  cout<<"\n Press any key to continue";
  getch();
  loginscreen();
  }
 else
 {
   exit(0);
 }
}

void Student::checksession(string local)//this code checks the existing session or admin if exist then page redirect to mainscreen:
{

int  flag=0;
 ifstream fin;
 fin.open("Admin.dat",ios::in|ios::binary);
 while(fin.read((char*)&s,sizeof(s)))
 {
  if(local==getsessionid())
  {
   cout<<"this session id already present:\n";
   cout<<"try again"<<endl;
   cout<<"press any key to continue";
   getch();
   flag++;
   fin.close();
   loginscreen();
  }
 }
 fin.close();  
}

void read(string n)//read function to read accountinfo of admin
{
  system("color 4A");
  cout<<"\n \n \n@@@@#####***Fetching Data Wait..................";
  cout<<"\n \n";
       for(int i=0;i<=50;i++)
         {
           Sleep(100);
           system("color 9");
           cout<<char(219);
         }
  system("cls");
  ifstream fin;
  fin.open("Admin.dat",ios::in|ios::binary);
  while(fin.read((char*)&s,sizeof(s)))
  {
    if(n==s.getsessionid())
    {
    s.accountinfo();
    }
  }
 fin.close();
}

void Student::accountinfo()//account info page code:
{
  cout<<"\n***************************Account info*************************************";
  cout<<"\t\t\t\t\t\t\t\t\n Your session id:"<<sessionid<<endl;
  cout<<"\t\t\t\t\t\t\t\t\n Your name is:"<<user<<endl;
  cout<<"\t\t\t\t\t\t\t\t\n Your gender is:"<<gender<<endl;
  cout<<"\t\t\t\t\t\t\t\t\n Your Department is:"<<Department<<endl;
  cout<<"\t\t\t\t\t\t\t\t\n Your Email is:"<<Email<<endl;
  cout<<"\t\t\t\t\t\t\t\t\n Your password is:"<<pass<<endl;
}
//Admin function completed:

/*Student details function start*/
void Student::getData()//this function takes student details:
{
  cout<<"\n\nEnter Student Details......\n";
  cout<<"Enter Admission No.     : "; cin>>admno;
  int copy;
  copy=admno;
  check(admno);
  admno=copy;
  cout<<"Enter Full Name         : "; cin.ignore(); cin.getline(name,20);
  cout<<"Enter Gender (M/F)      : "; cin>>gender;
  cout<<"Enter Standard          : "; cin>>std;
  cout<<"Enter Marks (out of 500): "; cin>>marks;
  cout<<endl;
  percentage=marks*100.0/500.00;
}

void Student::check(int a)//this function checks the existing admission number before student details:
{
  int  flag=0;
  ifstream fin;
  fin.open("Students.dat",ios::in|ios::binary);
   while(fin.read((char*)&s,sizeof(s)))
  {
    if(a==s.getAdmno())
   {
    cout<<"Details of the student already present:\n";
    cout<<"try again"<<endl;
    fin.close();
    cout<<"press any key to continue";
    getch();
    getData();
    break;
   }
 }
 fin.close();
}

void Student::showData()
 {
   cout<<"\n\n.......Student Details......\n";
   cout<<"Admission No.     : "<<admno<<endl;
   cout<<"Full Name         : "<<name<<endl;
   cout<<"Gender            : "<<gender<<endl;
   cout<<"Standard          : "<<std<<endl;
   cout<<"Marks (out of 500): "<<marks<<endl;
   cout<<"Percentage        : "<<percentage<<endl;
   cout<<endl;
 }

void adddata()//this function add student details existing files:
{
 
 s.getData();
 ofstream fout;
 fout.open("Students.dat",ios::binary|ios::out|ios::app);
 fout.write((char*)&s,sizeof(s));
 fout.close();
 cout<<"\n\nData Successfully Saved to File....\n";

}

void displayData() //this function display the all student information:
{
 ifstream fin;
 fin.open("Students.dat",ios::in|ios::binary);
 while(fin.read((char*)&s,sizeof(s)))
 {
  s.showData();
 }
 fin.close();
 cout<<"\n\nData Reading from File Successfully Done....\n";
}

void searchData()//this function search the existing student desired user:
{
 int n, flag=0;
 ifstream fin;
 fin.open("Students.dat",ios::in|ios::binary);
 cout<<"Enter Admission Number you want to search : ";
 cin>>n;
 while(fin.read((char*)&s,sizeof(s)))
 {
  if(n==s.getAdmno())
  {
   cout<<"The Details of Admission No. "<<n<<" shown herewith:\n";
   s.showData();
   flag++;
  }
 }
 fin.close();
 if(flag==0)
  cout<<"The Admission No. "<<n<<" not found....\n\n";
 cout<<"\n\nData Reading from File Successfully Done....\n";
}

void deleteData()//this function delete the student details desired user:
{
 int n, flag=0;
 ifstream fin;
 ofstream fout,tout;

 fin.open("Students.dat",ios::in|ios::binary);
 fout.open("TempStud.dat",ios::out|ios::app|ios::binary);
 tout.open("TrashStud.dat",ios::out|ios::app|ios::binary);
 cout<<"Enter Admission Number you want to move to Trash : ";
 cin>>n;

 while(fin.read((char*)&s,sizeof(s)))
 {
  if(n==s.getAdmno())
  {
   cout<<"The Following Admission No. "<<n<<" has been moved to Trash:\n";
   s.showData();
   tout.write((char*)&s,sizeof(s));
   flag++;
  }
  else
  {
   fout.write((char*)&s,sizeof(s));
  }
 }
 fout.close();
 tout.close();
 fin.close();
 if(flag==0)
   cout<<"The Admission No. "<<n<<" not found....\n\n";
   remove("Students.dat");
   rename("tempStud.dat","Students.dat");
}

void getTrash()
{
 ifstream fin;
 fin.open("TrashStud.dat",ios::in|ios::binary);
 while(fin.read((char*)&s,sizeof(s)))
 {
  s.showData();
 }
 fin.close();
 cout<<"\n\nData Reading from Trash File Successfully Done....\n";
}

void modifyData()
{
 int n, flag=0, pos;
 fstream fio;

 fio.open("Students.dat",ios::in|ios::out|ios::binary);
 
 cout<<"Enter Admission Number you want to Modify : ";
 cin>>n;
 
 while(fio.read((char*)&s,sizeof(s)))
 {
  pos=fio.tellg();
  if(n==s.getAdmno())
  {
   cout<<"The Following Admission No. "<<n<<" will be modified with new data:\n";
   s.showData();
   cout<<"\n\nNow Enter the New Details....\n";
   s.getData();
   fio.seekg(pos-sizeof(s));
   fio.write((char*)&s,sizeof(s));
   flag++;
  }
 }
 fio.close();
 
 if(flag==0)
  cout<<"The Admission No. "<<n<<" not found....\n\n";
}

//Menu functions which shows various options:
void  Student::project(string currentid, string username)
{
 int ch;
 do
 {
  system("cls");
  system("color 5F");
  cout<<"\t\t\t\t\t\t\t*********************STUDENT MANAGEMENT SYSTEM************************\n";
  cout<<"\t\t\t\t\t\t\t======================================================================\n";
  cout<<"\t\t\t\t\t\t\tWELCOME BACK::"<<username<<"\tSession id::"<<currentid<<endl;
  cout<<"\t\t\t\t\t\t\t0> Back to main menu\n"<<endl;
  cout<<"\t\t\t\t\t\t\t1> Write Data to File\n"<<endl;
  cout<<"\t\t\t\t\t\t\t2> Read Data From File\n"<<endl;
  cout<<"\t\t\t\t\t\t\t3> Search Data From File\n"<<endl;
  cout<<"\t\t\t\t\t\t\t4> Delete Data From File\n"<<endl;
  cout<<"\t\t\t\t\t\t\t5> Get Deleted Records from Trash file\n"<<endl;
  cout<<"\t\t\t\t\t\t\t6> Modify Data in File\n"<<endl;
  cout<<"\t\t\t\t\t\t\t7>Your account info:\n"<<endl;
  cout<<"\t\t\t\t\t\t\t==========================================================================\n";
  cout<<"\t\t\t\t\t\t\tEnter your choice  : ";
  cin>>ch;
  system("cls");
  switch(ch)
  {
   case 1: adddata(); break;
   case 2: displayData(); break;
   case 3: searchData(); break;
   case 4: deleteData(); break;
   case 5: getTrash(); break;
   case 6: modifyData(); break;
   case 7:read(currentid); break;
   case 0:loginscreen();
          break;

   default:cout<<"please enter a valid number";
  }
  system("pause");
 }while(1);
}

int main()//Main function::
{        
         system("color 1F");
         cout<<"\npress any key to start:";
         getch();
         system("cls");   //this is program loading function:
         cout<<"\n\n\n.................................... Program being Loading .......................";
         cout<<"\n\n";
         for(int i=0;i<=50;i++)
         {
           Sleep(80);
           cout<<char(219);
         }
         system("cls");
         s.loginscreen();
         return 0;
}
