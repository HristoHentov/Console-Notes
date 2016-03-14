/******************************
*       Христо Хентов         *
*          116-кнр            *
*                             *
*   Основи на програмирането  *
*        Влади Иванов         *
*        27/11/2015 г.        *
******************************/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <fstream>

using namespace std;

#include "class.h"
#include "note.cpp"
#include "account.cpp"
#include "menu.cpp"

int main()
{
    menu start;

    bool accLoop = true;
    bool mainLoop = true;

    userAccount * head = NULL;
    note * root = NULL;

    userAccount accDataBase;
    accDataBase.loadAccounts(head, root);

    do
    {
        switch(start.mainMenu())
        {
        case '1':
        {
            accLoop = true;
            string currentAccount = accountCreation(head);
            note accNoteList;
            do
            {
                switch(start.accountMenu(currentAccount))
                {
                case '1':
                {
                    accNoteList.createNote(root, noteCreation(root, currentAccount), currentAccount);
                    cout << "\nNote Successfully created!.";
                    system("PAUSE;");
                    break;
                }
                case '2':
                {
                    accNoteList.viewNotes(root, currentAccount, true);
                    cout << "\n";
                    system("PAUSE");
                    break;
                }
                case '3':
                {
                    noteDeletion(root, currentAccount);
                    break;
                }
                case '4':
                {
                    accLoop = false;
                    break;
                }
                case '5':
                    return 0;
                default :
                {
                    cin.ignore(100, '\n');
                    cout << "\nInvalid choice. Please try again.\n";
                    system("PAUSE");
                    break;
                }
                }
            }
            while(accLoop);
            break;
        }
        case '2':
        {
            system("CLS");
            accLoop = true;
            userAccount two;
            string currentAccount = two.logIn(head);
            note accNoteList;

            do
            {
                switch(start.accountMenu(currentAccount))
                {
                case '1':
                {
                    accNoteList.createNote(root, noteCreation(root, currentAccount), currentAccount);
                    cout << "\nNote Successfully created!.";
                    system("PAUSE;");
                    break;
                }
                case '2':
                {
                    accNoteList.viewNotes(root, currentAccount, true);
                    cout << "\n";
                    system("PAUSE");
                    break;
                }
                case '3':
                {
                    noteDeletion(root, currentAccount);
                    break;
                }
                case '4':
                {
                    accLoop = false;
                    break;
                }
                case '5':
                    return 0;
                default :
                {
                    cin.ignore(100, '\n');
                    cout << "\nInvalid choice. Please try again.\n";
                    system("PAUSE");
                    break;
                }
                }
            }
            while(accLoop);
            break;
        }
        case '3':
        {
            accountDeletion(head, root);
            break;

        }
        case '4':
        {
            start.helpMenu();
            break;
        }
        case '5':
        {
            return 0;
            break;
        }

        default :
        {
            cin.ignore(100, '\n');
            cout << "\nInvalid choice. Please try again.\n";
            system("PAUSE");
            break;
        }
        }

    }
    while(mainLoop);
    return 0;
}
