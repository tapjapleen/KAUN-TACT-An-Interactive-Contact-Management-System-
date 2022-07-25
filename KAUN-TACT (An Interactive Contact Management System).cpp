#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;


class Contact{
    private:
    char FirstName[50], LastName[50], Address[50], Email[50];
    long long PhoneNumber;

    public:
    //Now we will create various functions which will be helpful in our project
    //The below given function is used to read data from the user
    void CreateContact(){
        cout <<"Enter your first name: ";
        cin >> FirstName;

        cout << "Enter your last name : ";
        cin >> LastName;

        cout << "Enter your phone number: ";
        cin >> PhoneNumber;

        cout << "Enter address: ";
        cin >> Address;

        cout << "Enter e-mail: ";
        cin >> Email;

    }
    //The below function will be used for displaying the data
    void ShowContact(){ 
        cout <<"Name: "<< FirstName <<" "<< LastName <<endl;
        
        cout <<"Phone Number: "<< PhoneNumber << endl;

        cout << "Address: "<< Address << endl;

        cout << "E-mail ID: "<< Email << endl;


    }
    /*Now we will write a function that will save the contact data in a file. 
    This is the reason why we did #include <fstream> */

    void WriteToFile(){

        char ch;
        ofstream f1; //Whenever we want to write something to a file we use ofstream
        //f1-object in ofstream

        f1.open("CMS.dat",ios::binary | ios:: app );//here we are using app because we want to append the data in the file and we dont want to over-write the data

        do{ 
        CreateContact();//Now we are letting the user enter some data

        f1. write(reinterpret_cast<char*>(this), sizeof(*this));
        cout << "Do you have next data? (y/n)";
        cin >> ch;
        }
        while (ch=='y');

        cout << "Contact has been successfully created.";

        f1.close();
        
    }
    //Now we shall make a function to read data from the file
    void ReadFromFile(){
        //if stream(input file stream is used now)

        ifstream f2;

        f2.open("CMS.dat", ios:: binary); //Here, we do not need append mode because now we are just reading the file
        cout << "\n====================================================================\n";
        cout << "LIST OF CONTACTS:";
        cout << "\n====================================================================\n";

        //While reading the contacts, we have to read the contacts till end of file is reached
        while (!f2.eof()){
            if (f2.read(reinterpret_cast<char*>(this), sizeof(*this))){
                ShowContact();
                cout << "\n====================================================================\n";
            }
        }
        f2.close();
    }
    //Now we will make a function that is used to search a contact from the file

    void SearchOnFile(){
        ifstream f3; 

        long long phone;

        cout << "Enter phone no. :";
        cin >> phone; //Searching in the file using phone number
        //In case same record found, it's displayed

        f3.open("CMS.dat", ios::binary );

        while (!f3.eof()){
            if (f3.read(reinterpret_cast<char*>(this), sizeof (*this))){
                if (phone== PhoneNumber){
                    ShowContact();
                    return;
                }
            }
        }
        cout << "\n\n No record found";
        f3.close();
        
    }

    //The below given function will be used to delete contact from the file
    void DeleteFromFile(){
        long long phone;

        int flag= 0;
        ofstream f4;
        ifstream f5;
        f5.open("CMS.dat", ios:: binary); //Read mode
        f4.open("temp.dat", ios::binary); //Write mode
        
        cout << "Enter phone number that you want to delete: ";
        cin >>phone;

        while (!f5.eof()){
            if (f5.read(reinterpret_cast<char*>(this), sizeof (*this))){
                if (phone != PhoneNumber){
                    f4.write(reinterpret_cast<char*>(this), sizeof (*this));
                }
                else {
                    flag=1;
                }  
            }
            f5.close();
            f4.close();
            remove("CMS.dat");
            rename("temp.dat", "CMS.dat");
            if (flag==1){
                cout << "\tContact Deleted..";
            }else {
                cout << "\tContact Not Found..";
            }
        }
    }
        //The below written function is used to edit a contact

        void editContact(){
            long long phone;
            fstream f6; //fstream contains both ofstream and ifstream ops

            cout << "Edit contact";
            cout << "\n====================================================================\n";
            cout << "Enter the phone number that you want to edit: ";
            cin >> phone;

            f6.open("CMS.dat", ios::binary|ios::out|ios::in);
            //out and in mode both as both reading, writing ops reqd

            while (!f6.eof()){
                if (f6.read(reinterpret_cast<char*>(this), sizeof (*this))){
                    if (phone== PhoneNumber){
                        cout << "Enter new record\n";
                        CreateContact();

                        long long int pos=-1*sizeof(*this);
                        f6.seekp(pos, ios::cur); //cursor moved to place where we need to edit 
                        f6.write(reinterpret_cast<char*>(this), sizeof(*this));
                        cout <<endl<< endl<<"\t Contact successfully updated!";
                        return;

                    }
                }
            }
            cout << "\n\nNo record  found";
            f6.close();

        }

};

//Main function
int main(){
    system("cls");//used to clear the screen
    system("Color 3F"); //Color XY, X- bg colour Y- text colour

    cout <<"\n\n\n\n\n\n\n\n\n\t\t *WELCOME TO KAUN-TACT (A CONTACT MANAGEMENT SYSTEM)* ";
    getch();//used to hold the screen for some time

    while (1){
        Contact c1;
        int choice;

        system("cls");
        system("Color 03");

        cout << "\nCONTACT MANAGEMENT SYSTEM";
        cout << "\n\nMAIN MENU";

        cout << "\n====================================================================\n";
        cout << "[1] Add a new contact\n";
        cout << "[2] List of all contacts\n";
        cout << "[3] Search for a contact\n";
        cout << "[4] Delete a contact\n";
        cout << "[5] Edit a contact\n";
        cout << "[0] Exit";
        cout << "\n====================================================================\n";

        cout << "Enter your choice (numeric): ";
        cin >> choice;

        switch(choice){
            case 1:
            system("cls");
            c1.WriteToFile();
            break;

            case 2:
            system("cls");
            c1.ReadFromFile();
            break;

            case 3:
            system("cls");
            c1.SearchOnFile();
            break;

            case 4:
            system("cls");
            c1.DeleteFromFile();
            break;

            case 5:
            system("cls");
            c1.editContact();
            break;

            case 0:
            system("cls");
            cout << "\n\n\n\t\t\tThank you for using KAUN-TACT."<<endl<< endl;

            exit(0);
            break; 


            default:
            continue;
        }

        int opt;
        cout << "\n\n..::Enter the choice:\n[1] Main Menu\t\t[0] Exit\n";
        cin >>opt;

        switch(opt){
            case 0:
            system("cls");
            cout << "\n\n\n\t\t\tThank you for using KAUN-TACT."<<endl<< endl;

            exit(0);
            break; 

            default:
            continue;

        }


    }
    return 0;



}
