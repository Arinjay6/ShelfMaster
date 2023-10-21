#include<iostream>   /////////////////////////////////////////
#include<iomanip>    /////////////////////////////////////////
#include<string>     /////////////////////////////////////////
#include<fstream>    /////////////////////////////////////////
#include<conio.h>    //////////////////Header/////////////////
// #include<string.h>   //////////////////Files//////////////////
// #include<stdio.h>    /////////////////////////////////////////
#include <cstdlib>   /////////////////////////////////////////
#include <windows.h> /////////////////////////////////////////
using namespace std;
 
class Menu
{
    private:
    public:
    void mainMenu();
    void studentMenu();
    void bookMenu();
    void issueBook();
    void returnBook();
};
 
void Menu :: mainMenu()
{
    system("CLS");
    
    cout<<setw(35)<<"******************** MAIN MENU ***********************"<<endl<<endl;
    cout<<setw(38)<<"1. Student Menu\n"<<setw(35)<<"2. Book Menu\n"<<setw(36)<<"3. Issue Book\n"<<setw(37)<<"4. Return Book\n";
    cout<<setw(29)<<"5. Exit"<<endl;
}
void Menu :: studentMenu()
{
    system("CLS");
    system("color 8F");
    cout<<setw(35)<<"******************** student MENU ***********************"<<endl<<endl;
    cout<<setw(32)<<"1. New Entry\n"<<setw(35)<<"2. Modify Entry\n"<<setw(35)<<"3. Search Entry\n"<<setw(35)<<"4. Delete Entry\n";
    cout<<setw(43)<<"5. View Student Details\n"<<setw(46)<<"6. Go Back To Previous Menu"<<endl;
}
void Menu :: bookMenu()
{
    system("CLS");
    system("color 8F");
    cout<<setw(35)<<"******************** Book MENU ***********************"<<endl<<endl;
    cout<<setw(32)<<"1. New Entry\n"<<setw(35)<<"2. Modify Entry\n"<<setw(35)<<"3. Search Entry\n"<<setw(35)<<"4. Delete Entry\n";
    cout<<setw(44)<<"5. View All Book Details\n"<<setw(46)<<"6. Go Back To Previous Menu"<<endl;
}
class BookData
{
    public:
    char title[30];
    char author[30];
    char publisher[30];
    int status;
    int issuedRollNo;
    BookData()
    {
        status = 0;
        issuedRollNo = -9999;
    }
    void putbook_record();
};
 
class StudentData
{
    public:
    int rollNo;
    char name[30];
    char address[50];
    char branch[5];
    int status;
    char bookTitle[30];
    StudentData()
    {
        status = 0;
    }
    void put_record();
};
class Book
{
    public:
    void inputDetails();
    void modifyDetails();
    void searchDetails();
    void deleteDetails();
    void viewAllBookDetail();
};
void Book :: inputDetails()
{
    system("CLS");   
    fstream ofp;
    ofp.open("bookDatabase.txt", ios :: out  | ios :: app);
 
    if(!ofp)
    {
        cout<<"Unable to open file!!!!"<<endl;
        return;
    }
    BookData book;
    cout<<"Enter book title: ";
    cin>>book.title;
   cout<<"Enter Author name: ";
    cin>>book.author;
    cout<<"Enter book publisher: ";
    cin>>book.publisher; 
    ofp.write((char*)&book, sizeof(BookData));
    ofp.close();
}
 
