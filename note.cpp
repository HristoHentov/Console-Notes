note::note()
{
    char data[500] = ""; /// useless
    note * next = NULL;
    noteCheck = false;

}

void note::createNote(note * &root, char * tempUserData, string ownerName)
{
    if(!root)
    {
        root = new note;
        root -> data = tempUserData;
        root -> owner = ownerName;
        root -> next = NULL;
        return;
    }

    createNote(root -> next, tempUserData, ownerName);
}

void note::viewNotes(note * root, string accountName, bool noNotes)
{
    if(!root && noNotes)
    {
        cout << "\nYou don't have any notes.Please add some first.";
        return;
    }

    if(!root && !noNotes)
        return;

    if(root -> owner == accountName)
    {
        cout << root -> data << endl;
        noNotes = false;
    }

    viewNotes(root -> next, accountName, noNotes);
}

char * noteCreation(note * &root, string currAcc)
{
    char tempData[500];
    char * userData;
    cout << "Please enter the text you wish store in the note: " << endl;

    cin.ignore(500, '\n');
    cin.getline(tempData, 500);

    userData = new char [strlen(tempData) + 1];
    strcpy (userData, tempData);

    ofstream noteR;
    noteR.open("noteRelations.txt", ios::app);

    noteR << currAcc << '^' << tempData << endl;

    noteR.close();
    return userData;
}
void noteDeletion(note * &root, string  ownerName)
{
    char choice;
    bool retry = true;
    cout << "\nAre you sure you sure? ";

    do
    {
        cout << " [Y/N]";
        cin >> choice;

        switch(toupper(choice))
        {
        case 'Y' :
        {
            note DB;
            system("pause");


            DB.deleteNotes(root, ownerName);
            system("PAUSE");

            char tempName[32];
            char tmpName[32];
            char tmpData[500];
            char * namePoint;

            ifstream notes;
            notes.open("noteRelations.txt");

            ofstream tempRelations;
            tempRelations.open("tmp.txt", ios::app);

            do
            {
                notes.getline(tmpName, 32, '^');
                notes.getline(tmpData, 500, '\n');

                const char * namePoint = ownerName.c_str();
                if((strcmp(tmpName, namePoint)) != 0)
                    if(strlen(tmpName) > 0)
                        tempRelations << tmpName << "^" << tmpData << endl;


            }
            while (!notes.eof());

            notes.close();
            tempRelations.close();

            remove ("noteRelations.txt");
            rename ("tmp.txt", "noteRelations.txt");


            retry = false;
            break;
        }
        case 'N' :
        {
            return;
            retry = false;
        }

        default :
        {
            cout << "\nInvalid choice please try again: ";
            retry = true;
            break;
        }
        }
    }
    while(retry);
}


void note::deleteNotes(note * &root, string ownerN)
{
    if(!root)
        cout << "Notes database is empty!";
    else
    {
        note * current;
        note * prev;
        current = root;
        prev = NULL;

        bool retrace = false;
        bool continueTracing = false;
        bool nextIsHead = false;
        bool nextIsOther = false;
        do
        {
            while(current != NULL)
            {

                if(ownerN == current -> owner) /// if note is found
                {
                    continueTracing = true;
                    break;
                }

                else
                {
                    prev = current;
                    current= current -> next;
                }
            }

            if(current == NULL)
            {
                continueTracing = false;
            }


            else /// delete note based on location
            {
                if(root == current)
                {
                    root = root -> next; /// set root to point to the second note in the list
                    nextIsHead = true;
                }
                else /// any other position
                {
                    prev -> next = current -> next;
                    nextIsOther = true;
                }

                delete current;
                root -> noteCheck = false;
            }

            if(continueTracing)
            {
                if(nextIsHead)
                    current = root;
                else if(nextIsOther)
                    current = prev -> next;

                retrace = true;
            }
            else
                retrace = false;

        }
        while(retrace);

    }
}


