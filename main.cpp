#include <iostream>
#include <sstream>
#include <regex>
#include "AVL.h"
using namespace std;

// Function used to determine if inputted name is valid (a-z, A-Z, and spaces)
bool checkName(string& name)
{
    regex obj = regex("^[a-zA-Z ]+$");
    bool validName = regex_search(name, obj);
    return validName;
}

// Function used to determine if inputted ID is valid (0-9, 8 digits long)
bool checkID(string& ufID)
{
    regex obj = regex("^[0-9]{8,8}$");
    bool validID = regex_search(ufID, obj);
    return validID;
}

// Calls respected commands based on the user input
void AVLFunctions(AVLTree &tree, string& command, string& name, string& ufID)
{

    if(command == "insert")
    {
        if(!checkName(name) || !checkID(ufID))
        {
            cout << "unsuccessful" << endl;
        }
        else
        {
            tree.insert(name, ufID);
        }
    }
    else if(command == "remove")
    {
        if(!checkID(ufID))
        {
            cout << "unsuccessful" << endl;
        }

        else
        {
            tree.removeID(ufID);
            cout << "successful" << endl;
        }

    }
    else if(command == "search")
    {
        // if a name is inputted, searches for matching id
        if(checkName(name))
        {
            tree.searchName(name);
        }
        // if an id is inputted, searches for matching name
        else if(checkID(ufID))
        {
            tree.searchID(ufID);
        }
        else
        {
            cout << "unsuccessful" << endl;
        }
    }
    else if(command == "printInorder")
    {
        tree.printInorder();
    }
    else if(command == "printPreorder")
    {
        tree.printPreorder();
    }
    else if(command == "printPostorder")
    {
        tree.printPostorder();
    }
    else if(command == "printLevelCount")
    {
        tree.printLevelCount();
    }
    else if(command == "removeInorder")
    {
        int n = stoi(ufID);
        tree.removeInorder(n);
    }
    // in the case of an invalid command
    else
    {
        cout << "unsuccessful" << endl;
    }
}

// Function used to parse the inputted strings
void parseInput()
{
    AVLTree tree;
    // gets the number of commands and converts to a numerical value
    string numLines;
    getline(cin, numLines);
    int numOfCommands;
    numOfCommands = stoi(numLines);
    // loops through the lines (# of commands) times
    while(numOfCommands--) {
        string line;
        getline(cin, line);
        // splits the input into 3 variables (command, name, id)
        istringstream in(line);
        string command;
        in >> command;

        string name;
        if(line.find('"') != line.npos)
        {
            getline(in, name, '"');
            getline(in, name, '"');
        }
        string ufID;
        in >> ufID;

        // passes parsed data into AVLFunctions() and performs commands based on input
        AVLFunctions(tree, command, name, ufID);
    }
}

int main() {
    // read in number of commands
    // for each command, execute it on t variable
    parseInput();

  /* AVLTree tree;
    tree.insert("Adam","11111111");
    tree.insert("Brian", "22222222");
    tree.insert("Caroline", "33333333");
    tree.printPreorder();
    tree.printInorder();
    tree.printPostorder();
*/
   /* AVLTree tree;
    tree.insert("Brandon", "45679999");
    tree.insert("Brian", "35459999");
    tree.insert("Briana", "87879999");
    tree.insert("Bella", "95469999");
    tree.printInorder();
    tree.removeID("95469999");
    tree.printInorder();*/

    return 0;
}