#include <iostream>
#include "hashtable.h"
#include "passserver.h"

using namespace std;
using namespace cop4530;

void Menu();

//        usrnme  passwd
HashTable<string, string> table;
PassServer ps;


int main()
{
  char choice = ' ';

  while(choice != 'x')
  {
    Menu();
    cin >> choice;
    switch(choice)
    {
      case 'l':
        string filename;
        cout << "Enter filename: ";
        cin >> filename;
        if(!ps.load(filename))
        {
          cerr << "Error loading file.";
          //if necessary to output more specific errors, add here?
        }
        else
        {
          cout << "Loaded " << filename << " successfully." << endl;
          //maybe do something after loaded?
        }
        break;
      case 'a':
        ps.addUser(/**/);
        break;
      case 'r':
        ps.removeUser(/**/)
        break;
      case 'c':
        ps.changePassword(/**/)
        break;
      case 'f':
        string username;
        cout << "Enter username to find: ";
        cin >> username;
        if(ps.find(username))
        {
          cout << username << " found." << endl;
        }
        else
        {
          cout << username << " not found." << endl;
        }
        break;
      case 'd':
        ps.dump();
        break;
      case 's':
        ps.size();
        break;
      case 'w':
        ps.write_to_file(/*filename to create*/);
        break;
      case 'x':
        //nothing goes here.
        break;
      default:
        cout << "Invalid input. " << endl;
        break;
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
  cout << "\nEnter choice : ";
}