void Book :: searchDetails()
{
    system("CLS");
    fstream file;
    file.open("bookDatabase.txt", ios :: in );
    if(!file)
    {
        cout<<"Unable to open file!!!!"<<endl;
        cin.get();
        cin.get();
        return;
    }
    BookData book;
    char title[30];
 
    cout<<"Enter title of the book you want to search for: ";
    cin>>title;
 
    while(file.read((char*)&book, sizeof(BookData)))
    {
        if(strcmp(book.title, title) == 0)
        {
            system("color 0C");
       cout<<"<------------------------------------------------------------------------------------------------------------------------------------------------------------------->"<<endl;
        cout<<"| Book's Name"<<"\t\t\t\t"<<"Book Author"<<"\t\t\t\t"<<"Book Publisher"<<"\t\t\t\t"<<"Issued Roll No.                             |"<<endl;
        cout<<"<------------------------------------------------------------------------------------------------------------------------------------------------------------------->"<<endl;
        
        if(book.status == 1)
        {
            cout<<book.title<<"\t\t\t\t\t"<<book.author<<"\t\t\t\t\t"<<book.publisher<<"\t\t\t\t\t"<<book.issuedRollNo<<endl;
        }
        else
        {
            cout<<book.title<<"\t\t\t\t\t"<<book.author<<"\t\t\t\t\t"<<book.publisher<<"\t\t\t\t\t"<<"None"<<endl;
        }
        cin.get();
        cin.get();
        getch();
        return;
        }
    }
    cout<<"Book not found"<<endl;
    cin.get();
    cin.get();
    getch();
    return;
}
 
void Book :: modifyDetails()
{
    system("CLS");
    fstream file;
    file.open("bookDatabase.txt",  ios :: in | ios :: out | ios :: ate);
 
    if(!file)
    {
        cout<<"Unable to open file!!!!"<<endl;
        return;
    }
    file.seekg(0,ios:: beg);
 
    BookData book;
    char title[25];
 
    cout<<"Enter book title of   the book you want to modify: ";
    cin>>title;
    while(file.read((char*)&book, sizeof(BookData)))
    {
        if(strcmp(book.title, title) == 0)
        {
            int position = (-1)*sizeof(BookData);
            file.seekp(position, ios :: cur);
            cout<<"Enter new book title: ";
            cin>>book.title;
            cout<<"Enter New author's name ";
            cin>>book.author;
            cout<<"Enter New book publisher ";
            cin>>book.publisher;
            file.write((char*)&book, sizeof(BookData));
            cout<<"Record updated";
            cin.get();
            cin.get();
            return;
        }
    }
    cout<<"Record not found";
    cin.get();
    cin.get();
    return;
}
 
void Book :: deleteDetails()
{
    system("CLS");
    fstream file, temp;
    file.open("bookDatabase.txt",  ios:: in);
    temp.open("temp.txt", ios:: out);
 
    char title[25];
    BookData book;
    int flag = 0;
 
    cout<<"Enter book title to remove: ";
    cin>>title;
    while(file.read((char*)&book, sizeof(BookData)))
    {
        if(strcmp(book.title, title) == 0)
        {
            flag++;
            continue;
        }
 
        temp.write((char*)&book, sizeof(BookData));
    }
     file.close();
     temp.close();
     remove("bookDatabase.txt");
     rename("temp.txt", "bookDatabase.txt");
     if(flag == 1)
     cout<<"Record deleted"<<endl;
     else
     cout<<"Record not found"<<endl;
     cin.get();
    cin.get();
    return;
}

 
void BookData :: putbook_record()
{
    if(status == 1)
    cout<<title<<"\t\t\t\t\t"<<author<<"\t\t\t\t\t"<<publisher<<"\t\t\t\t\t"<<issuedRollNo<<endl;
    else
    cout<<title<<"\t\t\t\t\t"<<author<<"\t\t\t\t\t"<<publisher<<"\t\t\t\t\t"<<"None"<<endl;
}
 
 void Book :: viewAllBookDetail()
{
    system("CLS");
    fstream ifp;
    BookData book;
    ifp.open("bookDatabase.txt", ios :: in );
    if(!ifp)
    {
        cout<<"Unable to open file!!!!"<<endl;
        return;
    }
    else
    {
        system("color 0C");
       cout<<"<------------------------------------------------------------------------------------------------------------------------------------------------------------------->"<<endl;
        cout<<"| Book's Name"<<"\t\t\t\t"<<"Book Author"<<"\t\t\t\t"<<"Book Publisher"<<"\t\t\t\t"<<"Issued Roll No.                             |"<<endl;
        cout<<"<------------------------------------------------------------------------------------------------------------------------------------------------------------------->"<<endl;
        ifp.read((char*)&book, sizeof(BookData));
        while(!ifp.eof())
        {
            book.putbook_record();
            ifp.read((char*)&book,sizeof(BookData));
        }
    }
    ifp.close();
    getch();
    return;
}
class  Student
{
    public:
    void inputDetails();
    void modifyDetails();
    void searchDetails();
    void deleteDetails();
    void viewAllStudentsDetail();
};
void Student :: inputDetails()
{
    system("CLS");
    fstream ofp, ifp;
    ofp.open("studentDatabase.txt", ios :: in | ios :: out | ios :: app );
 
    if(!ofp)
    {
        cout<<"Unable to open file!!!!"<<endl;
        return;
    }
    StudentData student;
    cout<<"Enter Student's roll no. : ";
    cin>>student.rollNo;
    int number = student.rollNo;
    // ofp.close();
    // StudentData student;
    // ofp.open("studentDatabase.txt", ios :: in );
    while(ofp.read((char*)&student, sizeof(StudentData)))
    {
        if(number == student.rollNo)
        {
            cout<<"\nRoll Number is already registerd";
            cin.get();
            cin.get();
            // cout<<"\nEnter the roll no. again"<<endl;
            // cin>>number;
            return;
        }
    }
    ofp.close();

     ofp.open("studentDatabase.txt", ios :: out | ios :: app );
    student.rollNo = number;
   
   cout<<"Enter Student's name : ";
    cin>>student.name;
    cout<<"Enter Student's address: ";
    cin>>student.address; 
    cout<<"Enter Student's branch: ";
    cin>>student.branch;
 
    cout<<"Record added to database!!!";
   
    ofp.write((char*)&student, sizeof(StudentData)); 
    ofp.close();
  cin.get();
  cin.get();
}
 
