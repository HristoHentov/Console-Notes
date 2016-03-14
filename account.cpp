userAccount::userAccount()
{
    note * root = NULL;
}

void userAccount::createAccount(userAccount *&head, char * userName, char * passWord)
{
    if(!head)
    {
        head = new userAccount;
        head -> username = new char [strlen(userName) + 1];
        strcpy(head -> username, userName);
        head -> password = new char [strlen(passWord) + 1];
        strcpy(head -> password, passWord);
        head -> next = NULL;
        return;
    }

    createAccount(head -> next, userName, passWord);
}

string accountCreation(userAccount * &head)
{
    system("CLS");
    char temp[20];
    char * namePoint;


    char * passPoint;

    bool retry = true;


    cout << "Please choose a name and password for your account.";
    cout << "\nUsername must be between 4 and 20 symbols.";
    cout << "\nPassword must be between 5 and 32 symbols.";
    cin.ignore(20, '\n'); // flushes the input buffer
    do
    {
        cout << "\n\nUsername: ";
        cin.getline(temp, 20);

        namePoint = new char [strlen(temp) + 1];
        strcpy (namePoint, temp);
        if (strlen(temp) <= 3 || strlen(temp) > 20 || (checkName(namePoint)))
        {
            cout << "Invalid username. Please try agian.";
            retry = true;
        }
        else
            retry = false;

    }
    while(retry);

    char pass[32]; // permanent pass char.
    char a; // char to hold temp pass input
    int c; // infinite loop char.
    bool invalidPassword = false;
    do
    {


        cout << "Password: ";
        for (c = 0;;)
        {
            a = getch();
            if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
            {
                pass[c] = a;
                c++;
                cout << "*";
            }
            if(a == '\b' && c >= 1)
            {
                cout<<"\b \b";
                --c;
            }
            if(a=='\r')
            {
                pass[c]='\0';
                break;
            }

        }

        if(c < 5 || c > 32)
        {
            cout << "\nInvalid password. Please try again.\n" << endl;
            invalidPassword = true;
        }
        else
            invalidPassword = false;

    }
    while(invalidPassword);
    passPoint = new char [strlen(pass) + 1];
    strcpy(passPoint, pass);


    userAccount newAccount;
    newAccount.createAccount(head, namePoint, passPoint);
    newAccount.logAccount(namePoint, passPoint);

    cout << "\nAccount " << head -> username << " created successfully!";
    return namePoint;
}

bool checkName(char * name)
{
    char tempName[20];
    char junk[33];

    ifstream accDB;
    accDB.open("accinf.txt");
    while(!(accDB.eof())) // while end of file is not reached
    {
        accDB.getline(tempName, 20, '%'); //gets the line until the % symbol
        accDB.getline(junk, 33, '\n'); // gets the rest of the line
        if(!(strcmp(tempName, name))) // check to see if it is duplcate
        {
            accDB.close(); // closes the file
            return true; // terminates account Logging
        }
    }

    accDB.close();
    return false;

}
void userAccount::logAccount(char name[], char pass[]) // these should either be strings or char *
{
    char tempName[20];
    char junk[33];
    string tempRead;


    ifstream iaccLog;
    iaccLog.open("accinf.txt");

    while(!(iaccLog.eof()))
    {
        iaccLog.getline(tempName, 20, '%');
        iaccLog.getline(junk, 33, '\n');
        if(!(strcmp(tempName, name)))
        {
            iaccLog.close();
            return;
        }
    }
    iaccLog.close();

    ofstream accLog;
    accLog.open("accinf.txt", ios::app);
    accLog <<  name << "%" << pass << endl;
    accLog.close();
}

void userAccount::loadAccounts(userAccount * &head, note * &root)
{
    char tempName[32];
    char tempPass[32];

    ifstream accDB;
    accDB.open("accinf.txt");

    while(!accDB.eof())
    {
        userAccount accountDB;
        accDB.getline(tempName, 32, '%');
        accDB.getline(tempPass, 32, '\n');

        accountDB.createAccount(head, tempName, tempPass);
        loadAccNotes(head, tempName, root);
    }
    accDB.close();
}

void userAccount::loadAccNotes(userAccount * head, char accName[32], note * &root)
{
    char currName[32];
    char * noteData;
    char tempData[500];
    note handle;

    ifstream noteDB;
    noteDB.open("noteRelations.txt");

    while(!noteDB.eof())
    {

        noteDB.getline(currName, 32, '^');
        noteDB.getline(tempData, 500, '\n');

        noteData = new char [strlen(tempData) + 1];
        strcpy (noteData, tempData);

        if(!strcmp(accName, currName))
            handle.createNote(root, noteData, accName);


    }
    noteDB.close();
}

