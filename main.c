#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>                  //contains strcmp(),strcpy(),strlen(),etc
#include<ctype.h>                   //contains toupper(), tolower(),etc
#include<dos.h>                     //contains _dos_getdate
#include<time.h>
//#include<bios.h>

#define RETURNTIME 15

char catagories[][20]={"Computer","Electronics","Electrical","Civil","Mechanical","Instrumentation"};
void returnfunc(void);
void MainMenu(void);
void AddBooks(void);
void DeleteBooks(void);
void EditBooks(void);
void SearchBooks(void);
void IssueBooks(void);
void ViewBooks(void);
void CloseApplication(void);
int  getdata();
int  checkid(int);
int t(void);
//void show_mouse(void);
void Password();
void issuerecord();
void loaderanim();

//list of global files that can be acceed form anywhere in program
FILE *fp,*ft,*fs;


//COORD coord = {0, 0};
//list of global variable
int s;
char findbook;
char password[20]={"KirtiChaudhari95"};

/*void gotoxy (int x, int y)
{
coord.X = x; coord.Y = y; // X and Y coordinates
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}*/

struct meroDate
{
    int mm,dd,yy;
};
struct books
{
    int id;
    char stname[20];
    char name[20];
    char Author[20];
    int quantity;
    float Price;
    int count;
    int rackno;
    char *cat;
    struct meroDate issued;
    struct meroDate duedate;
};
struct books a;
int main()
{
    Password();
    getch();
    return 0;
}
void MainMenu()
{
    system("cls");
    int i;
    printf("\n***********MAIN MENU**************");
    printf("\n1. Add Books");
    printf("\n2. Delete books");
    printf("\n3. Search Books");
    printf("\n4. Issue Books");
    printf("\n5. View Book list");
    printf("\n6. Edit Book's Record");
    printf("\n7. Close Application");
    t();
    printf("\nEnter your choice:");
    switch(getch())
    {
    case '1':
    AddBooks();
    break;

    case '2':
    DeleteBooks();
    break;

    case '3':
    SearchBooks();
    break;

    case '4':
    IssueBooks();
    break;

    case '5':
    ViewBooks();
    break;

    case '6':
    EditBooks();
    break;

    case '7':
    {
        system("cls");
        printf("\n\t**************LIBRARY MANAGEMENT SYSTEM*********************");
        printf("\nExiting in 3 second...........>");
        Sleep(3000);
        exit(0);
    }

    default:
    {
        printf("\nWrong Entry!!Please re-entered correct option");
        if(getch())
        MainMenu();
    }
    }
}
//Function that will add the books//
void AddBooks(void)
{
    system("cls");
    int i;

    printf("\nSELECT CATEGOIES");
    printf("\n\t 1. Computer");
    printf("\n\t 2. Electronics");
    printf("\n\t 3. Electrical");
    printf("\n\t 4. Civil");
    printf("\n\t 5. Mechanical");
    printf("\n\t 6. Instrumentation");
    printf("\n\t 7. Back to main menu");
    printf("\nEnter your choice:");
    scanf("%d",&s);
    if(s==7)

    MainMenu() ;
    system("cls");
    fp=fopen("LibraryDB.dat","ab+");
    if(getdata()==1)
    {
        a.cat=catagories[s-1];
        fseek(fp,0,SEEK_END);
        fwrite(&a,sizeof(a),1,fp);
        fclose(fp);
        printf("\nThe record is successfully saved");
        printf("\nSave any more?(Y / N):");
    if(getch()=='n')
    MainMenu();
    else
    system("cls");
    AddBooks();
    }
}
void DeleteBooks()    //function that delete items from file fp
{
    system("cls");
    int d;
    char another='y';
    while(another=='y')  //infinite loop
    {
        system("cls");
        printf("\nEnter the Book ID to  delete:");
        scanf("%d",&d);
        fp=fopen("LibraryDB.dat","rb+");
        rewind(fp);
    while(fread(&a,sizeof(a),1,fp)==1)
    {
        if(a.id==d)
        {
            printf("\nThe book record is available");
            printf("\nBook name is %s",a.name);
            printf("\nRack No. is %d",a.rackno);
            findbook='t';
        }
    }
    if(findbook!='t')
    {
        printf("\nNo record is found modify the search");
        if(getch())
        MainMenu();
    }
    if(findbook=='t' )
    {
        printf("\nDo you want to delete it?(Y/N):");
        if(getch()=='y')
        {
            //Creating temporary file for deletion
            ft=fopen("Temporary.dat","wb+");
            rewind(fp);
    while(fread(&a,sizeof(a),1,fp)==1)
    {
    if(a.id!=d)
    {
        fseek(ft,0,SEEK_CUR);
        //Writing in temporary file whatever we delete//
        fwrite(&a,sizeof(a),1,ft);
    }
    }
    fclose(ft);
    fclose(fp);
    remove("LibraryDB.dat");
    //copy all item from temporary file to fp except that we want to delete//
    rename("Temporary.dat","LibraryDB.dat");
    fp=fopen("LibraryDB.dat","rb+");
    if(findbook=='t')
    {
        printf("\nThe record is successfully deleted");
        printf("\nDelete another record?(Y/N)");
    }
            }
    else
    MainMenu();
    fflush(stdin);
    another=getch();
    }
}
    MainMenu();
}
//Function that will perform SearchBooks
void SearchBooks()
{
        system("cls");
        int d;
        printf("\n*****************************SEARCH BOOKS*********************************");
        printf("\n\t\t\t\t 1. Search By ID");
        printf("\n\t\t\t\t 2. Search By Name");
        printf("\nEnter Your Choice");
        fp=fopen("LibraryDB.dat","rb+"); //open file for reading propose
        rewind(fp);   //move pointer at the begining of file
switch(getch())
{
    case '1':
    {
    system("cls");
    printf("\n****Search Books By Id****");
    printf("\nEnter the book id:");
    scanf("%d",&d);
    printf("\nSearching........");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
        if(a.id==d)
        {
            Sleep(2);
            printf("\nThe Book is available");
            printf("\nID:%d",a.id);
            printf("\nName:%s",a.name);
            printf("\nAuthor:%s ",a.Author);
            printf("\nQuantity:%d ",a.quantity);
            printf("\nPrice:Rs.%.2f",a.Price);
            printf("\nRack No:%d ",a.rackno);
            findbook='t';
        }
    }
//checks whether condition enters inside loop or not
    if(findbook!='t')
    {
        printf("\nNo Record Found");
    }
        printf("\nTry another search?(Y/N)");
        if(getch()=='y')
        SearchBooks();
        else
        MainMenu();
        break;
    }
case '2':
{
    char s[15];
    system("cls");
    printf("\n****Search Books By Name****");
    printf("\nEnter Book Name:");
    scanf("%s",s);
    int d=0;
    while(fread(&a,sizeof(a),1,fp)==1)
    {
        //To check whether a.name is equal to s or not
    if(strcmp(a.name,(s))==0)
    {
    printf("\nThe Book is available");
    printf("\nID:%d",a.id);
    printf("\nName:%s",a.name);
    printf("\nAuthor:%s",a.Author);
    printf("\nQuantity:%d",a.quantity);
    printf("\nPrice:Rs.%.2f",a.Price);
    printf("\nRack No:%d ",a.rackno);
    d++;
     }

}
    if(d==0)
    {
        printf("\nNo Record Found");
    }
    printf("\nTry another search?(Y/N)");
    if(getch()=='y')
    SearchBooks();
    else
    MainMenu();
    break;
    }
    default :
    getch();
    SearchBooks();
}
fclose(fp);
}
//Function that issues books from library
void IssueBooks(void)
{
    int t;
    system("cls");
    printf("\n********************************ISSUE SECTION**************************");
    printf("\n\t\t\t\t 1. Issue a Book");
    printf("\n\t\t\t\t 2. View Issued Book");
    printf("\n\t\t\t\t 3. Search Issued Book");
    printf("\n\t\t\t\t 4. Remove Issued Book");
    printf("\nEnter a Choice:");
switch(getch())
{
    case '1':  //issue book
    {
        system("cls");
        int c=0;
        char another='y';
        while(another=='y')
        {
            system("cls");
            printf("\n***Issue Book section***");
            printf("\nEnter the Book Id:");
            scanf("%d",&t);
            fp=fopen("LibraryDB.dat","rb");
            fs=fopen("IssueBook.dat","ab+");
            if(checkid(t)==0) //issues those which are present in library
            {
                printf("\nThe book record is available");
                printf("\nThere are %d un-issued books in library ",a.quantity);
                printf("\nThe name of book is %s",a.name);
                printf("\nEnter student name:");
                scanf("%s",a.stname);
//struct dosdate_t d; //for current date
//_dos_getdate(&d);
//a.issued.dd=d.day;
//a.issued.mm=d.month;
//a.issued.yy=d.year;

                printf("\nIssued date=%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
                printf("\nThe BOOK of ID %d is issued",a.id);
                a.duedate.dd=a.issued.dd+RETURNTIME;   //for return date
                a.duedate.mm=a.issued.mm;
                a.duedate.yy=a.issued.yy;
    if(a.duedate.dd>30)
    {
    a.duedate.mm+=a.duedate.dd/30;
    a.duedate.dd-=30;

    }
    if(a.duedate.mm>12)
    {
    a.duedate.yy+=a.duedate.mm/12;
    a.duedate.mm-=12;

    }
    printf("\nTo be return:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
    fseek(fs,sizeof(a),SEEK_END);
    fwrite(&a,sizeof(a),1,fs);
    fclose(fs);
    c=1;
    }
    if(c==0)
    {
        printf("\nNo record found");
    }
    printf("\nIssue any more(Y/N):");
    fflush(stdin);
    another=getche();
    fclose(fp);
}
break;
}
case '2':  //show issued book list
{
        system("cls");
        int j=4;
        printf("\n*******************************Issued book list*******************************\n");
        printf("\nSTUDENT NAME    \nCATEGORY    \nID    \nBOOK NAME    \nISSUED DATE    \nRETURN DATE");
        fs=fopen("IssueBook.dat","rb");
        while(fread(&a,sizeof(a),1,fs)==1)
        {
        printf("%s",a.stname);
        printf("%s",a.cat);
        printf("%d",a.id);
        printf("%s",a.name);
        printf("%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy );
        printf("%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
//struct dosdate_t d;
//_dos_getdate(&d);

// printf("Current date=%d-%d-%d",d.day,d.month,d.year);
        j++;
        }
        fclose(fs);
        returnfunc();
}
break;
case '3':   //search issued books by id
{
    system("cls");

        printf("\nEnter Book ID:");
        int p,c=0;
        char another='y';
    while(another=='y')
    {
        scanf("%d",&p);
        fs=fopen("IssueBook.dat","rb");
    while(fread(&a,sizeof(a),1,fs)==1)
    {
        if(a.id==p)
        {
        issuerecord();
        printf("Press any key.......");
        getch();
        issuerecord();
        c=1;
        }
    }
fflush(stdin);
fclose(fs);
if(c==0)
{
    printf("\nNo Record Found");
}
    printf("\nTry Another Search?(Y/N)");
    another=getch();
}
}
break;
case '4':  //remove issued books from list
{
    system("cls");
    int b;
    FILE *fg;  //declaration of temporary file for delete
    char another='y';
while(another=='y')
{
    printf("\nEnter book id to remove:");
    scanf("%d",&b);
    fs=fopen("IssueBook.dat","rb+");
while(fread(&a,sizeof(a),1,fs)==1)
{
    if(a.id==b)
    {
        issuerecord();
        findbook='t';
    }
if(findbook=='t')
{
    printf("\nDo You Want to Remove it?(Y/N)");
    if(getch()=='y')
    {
        fg=fopen("Records.dat","wb+");
        rewind(fs);
while(fread(&a,sizeof(a),1,fs)==1)
{
    if(a.id!=b)
    {
        fseek(fs,0,SEEK_CUR);
        fwrite(&a,sizeof(a),1,fg);
    }
}
fclose(fs);
fclose(fg);
remove("IssueBook.dat");
rename("Records.dat","IssueBook.dat");
printf("\nThe issued book is removed from list");
}
}
if(findbook!='t')
{
    printf("\nNo Record Found");
}
}
    printf("\nDelete any more?(Y/N)");
    another=getch();
}
}
default:
    printf("\nWrong Entry!!");
    getch();
    IssueBooks();
    break;
}
returnfunc();
}
void ViewBooks(void)  //show the list of book persists in library
{
    int i=0,j;
    system("cls");
    printf("\n************************BOOK LIST*****************************");
    printf("\nCATEGORY      ID     BOOK NAME      AUTHOR       QTY      PRICE     RACKNO");
    j=4;
    fp=fopen("LibraryDB.dat","rb");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
        printf("\n%s",a.cat);
        printf("%d",a.id);
        printf("%s",a.name);
        printf("%s",a.Author);
        printf("%d",a.quantity);
        printf("%.2f",a.Price);
        printf("%d",a.rackno);
        printf("\n\n");
        j++;
        i=i+a.quantity;
    }
printf("\nTotal Books =%d",i);
fclose(fp);
returnfunc();
}
void EditBooks(void)  //edit information about book
{
    system("cls");
    int c=0;
    int d,e;

    printf("\n****Edit Books Section****");
    char another='y';
while(another=='y')
{
system("cls");
    printf("\nEnter Book Id to be edited:");
    scanf("%d",&d);
    fp=fopen("LibraryDB.dat","rb+");
while(fread(&a,sizeof(a),1,fp)==1)
{
    if(checkid(d)==0)
    {
        printf("\nThe book is availble");
        printf("\nThe Book ID:%d",a.id);
        printf("\nEnter new name:");
        scanf("%s",a.name);
        printf("\nEnter new Author:");
        scanf("%s",a.Author);
        printf("\nEnter new quantity:");
        scanf("%d",&a.quantity);
        printf("\nEnter new price:");
        scanf("%f",&a.Price);
        printf("\nEnter new rackno:");
        scanf("%d",&a.rackno);
        printf("\nThe record is modified");
        fseek(fp,ftell(fp)-sizeof(a),0);
        fwrite(&a,sizeof(a),1,fp);
        fclose(fp);
        c=1;
}
if(c==0)
{
    printf("\nNo record found");
}
}
printf("\nModify another Record?(Y/N)");
fflush(stdin);
another=getch() ;
}
returnfunc();
}
void returnfunc(void)
{
    printf("\nPress ENTER to return to main menu");
    a:
    if(getch()==13) //allow only use of enter
    MainMenu();
    else
    goto a;
}
int getdata()
{
    int t;
    printf("\nEnter the Information Below");
    printf("\nCategory:");
    printf("%s",catagories[s-1]);

    printf("\nBook ID:\t");

    scanf("%d",&t);
if(checkid(t) == 0)
{
    printf("\nThe book id already exists\a");
    getch();
    MainMenu();
    return 0;
}
    a.id=t;
    printf("\nBook Name:");
    scanf("%s",a.name);

    printf("\nAuthor:");
    scanf("%s",a.Author);
    printf("\nQuantity:");
    scanf("%d",&a.quantity);
    printf("\nPrice:");
    scanf("%f",&a.Price);

    printf("\nRack No:");
    scanf("%d",&a.rackno);
    return 1;
}
int checkid(int t)  //check whether the book is exist in library or not
{
    rewind(fp);
    while(fread(&a,sizeof(a),1,fp)==1)
    if(a.id==t)
    return 0;  //returns 0 if book exits
    return 1; //return 1 if it not
}
int t(void) //for time
{
    time_t t;
    time(&t);
    printf("\nDate and time:%s\n",ctime(&t));
    return 0 ;
}
/*void show_mouse(void) //show inactive mouse pointer in programme
{
union REGS in,out;
       in.x.ax = 0x1;
       int86(0x33,&in,&out);
}*/
void Password(void) //for password option
{
    system("cls");
    char d[25]="Password Protected";
    char ch,pass[10];
    int i=0,j;
for(j=0;j<20;j++)
{
    Sleep(50);
    printf("*");
}
for(j=0;j<20;j++)
{
    Sleep(50);
    printf("%c",d[j]);
}
for(j=0;j<20;j++)
{
    Sleep(50);
    printf("*");
}
printf("\nEnter Password:");
while(ch!=13)
{
    ch=getch();
    if(ch!=13 && ch!=8){
    putch('*');
    pass[i] = ch;
    i++;
}
}
pass[i] = '\0';
if(strcmp(pass,password)==0)
{
    printf("\nPassword match");
    printf("\nPress any key to countinue.....");
    getch();
    MainMenu();
}
else
{
    printf("\nWarning!! Incorrect Password");
    getch();
    Password();
}
}
void issuerecord()  //display issued book's information
{
    system("cls");
    printf("\nThe Book has taken by Mr. %s",a.stname);
    printf("\nIssued Date:%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
    printf("\nReturning Date:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
}
/*void loaderanim()
{
int loader;
system("cls");
gotoxy(20,10);
printf("LOADING........");
printf("\n\n");
gotoxy(22,11);
for(loader=1;loader<20;loader++)
{
Sleep(100);printf("%c",219);}
}*/
//End of program