void Student :: modifyDetails()
{
    system("CLS");
    fstream fp;
    fp.open("studentDatabase.txt",  ios :: in | ios :: out | ios :: ate);
 
    if(!fp)
    {
        cout<<"Unable to open file!!!!"<<endl;
        return;
    }
    fp.seekg(0,ios:: beg);
 
    int target;
    cout<<"Enter Student's roll no. to modify: ";
    cin>>target;
 
    StudentData student;
 
    while(fp.read((char*)&student, sizeof(StudentData)))
    {
        if(target == student.rollNo)
        {
            int position = (-1)*sizeof(StudentData);
            fp.seekp(position, ios :: cur);
            cout<<"Enter  Student's new roll no. : ";
            cin>>student.rollNo;
            cout<<"Enter Student's new name: ";
            cin>>student.name;
            cout<<"Enter Student's new address: ";
            cin>>student.address; 
            cout<<"Enter Student's new branch: ";
            cin>>student.branch;
            
            fp.write((char*)&student, sizeof(StudentData));
            fp.close();
            cout<<"Record updated";
            return;
        }
    }
    cout<<"Roll number not found";
    return;
}
 
void Student :: searchDetails()
{
    system("CLS");
    fstream ifp;
    ifp.open("studentDatabase.txt", ios :: in );
    if(!ifp)
    {
        cout<<"Unable to open file!!!!"<<endl;
        return;
    }
    int target;
    cout<<"Enter roll no to search: ";
    cin>>target;
 
    StudentData student;
    while(ifp.read((char*)&student, sizeof(StudentData)))
    {
        if(target == student.rollNo)
        {
            system("color 0C");
            cout<<"<----------------------------------------------------------------------------------------->"<<endl;
        cout<<"| Student's Name"<<setw(25)<<"Roll no."<<setw(25)<<"Student's branch"<<setw(25)<<"Student's address |"<<endl;
        cout<<"<----------------------------------------------------------------------------------------->"<<endl;
        cout<<student.name<<setw(28)<<student.rollNo<<setw(25)<<student.branch<<setw(28)<<student.address<<endl;
        if(student.status == 1)
        {
            cout<<"Issued Book name is: "<<student.bookTitle<<endl;
        }
        else
        {
            cout<<"No book issued to this roll no. !!!!"<<endl;
        }
        cin.get();
        cin.get();
        return;
        }
    }
    cout<<"Record not found"<<endl;
    getch();
    return;
}
 
