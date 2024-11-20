#include <iostream>
#include "hashtable.h"
#include "passserver.h"

using namespace std;
using namespace cop4530;

void Menu();

int main()
{
    char choice = ' ';
	int hashSize;
	cout << "Enter preferred hash table capacity (integer): ";
	cin >> hashSize;
	PassServer ps(hashSize);

    while (choice != 'x')
    {
        Menu();
        cin >> choice;
        switch (choice)
        {//switch is getting mad at me, so adding {} around all case blocks so it stops crying.
            case 'l':
            {
                string loadFile;
                cout << "Enter filename: ";
                cin >> loadFile;
                if (!ps.load(loadFile.c_str()))
                {
                    cerr << "Error loading file.";
                    // if necessary to output more specific errors, add here?
                }
                else
                {
                    cout << "Loaded " << loadFile << " successfully." << endl;
                    // maybe do something after loaded?
                }
                break;
            }

            case 'a':
			{
				pair<string, string> newUser;
				cout << "Enter username: ";
				cin >> newUser.first;
				cout << endl << "Enter password: ";
				cin >> newUser.second;
				cout << endl;

                if(ps.addUser(newUser))
					cout << "User " << newUser.first << " added successfully." << endl;
				else
					cout << "Unable to add user." << endl;
                break;
			}

            case 'r':
			{
				string userSearch;
				cout << "Enter the username to remove: ";
				cin >> userSearch;

                if(ps.removeUser(userSearch))
					cout << endl << userSearch << " found.";
				else
					cout << endl << userSearch << " NOT found.";
                break;
			}
            case 'c':
			{
				string newPass = "";
				pair<string, string> findUser;
				cout << "Enter the username you want to modify: ";
				cin >> findUser.first;
				
				cout << endl << "Enter the password for that user: ";
				cin >> findUser.second;

				cout << "Enter the new password: ";
				cin >> newPass;
				cout << endl;

                if(ps.changePassword(findUser, newPass))
					cout << "Changed password successfully." << endl;
				else
					cout << "Unable to change password." << endl;
                break;
			}
            case 'f':
            {
			    string username;
                cout << "Enter username to find: ";
                cin >> username;

                if (ps.find(username))
                    cout << username << " found." << endl;
                else
                    cout << username << " not found." << endl;
                break;
			}
            case 'd':
            {
			    ps.dump();
                break;
			}
            case 's':
            {
			    cout << "Size of HashTable: " << ps.size() << endl;
                break;
			}
            case 'w':
			{
				string writeFile;
				cout << "Enter filename to write to: ";
				cin >> writeFile;
				cout << endl;

                if(ps.write_to_file(writeFile.c_str()))
					cout << "Write successful." << endl;
				else
					cout << "Write fail." << endl;
                break;
			}
            case 'x':
            {
			    // nothing goes here.
                break;
			}
            default:
            { 
			    cout << "Invalid input. " << endl;
                break;
			}
        }
    }
}

void Menu()
{
    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice: ";
}
