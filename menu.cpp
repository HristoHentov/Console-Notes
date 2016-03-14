
menu::menu() // clean up
{

}
char menu::mainMenu()
{
    char menuChoice;
    system("CLS");
    cout << "Welcome to the Console Data Keeper 2015. \nPlease choose an action.";
    cout << "\n\n=======================================";                               /// USE ASCI chars for better frames
    cout << "\n| 1. Create a new account.            |";
    cout << "\n| 2. Log in to an existing account.   |";
    cout << "\n| 3. Delete an account.               |";
    cout << "\n| 4. Help / Instructions.             |";
    cout << "\n| 5. Quit.                            |";
    cout << "\n=======================================";

    cout << "\nYour choice: ";
    cin >> menuChoice;

    return menuChoice;
}

void menu::helpMenu()
{
    system("CLS");
    cout << "                           -= Console Notes 2015 =-";
    cout << "\n===============================================================================";
    cout << "\nThis is a note creation console application. If you want to make some notes";
    cout << "\nfirst make an account by choosing option number 1 from the main menu.";
    cout << "\n\nAfter having created a new account you can add a new note, view your existing";
    cout << "\nnotes or delete them.";
    cout << "\n\nAdditionaly, you can delete your account at any time.";
    cout << "\n\n===============================================================================";
    cout << "\n\nEnjoy using this program. ";
    system("PAUSE");
}

char menu::accountMenu(string name)
{
    char choice;
    system("CLS");
    cout << "                           -= Console Notes 2015 =-";
    cout << "\nAccount: " << name;
    cout << "\n=======================================";
    cout << "\n| 1. Create a new note.                |";
    cout << "\n| 2. View your notes.                  |";
    cout << "\n| 3. Delete note.                      |";
    cout << "\n| 4. Log out and return to main menu.  |";
    cout << "\n| 5. Quit.                             |";
    cout << "\n=======================================";
    cout << "\n\nYour choice: ";
    cin >> choice;

    return choice;
}