void StudentData :: put_record()
{
    
     if(status == 1)
    cout<<name<<"\t\t\t\t\t"<<rollNo<<"\t\t\t\t\t"<<branch<<"\t\t\t\t\t"<<address<<"\t\t\t\t"<<bookTitle<<endl;
    else
     cout<<name<<"\t\t\t\t\t"<<rollNo<<"\t\t\t\t\t"<<branch<<"\t\t\t\t\t"<<address<<"\t\t\t\t"<<"None"<<endl;
}   
 
 void Student :: viewAllStudentsDetail()
{
    system("CLS");
    fstream ifp;
    StudentData student;
    ifp.open("studentDatabase.txt", ios :: in );
    if(!ifp)
    {
        cout<<"Unable to open file!!!!"<<endl;
        return;
    }
    else
    {
        system("color 0C");
        cout<<"<------------------------------------------------------------------------------------------------------------------------------------------------------------------->"<<endl;
        cout<<"| Student's Name"<<"\t\t\t"<<"Roll no."<<"\t\t\t"<<"Student's branch"<<"\t\t\t"<<"Student's address"<<"\t\t\t"<<"Book Issued |"<<endl;
        cout<<"<------------------------------------------------------------------------------------------------------------------------------------------------------------------->"<<endl;
        ifp.read((char*)&student, sizeof(StudentData));
        while(!ifp.eof())
        {
            student.put_record();
            ifp.read((char*)&student,sizeof(StudentData));
        }
    }
    ifp.close();
    getch();
    return;
}
 
void Student :: deleteDetails()
{
    system("CLS");
    fstream file, temp;
    file.open("studentDatabase.txt", ios:: in );
    temp.open("temp.txt", ios:: out );
 
    
    StudentData student;
    int target, flag = 0;
 
    cout<<"Enter roll number to delete: ";
    cin>>target;
    while(file.read((char*)&student, sizeof(StudentData)))
    {
        if(student.rollNo == target)
        {
            flag++;
            continue;
        }
 
        temp.write((char*)&student, sizeof(StudentData));
    }
     file.close();
     temp.close();
     remove("studentDatabase.txt");
     rename("temp.txt", "studentDatabase.txt");
     if(flag == 1)
     cout<<"Record deleted"<<endl;
     else
     cout<<"Record not found"<<endl;
     cin.get();
    cin.get();
    return;
}
 
void Menu :: issueBook()
{
    system("CLS");
    fstream sp, bp;
    sp.open("studentDatabase.txt", ios:: in | ios::out | ios:: ate);
    bp.open("bookDatabase.txt", ios:: in | ios::out | ios:: ate);
    bp.seekg(0, ios :: beg);
    sp.seekg(0, ios :: beg);
    int rollNo, flagS = 0, flagB = 0, position;
    char title[30];
    StudentData student;
    BookData book;
 
    cout<<"Enter the roll no. to issue book: ";
    cin>>rollNo;
 
    while(sp.read((char*)&student, sizeof(StudentData)))
    {
        if(student.rollNo == rollNo)
        {
            position = (-1)*sizeof(StudentData);
            sp.seekp(position,ios::cur);
            flagS++;
            break;
        }
    }
    if(flagS != 1)
    {
        cout<<"Record not found!"<<endl;
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }
    cout<<"Enter the book you want to issue: ";
    cin>>title;
    while(bp.read((char*)&book, sizeof(BookData)))
    {
        if(strcmp(book.title, title) == 0)
        {
            position = (-1)*sizeof(BookData);
            bp.seekp(position, ios :: cur);
            flagB++;
        
            break;
        }
    }
 
    if(flagB!= 1)
        {
        cout<<"Record not found!"<<endl;
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }
    if(student.status != 1 && book.status != 1)
    {
        strcpy(student.bookTitle, title);
        student.status = 1;
        book.status = 1;
        book.issuedRollNo = student.rollNo;
        sp.write((char*)&student, sizeof(StudentData));
        bp.write((char*)&book, sizeof(BookData));
        sp.close();
        bp.close();
 
    }
    else
    {
        if(student.status == 1)
        {
            cout<<"Student account is full!!!!"<<endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
        }
        else
        {
            cout<<"Book is already issued!!!!"<<endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
        }
    }
    
}
 