string userAccount::logIn(userAccount *head)
{
    bool retry;
    char temp [20];
    char * namePoint;
    char * passPoint;
    cout << "Please enter your account info.";
    cin.ignore(20, '\n');

    do
    {
        cout << "\nUsername: ";
        cin.getline(temp, 20);

        namePoint = new char [strlen(temp) + 1];
        strcpy (namePoint, temp);
        if (strlen(temp) <= 3 || strlen(temp) > 20)
        {
            cout << "\nInvalid username. Please try agian.";
            retry = true;
        }
        if (!checkName(head, namePoint))
        {
            cout << "\nNo such user. Please try again.";
            retry = true;
        }
        else
            retry = false;

    }
    while(retry);




    char pass[32];
    char a;
    int c;
    bool authenticate = false;
    do
    {


        cout << "Password: ";
        for (c = 0;;)
        {
            a = getch();
            if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
            {
                pass[c] = a;
                c++;
                cout << "*";
            }
            if(a == '\b' && c >= 1)
            {
                cout<<"\b \b";
                --c;
            }
            if(a=='\r')
            {
                pass[c]='\0';
                break;
            }

        }

        passPoint = new char [strlen(pass) + 1];
        strcpy(passPoint, pass);

        if(checkList(head, namePoint, passPoint))
        {
            cout << "\n\nLogged in successfully!" << endl;
            authenticate = true;
        }
        else
            cout << "\n\nWrong password. Please try again." << endl;

    }
    while(!authenticate);
    system("PAUSE");
    return namePoint;
}

bool userAccount::checkList(userAccount * head, char * name, char * pass)
{
    if(!head)
        return false;

    if(!(strcmp(head -> username, name)) && !(strcmp(head -> password, pass)))
        return true;

    checkList(head -> next, name, pass);

}

bool userAccount::checkName(userAccount * head, char * name)
{
    if(!head)
        return false;

    if(!(strcmp(head -> username, name)))
        return true;

    checkName(head -> next, name);

}

void accountDeletion(userAccount * &head, note * &root)
{
    bool retry;
    char temp [20];
    char * namePoint;
    char * passPoint;
    userAccount acc;

    cout << "\nPlease enter the name of the account you wish to delete: ";
    cin.ignore(20, '\n');

    do
    {
        cout << "\nUsername: ";
        cin.getline(temp, 20);

        namePoint = new char [strlen(temp) + 1];
        strcpy (namePoint, temp);
        if (strlen(temp) <= 3 || strlen(temp) > 20)
        {
            /// handling for input.
            cout << "\nInvalid username. Please try agian.";
            retry = true;
        }

        else if (!acc.checkName(head, namePoint))
        {
            cout << "\nNon-existing account. Please try again.";
            retry = true;
        }

        else
            retry = false;

    }
    while(retry);




    char pass[32];
    char a;
    int c;
    bool moveon;

    do
    {


        cout << "Password: ";
        for (c = 0;;)
        {
            a = getch();
            if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
            {
                pass[c] = a;
                c++;
                cout << "*";
            }
            if(a == '\b' && c >= 1)
            {
                cout<<"\b \b";
                --c;
            }
            if(a=='\r')
            {
                pass[c]='\0';
                break;
            }

        }
        passPoint = new char [strlen(pass) + 1];
        strcpy(passPoint, pass);


        if(acc.checkList(head, namePoint, passPoint))
            moveon = true;

        else
        {
            cout << "\nWrong password!";
            moveon = false;
        }

    }
    while(!moveon);

    acc.deleteAccount(head, root, namePoint, passPoint);

    char tempName[32];
    char tempPass[32];

    char tmpData[500];
    char tmpName[32];
    ifstream accDB;
    accDB.open("accinf.txt");

    ifstream notes;
    notes.open("noteRelations.txt");

    ofstream tempFile;
    tempFile.open("temp.txt", ios::app);

    ofstream tempRelations;
    tempRelations.open("tmp.txt", ios::app);
    string tmpch;

    do
    {
        accDB.getline(tempName, 32, '%');
        accDB.getline(tempPass, 32, '\n');

        if((strcmp(tempName, namePoint)) != 0)
            if(strlen(tempName) > 0)
                tempFile << tempName << "%" << tempPass << endl;



    }
    while(!accDB.eof());
    do
    {
        notes.getline(tmpName, 32, '^');
        notes.getline(tmpData, 500, '\n');

        if((strcmp(tmpName, namePoint)) != 0)
            if(strlen(tmpName) > 0)
                tempRelations << tmpName << "^" << tmpData << endl;
    }
    while (!notes.eof());

    accDB.close();
    tempFile.close();

    notes.close();
    tempRelations.close();

    remove ("accinf.txt");
    rename ("temp.txt", "accinf.txt");

    remove ("noteRelations.txt");
    rename ("tmp.txt", "noteRelations.txt");

    cout << "\n\nAccount successfully removed from Database." << endl;
    system("PAUSE");
}

void userAccount::deleteAccount(userAccount * &head, note * &root, char * accountName, char * accountPassword)
{

    if(!head)
        cout << "\nAccount database is empty!";
    else
    {
        userAccount * curr;
        userAccount * trail;
        curr = head;
        trail = NULL;

        while(curr != NULL)
        {
            if(!(strcmp(curr -> username, accountName)))
                break;
            else
            {
                trail = curr;
                curr = curr -> next;
            }
        }

        //if(curr == NULL)
        //cout << "Account does not exist in database.";

        if(curr != NULL)
        {
            if(head == curr)
                head = head -> next;
            else
                trail -> next = curr -> next;

            delete curr;
        }
    }

    if(!root)
        cout << "Notes database is empty!";
    else
    {
        note * current;
        note * prev;
        current = root;
        prev = NULL;

        while(current != NULL)
        {
            string tempName = current -> owner;
            const char * c = tempName.c_str();

            if(!(strcmp(c, accountName)))
                break;
            else
            {
                prev = current;
                current= current -> next;
            }
        }

        if(current != NULL)
        {
            if(root == current)
                root = root -> next;
            else
                prev -> next = current -> next;

            delete current;
        }
    }
/// DELETE NOTE NODE --- END;
    return;
}
