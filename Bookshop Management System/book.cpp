#include<iostream>
#include<conio.h>
#include<string.h>
#include<fstream>
#include<iomanip>
using namespace std;
class book
{
          char book_id[30];
          char book_name[50];
          char author_name[20];
          int copies;
          
  public:
  	static int count;
          void book_details()
          {
          		
                    cout<<"\nEnter The Book Number: ";
                    cin>>book_id;
                    cout<<"\nEnter The Name of The Book: ";
                   cin.ignore();
                    cin.getline(book_name,50);
                    cout<<"\nEnter The Author's Name: ";
                    cin.ignore();
                    cin.getline(author_name,50);
                    fflush(stdin);
           			cout<<"\nEnter No. Of Copies : ";
    				cin>>copies; 
					count=count+copies;         }
          void show_book()
          {
                    cout<<"\nBook Number: "<<book_id;
                    cout<<"\nBook Name: "<<book_name;
                    cout<<"\nAuthor's Name: "<<author_name;
                    cout<<"\nCOPIES : "<<copies<<"\n";
           //         cout<<"total copies"<<count<<"\n";                    

          }
          void modify_book()
          {
                    cout<<"\nBook number : "<<book_id;
                    cout<<"\nModify Book Name : ";
                    cin.ignore();
                    cin.getline(book_name,50);
                    cout<<"\nModify Author's Name: ";
                    cin.ignore();
                    cin.getline(author_name,50);
                    fflush(stdin);
       				cout<<"\nEnter No. Of Copies : ";
    				cin>>copies;
    				
          }
          
          char* getbooknumber()
          {
                    return book_id;
          }
          void report()
          {
		  cout<<book_id<<setw(30)<<book_name<<setw(30)<<author_name<<setw(30)<<copies<<endl;
		  }
};
int book::count=0;

fstream fp;
book bk;
void write_book()
{
          system("cls");
          int more_or_main;
          fp.open("bookshop.dat",ios::out|ios::app);
          do
          {
                    bk.book_details();
                    fp.write((char*)&bk,sizeof(book));
                    cout<<"\nPress 1 to add more books.";
                    cout<<"\nPress 2 to return to main menu.\n";
                    cout<<"Press 1 to add and Press 2 to go main menu: ";
                    cin>>more_or_main;
          }
		  while(more_or_main == 1);
          fp.close();
          
}
void display_book(char n[])
{
          system("cls");
          cout<<"\nBook Details\n";
          int check=0;
          fp.open("bookshop.dat",ios::in);
          while(fp.read((char*)&bk,sizeof(book)))
          {
                    if(strcmpi(bk.getbooknumber(),n)==0)
                    {
                               bk.show_book();
                              check=1;
                    }
          }
          fp.close();
          if(check==0)
                    cout<<"\n\nBook does not exist\n";
        getch();
}
 
void modify_book()
{
          system("cls");
          char n[20];
          int found=0;
          cout<<"\n\n\tModify Book";
          cout<<"\n\n\tEnter The book number: ";
          cin>>n;
          fp.open("bookshop.dat",ios::in|ios::out);
          while(fp.read((char*)&bk,sizeof(book)) && found==0)
          {
                    if(strcmpi(bk.getbooknumber(),n)==0)
                    {
                               bk.show_book();
                               cout<<"\nEnter The New Details of book"<<endl;
                               bk.modify_book();
                               int pos=1*sizeof(bk);
                              fp.seekp(pos,ios::cur);
                              fp.write((char*)&bk,sizeof(book));
                              cout<<"\n\n\tRecord Updated Successfully\n";
                              found=1;
                    }
          }
          fp.close();
          if(found==0)
                    cout<<"\n\n Record Not Found ";
          getch();
}
 
void delete_book()
{
          system("cls");
          char n[20];
          int flag=0;
          cout<<"\n\n\n\tDelete Book";
          cout<<"\n\nEnter The Book's number You Want To Delete: ";
          cin>>n;
          fp.open("bookshop.dat",ios::in|ios::out);
          fstream fp2;
          fp2.open("Temp.dat",ios::out);
          fp.seekg(0,ios::beg);
          while(fp.read((char*)&bk,sizeof(book)))
          {
                    if(strcmpi(bk.getbooknumber(),n)!=0)  
                    {
                               fp2.write((char*)&bk,sizeof(book));
                    }
                    else
                              flag=1;
          }
          fp2.close();
          fp.close();
          remove("bookshop.dat");
          rename("Temp.dat","bookshop.dat");
          if(flag==1)
                    cout<<"\n\n\tRecord Deleted";
          else
                    cout<<"\n\nRecord not found";
          getch();
}
 
void display_allb()
{
          system("cls");
          fp.open("bookshop.dat",ios::in);
          if(!fp)
          {
                    cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
                    getch();
                    return;
          }
          cout<<"\n\n\t\tBook List\n\n\n";
          cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author"<<setw(25)<<"Copies"<<endl<<"\n";
          while(fp.read((char*)&bk,sizeof(book)))
          {
                    bk.report();
          }
          cout<<"\n\nTotal no copies="<<bk.count<<"\n";
          fp.close();
          getch();
}
 
int main()
{
		
          int option = 0;
          for(;;)
          {
            cout<<"\t\t\nBook Shop Management System\n";
                cout<<"\n\t\tPress 1 to Insert Books";
                cout<<"\n\t\tPress 2 to Show all Books";
                cout<<"\n\t\tPress 3 to Check for avalibility";
                cout<<"\n\t\tPress 4 to Modify Books";
                cout<<"\n\t\tPress 5 to Delete Books";
                cout<<"\n\t\tPress 6 to Exit";
 				cout<<"\n\t\t\n";
 				cout<<"\n\t\tSelect Options: ";
 				cin>>option;
 			switch(option)
          	{
                    case 1:  system("cls");
                                         write_book();
                                                   break;
                               case 2: display_allb();
                                 break;
                    case 3:
                              char num[20];
                               system("cls");
                              cout<<"\n\n\tPlease Enter The book No. \n";
                              cin>>num;
                              display_book(num);
                              break;
                    case 4: modify_book();break;
                    case 5: delete_book();break;
                    case 6: exit(0);
                            break;
                    default:cout<<"\a";
          }     
           
          }
}