void Menu :: returnBook()
{
    system("CLS");
    fstream sp, bp;
    sp.open("studentDatabase.txt", ios:: in | ios::out | ios:: ate);
    bp.open("bookDatabase.txt", ios:: in | ios::out | ios:: ate);
    bp.seekg(0, ios :: beg);
    sp.seekg(0, ios :: beg);
    int rollNo, flagS = 0, flagB = 0, position;
    char title[30];
    StudentData student;
    BookData book;
 
    cout<<"Enter the roll no. to return a book: ";
    cin>>rollNo;
 
    while(sp.read((char*)&student, sizeof(StudentData)))
    {
        if(student.rollNo == rollNo)
        {
            position = (-1)*sizeof(StudentData);
            sp.seekp(position,ios::cur);
            flagS++;
            break;
        }
    }
    if(flagS != 1)
    {
        cout<<"Record not found!"<<endl;
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }
    
    while(bp.read((char*)&book, sizeof(BookData)))
    {
        if(strcmp(book.title, student.bookTitle) == 0)
        {
            position = (-1)*sizeof(BookData);
            bp.seekp(position, ios :: cur);
            flagB++;
            break;
        }
    }
 
    if(flagB!= 1)
        {
        cout<<"Record not found!!!!!!!"<<endl;
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }
    if(student.status == 1 && book.status == 1)
    {
        student.status = 0;
        book.status = 0;
        book.issuedRollNo = -9999;
        sp.write((char*)&student, sizeof(StudentData));
        bp.write((char*)&book, sizeof(BookData));
        sp.close();
        bp.close();
 
    }
    else
    {
        if(student.status == 0)
        {
            cout<<"Student account is full!!!!"<<endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
        }
        else
        {
            cout<<"Book is already issued!!!!"<<endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
        }
    }
    
}
 
int main()
{
    Menu menu;
    int quit = 0;
    char choice[3];
    system("CLS");
    string welcome = " Welcome to LIBRARY... ";
        for(int i = 0; i < 20; i++)
        {
            Sleep(101);   //to suspend its execution temporarily for a period of time
            cout << "<";
        }
        for(int i = 0; i < welcome.length(); i++)
        {
            Sleep(100);
            cout << welcome[i];
        }
 
        for(int i = 0; i < 20; i++)
        {
            Sleep(101);
            cout << ">";
        }
        cout << endl
             << endl
             << endl;
             cout<<"\nPress enter to continue";
             cin.get();
    while(!quit)
    {
        system("CLS");
        menu.mainMenu();
        cout<<setw(48)<<"Please enter your choice: "<<endl;
        
        cin>>choice;
        
 
        switch(atoi(choice))/*using <cstdlib>*/
    
        {
            case 1:
            {
                system("clear");
                menu.studentMenu();
                cout<<setw(48)<<"Please enter your choice: "<<endl;
                cin>>choice;
                Student s1;
                switch(atoi(choice))
                {
                    case 1:
                    s1.inputDetails();
                    break;
                    case 2:
                    s1.modifyDetails();
                    break;
                    case 3:
                    s1.searchDetails();
                    break;
                    case 4:
                    s1.deleteDetails();
                    break;
                    case 5:
                    s1.viewAllStudentsDetail();
                    break;
                    case 6:
                    break;
                    default:
                    cout<<"Wrong input recieved!!!!"<<endl;
                }
                break;
            }
 
            case 2:
            {
                system("clear");
                menu.bookMenu();
                cout<<setw(48)<<"Please enter your choice: "<<endl;
                
                cin>>choice;
                Book b1;
                switch(atoi(choice))
                {
                    case 1:
                    b1.inputDetails();
                    break;
                    case 2:
                    b1.modifyDetails();
                    break;
                    case 3:
                    b1.searchDetails();
                    break;
                    case 4:
                    b1.deleteDetails();
                    break;
                    case 5:
                    b1.viewAllBookDetail();
                    break;
                    case 6:
                    break;
                    default:
                    cout<<setw(48)<<"Wrong input recieved!!!!"<<endl;
                }
                break;
            }
 
            case 3:
            menu.issueBook();
            break;
            case 4:
            menu.returnBook();
            break;
            case 5:
            quit++;
            break;
 
            default:
            cout<<setw(48)<<"Please Enter correct input"<<endl;
            cin>>choice;
 
        }
    }
 
    return 0;
}
