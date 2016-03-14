class menu
{
public:
    menu();

    char mainMenu(), accountMenu(string);
    void helpMenu();
};

class note
{

public:
    note();
    note * next;
    char * data;
    string owner;


    void createNote(note * &root, char * userData, string ownerName);
    void viewNotes(note * root, string accountName, bool);
    void deleteNotes(note * &root, string);

private :
    bool noteCheck;
};


void noteDeletion(note * &root, string);


class userAccount
{
public:

    userAccount();
    userAccount * next;


    char * username; /// make it private and char * array and add get()/set() functions
    char * password; /// make it private and char * arrayand add get()/set() functions
    note * root;     /// make it private and add get()/set() functions


    void createAccount(userAccount * &head, char * userName, char * passWord);
    string logIn(userAccount * head);
    void logAccount(char name[], char pass[]);
    void deleteAccount(userAccount * &head, note * &root, char * accountName, char* accountPass);
    bool checkList(userAccount * head, char * name, char * pass);
    bool checkName(userAccount * head, char * name);
    void loadAccounts(userAccount * &head, note * &root);
    void loadAccNotes(userAccount * head, char accName[32], note * &root); /// make both of these 1 function
};



string accountCreation(userAccount * &head);
void accountDeletion(userAccount * &head, note * &root);
char * noteCreation(note * &root, string);
bool checkName(char *);

