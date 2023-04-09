#include "knight2.h"
/* * * Begin class Events * * */
Events::Events(const string &file_events)
{
    ifstream ifs;
    stringstream ss;
    string line;
    string content;
    ifs.open(file_events);
    int c = 0;
    while (getline(ifs, line))
    {
        content += line + '\n';
    }
    ss << content;
    ss >> evntnum;
    evnt = new int[evntnum];
    while (ss >> evnt[c])
    {
        c++;
    }
}

int Events::count() const
{
    return evntnum;
}

int Events::get(int i) const
{
    return evnt[i];
}

Events::~Events()
{
    delete[] evnt;
    evnt = nullptr;
}
/* * * End class Events * * */

/* * * BEGIN implementation of class BaseOpponent* * */

/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class BaseKnight * * */
int BaseKnight::snt(int a)
{
    int k = 0;
    if (a <= 1)
        return 0;
    else if (a == 2)
        return 1;
    else
    {
        for (int i = 2; i < a; i++)
            if (a % i == 0)
                k++;
        if (k != 0)
            return 0;
        else
            return 1;
    }
}

int BaseKnight::pythagoras(int n)
{
    int a = n % 10;
    int b = (n % 100 - a) / 10;
    int c = (n - a - b * 10) / 100;
    if (n > 100 && n < 999)
    {
        if (pow(a, 2) == pow(b, 2) + pow(c, 2) || pow(b, 2) == pow(a, 2) + pow(c, 2) || pow(c, 2) == pow(a, 2) + pow(b, 2))
            return 1;
        else
            return 0;
    }
    else
        return 0;
}
BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    BaseKnight *knight;
    if (snt(maxhp) == 1)
    {
        knight = new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    else if (maxhp == 888)
    {
        knight = new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    else if (pythagoras(maxhp))
    {
        knight = new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    else
    {
        knight = new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    return knight;
}

string BaseKnight::toString() const
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) + ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) + ",gil:" + to_string(gil) + "," + bag->toString() + ",knight_type:" + typeString[knightType] + "]";
    return s;
}

KnightType BaseKnight::getType() const
{
    return knightType;
}
/* * * END implementation of class BaseKnight * * */

/* * * Begin class BaseItem * * */

/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of LinkedList * * */
// inserting elements (At start of the list)
void LinkedList::insert(string val)
{
    // make a new node
    Node *new_node = new Node(val);

    // If list is empty, make the new node, the head
    if (head == nullptr)
    {
        head = new_node;
    }
    // else, make the new_node the head and its next, the previous
    // head
    else
    {
        new_node->next = head;
        head = new_node;
    }
}

// loop over the list. return true if element found
bool LinkedList::search(string val)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data == val)
            return true;
        temp = temp->next;
    }
    return false;
}

void LinkedList::remove(string val)
{
    Node *temp = head;
    // If the head is to be deleted
    if (temp != nullptr && temp->data == val)
    {
        head = temp->next;
        delete temp;
        return;
    }
    // Else loop over the list and search for the node to delete
    else
    {
        Node *curr = head;
        while (temp != nullptr && temp->data != val)
        {
            // When node is found, delete the node and modify the pointers
            curr = temp;
            temp = temp->next;
        }
        // If values is not found in the linked list
        if (!temp)
        {
            cout << "Value not found" << endl;
            return;
        }

        curr->next = temp->next;
        delete temp;
    }
}

void LinkedList::display()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

/* * * END implementation of LinkedList * * */

/* * * BEGIN implementation of class BaseBag * * */
bool BaseBag::insertFirst(BaseItem *item)
{
    int maxitemnum;
    int itemnum;
    LinkedList listItem;
    if (knight->getType() == DRAGON)
        maxitemnum = 14;
    else if (knight->getType() == LANCELOT)
        maxitemnum = 16;
    else if (knight->getType() == NORMAL)
        maxitemnum = 19;
    if (itemnum < maxitemnum && ((knight->getType() == DRAGON) && (listItem.search("Antidote") == 0)))
        return true;
    else
        return false;
}
BaseItem *BaseBag::get(ItemType itemType)
{
}
string BaseBag::toString() const
{
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string &file_armyknights)
{
    ifstream ifs;
    stringstream ss;
    string content;
    string line, data;
    int count;
    ifs.open(file_armyknights);
    getline(ifs, line);
    ss << line;
    ss >> armyNum;
    army = new BaseKnight *[armyNum];
    int id = 1;
    int maxhp, level, gil, antidote, phoenixdownI;
    for (int i = 0; i < armyNum; i++)
    {
        ss.str();
        getline(ifs, content);
        ss << content;
        ss >> maxhp >> level >> gil >> antidote >> phoenixdownI;
        army[i] = BaseKnight::create(id++, maxhp, level, gil, antidote, phoenixdownI);
    }
}

ArmyKnights::~ArmyKnights()
{
    for (int i = 0; i < armyNum; i++)
    {
        delete army[i];
    }
    delete[] army;
}
bool ArmyKnights::fight(BaseOpponent *opponent)
{
}
bool ArmyKnights::adventure(Events *events)
{
}
int ArmyKnights::count() const
{
}
BaseKnight *ArmyKnights::lastKnight() const
{
}
bool ArmyKnights::hasPaladinShield() const
{
}
bool ArmyKnights::hasLancelotSpear() const
{
}
bool ArmyKnights::hasGuinevereHair() const
{
}
bool ArmyKnights::hasExcaliburSword() const
{
}
void ArmyKnights::printInfo() const
{
    cout << "No. knights: " << this->count();
    if (this->count() > 0)
    {
        BaseKnight *lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
         << ";LancelotSpear:" << this->hasLancelotSpear()
         << ";GuinevereHair:" << this->hasGuinevereHair()
         << ";ExcaliburSword:" << this->hasExcaliburSword()
         << endl
         << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const
{
    cout << (win ? "WIN" : "LOSE") << endl;
}
/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure()
{
    armyKnights = nullptr;
    events = nullptr;
}

/* * * END implementation of class KnightAdventure * * */