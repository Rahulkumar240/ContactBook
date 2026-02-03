#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

//colour code for terminal
void Red () {
    cout<<"\033[1;31m";
}

void Yellow () {
    cout<<"\033[1;33m";
}

void Blue () {
    cout<<"\033[1;34m";
}

void Green () {
    cout<<"\033[0;32m";
}

void Purple () {
    cout<<"\033[0;35m";
}

void White () {
    cout<<"\033[0;37m";
}

void Cyan () {
    cout<<"\033[0;36m";
}

void ResetTextColor () {
    cout<<"\033[0m";
}


class Contact {
    public:
        string name;
        string phoneNo;
        string emailId;

    void printContact(){
        Purple();
        cout<<"____________________________"<<endl;
        cout<<"Name               :"<<name<<endl;
        cout<<"Phone Number       :"<<phoneNo<<endl;
        cout<<"Email Id           :"<<emailId<<endl;
        ResetTextColor();
    }
};

class contactBook{
    private:
        vector<Contact> listofcontacts;
    protected:
        void storeContactInFile();
        void readContactFromFile();
    public:
        void mainMenu();
        void addNewContact();
        void viewAllContact();
        void searchContactByName();
        void deleteContactByName();
        void updateContact();

};

void contactBook::storeContactInFile(){
    ofstream fout("Contact.txt");
    if(fout.is_open()){
        
    for(const auto& Contact : listofcontacts){
        fout<<Contact.name<<"\n";
        fout<<Contact.phoneNo<<"\n";
        fout<<Contact.emailId<<"\n";
    }
    fout.close();
    }
    else{
        Red();
        cout<<"File Not Found!"<<endl;
        ResetTextColor();
    }
}

void contactBook::readContactFromFile(){
    ifstream fin("Contact.txt");
    if(fin.is_open()){
        Contact contact;
        listofcontacts.clear();

        while(getline(fin,contact.name)){
            getline(fin,contact.phoneNo);
            getline(fin,contact.emailId);

            listofcontacts.push_back(contact);
        }
        fin.close();
    }
    else{
        Red();
        cout<<"File Not Found!"<<endl;
        ResetTextColor();
    }
}

void contactBook::mainMenu(){
    int choice;
    readContactFromFile();
    cout<<"Welcome to Contact Book ☎︎"<<endl;

    do{
        Green();
        cout<<"_____________________________"<<endl;
        cout<<"1. Add New Contact"<<endl;
        cout<<"2. View All Contacts"<<endl;
        cout<<"3. Search Contact By Name"<<endl;
        cout<<"4. Delete Contact By Name"<<endl;
        cout<<"5. Update Contact"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;
        ResetTextColor();
        cin.ignore();
        system("cls");
        switch(choice){
            case 1:
            addNewContact();
            break;
            case 2:
            viewAllContact();
            break;
            case 3:
            searchContactByName();
            break;
            case 4:
            deleteContactByName();
            break;
            case 5:
            updateContact();
            break;
            case 6:
            cout<<"Exiting..."<<endl;
            storeContactInFile();
            break;
            default:
            Red();
            cout<<"Invalid Choice, please try again."<<endl;
            ResetTextColor();
        }
    }while(choice!=6);
}

void contactBook::addNewContact(){
    Contact newcontact;
    Blue();
    cout<<"__________________________"<<endl;
    cout<<"Enter Name              : ";
    getline(cin,newcontact.name);
    cout<<"Enter Phone Number      : ";
    getline(cin,newcontact.phoneNo);
    cout<<"Enter EmailId           : ";
    getline(cin,newcontact.emailId);
    ResetTextColor();
    listofcontacts.push_back(newcontact);
    Green();
    cout<<"Contact added successfully!"<<endl;
    ResetTextColor();
}

void contactBook::viewAllContact(){
    if(listofcontacts.empty()){
        Red();
        cout<<"No Contacts available! "<<endl;
        ResetTextColor(); 
    }
    else{
        int count = 1;
        for(auto& contact : listofcontacts){
            Yellow();
            cout<<endl;
            cout<<"Contact No      : "<<setfill('0')<<setw(2)<<count++<<endl;
            contact.printContact();
        }
    }
}

void contactBook :: searchContactByName(){
    string name;
    cout<<"_____________________________"<<endl;
    cout<<"Enter the name to search : ";
    getline(cin,name);
    bool found = false;

    for(auto& Contact : listofcontacts){
        if(Contact.name == name){
            Contact.printContact();
            found = true;
            break;
        }
    }

    if(!found){
        Red();
        cout<<"Contact not found!"<<endl;
        ResetTextColor();
    }
}

void contactBook :: deleteContactByName(){
    string name;
    cout<<"_______________________________"<<endl;
    cout<<"Enter the name to delete : ";
    getline(cin,name);
    bool found = false;

    for(auto it = listofcontacts.begin();it != listofcontacts.end();++it){
        if(it->name == name){
            listofcontacts.erase(it);
            found = true;
            Green();
            cout<<"Contact Deleted successfully!"<<endl;
            ResetTextColor();
            break;
        }

        
    }
    if(!found){
            Red();
            cout<<"Contact Not Found!"<<endl;
            ResetTextColor();
        }
}

void contactBook :: updateContact(){
    string name;
    cout<<"________________________________"<<endl;
    cout<<"Enter the name to update : ";
    getline(cin,name);
    bool found = false;

    for(auto&  contact  : listofcontacts){
        if(contact.name == name){
            cout<<"Updating Contact... "<<endl;
            cout<<"Enter new PhoneNumber : ";
            getline(cin,contact.phoneNo);
            cout<<"Enter New EmailID  : ";
            getline(cin,contact.emailId);
            found = true;
            cout<<"Contact Updated Successfully!"<<endl;
            break;
        }
    }
    if(!found){
        Red();
        cout<<"Contact Not Found !"<<endl;
        ResetTextColor();
    }
}

int main(){
    contactBook cb;
    cb.mainMenu();
    return 0;
}