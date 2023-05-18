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
        content += line + '\n';
    ss << content;
    ss >> this->evntnum;
    evnt = new int[evntnum];
    while (ss >> evnt[c])
    {
        c++;
        if (c == evntnum)
            break;
    }
}

int Events::count() const { return this->evntnum; }

int Events::get(int i) const { return evnt[i]; }

Events::~Events()
{
    delete[] evnt;
    evnt = nullptr;
}
/* * * End class Events * * */

/* * * BEGIN implementation of class BaseOpponent* * */
BaseOpponent::BaseOpponent(string OpponentType, int baseDamage, int gil, int eventid) : OpponentType(OpponentType), baseDamage(baseDamage), gil(gil), eventid(eventid), appear(false) {}
BaseOpponent::BaseOpponent(string OpponentType, int eventid, bool appear) : OpponentType(OpponentType), eventid(eventid), appear(appear) {}
MadBear::MadBear(int i) : BaseOpponent("MadBear", 10, 100, 1) { this->levelO = (i + this->eventid) % 10 + 1; }
Bandit::Bandit(int i) : BaseOpponent("Bandit", 15, 150, 2) { this->levelO = (i + this->eventid) % 10 + 1; }
LordLupin::LordLupin(int i) : BaseOpponent("LordLupin", 45, 450, 3) { this->levelO = (i + this->eventid) % 10 + 1; }
Elf::Elf(int i) : BaseOpponent("Elf", 75, 750, 4) { this->levelO = (i + this->eventid) % 10 + 1; }
Troll::Troll(int i) : BaseOpponent("Troll", 95, 800, 5) { this->levelO = (i + this->eventid) % 10 + 1; }
Tornbery::Tornbery(int i) : BaseOpponent("Tornbery", 0, 0, 6) { this->levelO = (i + this->eventid) % 10 + 1; }
QueenofCards::QueenofCards(int i) : BaseOpponent("QueenofCards", 0, 0, 7) { this->levelO = (i + this->eventid) % 10 + 1; }
NinaDeRings::NinaDeRings() : BaseOpponent("NinadeRings", 0, 0, 8) {}
DurianGarden::DurianGarden() : BaseOpponent("DurianGarden", 0, 0, 9) {}
OmegaWeapon::OmegaWeapon(bool appear) : BaseOpponent("OmegaWeapon", 10, appear) {}
Hades::Hades(bool appear) : BaseOpponent("Hades", 11, appear) {}
Ultimecia::Ultimecia() : BaseOpponent("Ultimecia", 0, 0, 99) { UltiHP = 5000; }
/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class BaseKnight * * */
BaseKnight::BaseKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote, KnightType knightType) : id(id), maxhp(maxhp), level(level), gil(gil), antidote(antidote), phoenixdownI(phoenixdownI), hp(maxhp), knightType(knightType), poisened(false) {}
int BaseKnight::snt(int a)
{
    if (a == 1)
        return 0;
    else if (a == 2)
        return 1;
    else
        for (int i = 2; i < a; i++)
            if (a % i == 0)
                return 0;
    return 1;
}

int BaseKnight::pythagoras(int n)
{
    int a = n % 10;
    int b = (n % 100 - a) / 10;
    int c = (n - a - b * 10) / 100;
    if (n > 100 && n < 999 && a != 0 && b != 0 && c != 0)
    {
        if (pow(a, 2) == pow(b, 2) + pow(c, 2) || pow(b, 2) == pow(a, 2) + pow(c, 2) || pow(c, 2) == pow(a, 2) + pow(b, 2))
            return 1;
        return 0;
    }
    return 0;
}
BaseKnight *BaseKnight::create(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote)
{
    BaseKnight *knight;
    if (snt(maxhp) == 1)
        knight = new PaladinKnight(id, maxhp, level, phoenixdownI, gil, antidote, PALADIN);
    else if (maxhp == 888)
        knight = new LancelotKnight(id, maxhp, level, phoenixdownI, gil, antidote, LANCELOT);
    else if (pythagoras(maxhp) == 1)
        knight = new DragonKnight(id, maxhp, level, phoenixdownI, gil, antidote, DRAGON);
    else
        knight = new NormalKnight(id, maxhp, level, phoenixdownI, gil, antidote, NORMAL);
    return knight;
}

string BaseKnight::toString() const
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    string s("");
    s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) + ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) + ",gil:" + to_string(gil) + "," + bag->toString() + ",knight_type:" + typeString[knightType] + "]";
    return s;
}

PaladinKnight::PaladinKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote, KnightType knightType) : BaseKnight(id, maxhp, level, phoenixdownI, gil, antidote, knightType) {}
LancelotKnight::LancelotKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote, KnightType knightType) : BaseKnight(id, maxhp, level, phoenixdownI, gil, antidote, knightType) {}
DragonKnight::DragonKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote, KnightType knightType) : BaseKnight(id, maxhp, level, phoenixdownI, gil, antidote, knightType) {}
NormalKnight::NormalKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote, KnightType knightType) : BaseKnight(id, maxhp, level, phoenixdownI, gil, antidote, knightType) {}
/* * * END implementation of class BaseKnight * * */

/* * * Begin class BaseItem * * */
BaseItem::BaseItem(ItemType itemType) : itemType(itemType) {}
Antidote::Antidote() : BaseItem(ANTIDOTE) {}
bool Antidote::canUse(BaseKnight *knight)
{
    if (knight->poisened == true)
        return true;
    return false;
}
void Antidote::use(BaseKnight *knight) { knight->poisened = false; }
PhoenixDownI::PhoenixDownI() : BaseItem(PHOENIXI) {}
bool PhoenixDownI::canUse(BaseKnight *knight)
{
    if (knight->hp <= 0)
        return true;
    return false;
}
void PhoenixDownI::use(BaseKnight *knight) { knight->hp = knight->maxhp; }
PhoenixDownII::PhoenixDownII() : BaseItem(PHOENIXII) {}
bool PhoenixDownII::canUse(BaseKnight *knight)
{
    if (knight->hp < int((knight->maxhp) / 4))
        return true;
    return false;
}
void PhoenixDownII::use(BaseKnight *knight) { knight->hp = knight->maxhp; }
PhoenixDownIII::PhoenixDownIII() : BaseItem(PHOENIXIII) {}
bool PhoenixDownIII::canUse(BaseKnight *knight)
{
    if (knight->hp < int((knight->maxhp) / 3))
        return true;
    return false;
}
void PhoenixDownIII::use(BaseKnight *knight)
{
    if (knight->hp <= 0)
        knight->hp = int((knight->maxhp) / 3);
    else
        knight->hp += int((knight->maxhp) / 4);
}
PhoenixDownIV::PhoenixDownIV() : BaseItem(PHOENIXIV) {}
bool PhoenixDownIV::canUse(BaseKnight *knight)
{
    if (knight->hp < int((knight->maxhp) / 2))
        return true;
    return false;
}
void PhoenixDownIV::use(BaseKnight *knight)
{
    if (knight->hp <= 0)
        knight->hp = int((knight->maxhp) / 2);
    else
        knight->hp += int((knight->maxhp) / 5);
}
/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class BaseBag * * */
BaseBag::BaseBag(int maxItems) : head(nullptr), maxItems(maxItems) {}
BaseBag::BaseBag() : head(nullptr) {}
int BaseBag::countItem()
{
    int count = 0;
    Node *temp = head;
    while (temp != nullptr)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

bool BaseBag::search(ItemType itemType)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data->itemType == itemType)
            return true;
        temp = temp->next;
    }
    return false;
}

BaseItem *BaseBag::get(ItemType itemType)
{
    if (search(itemType) == false)
        return nullptr;

    if (head->data->itemType == itemType)
        return head->data;

    Node *prevX = nullptr, *currX = head;
    while (currX && currX->data->itemType != itemType)
    {
        prevX = currX;
        currX = currX->next;
    }
    return prevX->data;
}

void BaseBag::deleteItem(BaseItem *data)
{
    Node *prevX = nullptr;
    Node *currX = head;
    while (currX != nullptr && currX->data != data)
    {
        prevX = currX;
        currX = currX->next;
    }

    if (currX == nullptr)
        return;

    if (currX != head)
    {
        prevX->next = head;
        Node *temp = head->next;
        head->next = currX->next;
        currX->next = temp;
        head = currX;
    }

    // Delete the head
    Node *temp1 = head;
    if (temp1 != nullptr)
    {
        head = temp1->next;
        delete temp1;
    }
}

string BaseBag::toString()
{
    string temp = "Bag[count=";
    temp += to_string(this->countItem()) + ";";
    Node *curr = head;
    int count = 0;
    if (head == nullptr)
        temp += "]";
    while (curr != nullptr)
    {
        if (curr->data->itemType == ANTIDOTE)
            temp += "Antidote";
        else if (curr->data->itemType == PHOENIXI)
            temp += "PhoenixI";
        else if (curr->data->itemType == PHOENIXII)
            temp += "PhoenixII";
        else if (curr->data->itemType == PHOENIXIII)
            temp += "PhoenixIII";
        else if (curr->data->itemType == PHOENIXIV)
            temp += "PhoenixIV";
        count++;
        if (count < countItem())
            temp += ",";
        else
            temp += "]";
        curr = curr->next;
    }
    return temp;
}

PaladinBag::PaladinBag() : BaseBag() {}
bool PaladinBag::insertFirst(BaseItem *item)
{
    Node *new_node = new Node(item);
    if (head == nullptr)
        head = new_node;
    else
    {
        new_node->next = head;
        head = new_node;
    }
    return true;
}
LancelotBag::LancelotBag() : BaseBag(16) {}
bool LancelotBag::insertFirst(BaseItem *item)
{
    if (countItem() == maxItems)
        return false;
    else
    {
        Node *new_node = new Node(item);
        if (head == nullptr)
            head = new_node;
        else
        {
            new_node->next = head;
            head = new_node;
        }
    }
    return true;
}
DragonBag::DragonBag() : BaseBag(14) {}
bool DragonBag::insertFirst(BaseItem *item)
{
    if (countItem() == maxItems)
        return false;
    else
    {
        Node *new_node = new Node(item);
        if (head == nullptr)
            head = new_node;
        else
        {
            new_node->next = head;
            head = new_node;
        }
    }
    return true;
}
NormalBag::NormalBag() : BaseBag(19) {}
bool NormalBag::insertFirst(BaseItem *item)
{
    if (countItem() == maxItems)
        return false;
    else
    {
        Node *new_node = new Node(item);
        if (head == nullptr)
            head = new_node;
        else
        {
            new_node->next = head;
            head = new_node;
        }
    }
    return true;
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
    BaseItem *item;
    ifs.open(file_armyknights);
    getline(ifs, line);
    ss << line;
    ss >> this->armyNum;
    int id = 1;
    army = new BaseKnight *[armyNum];
    int maxhp, level, gil, antidote, phoenixdownI;
    for (int i = 0; i < armyNum; i++)
    {
        ss.clear();
        ss.str("");
        content = "";
        getline(ifs, content);
        ss << content;
        ss >> maxhp >> level >> phoenixdownI >> gil >> antidote;
        army[i] = BaseKnight::create(id++, maxhp, level, phoenixdownI, gil, antidote);
        if (army[i]->knightType == PALADIN)
            army[i]->bag = new PaladinBag();
        else if (army[i]->knightType == LANCELOT)
            army[i]->bag = new LancelotBag();
        else if (army[i]->knightType == DRAGON)
            army[i]->bag = new DragonBag();
        else
            army[i]->bag = new NormalBag();
        if (army[i]->phoenixdownI != 0)
        {
            item = new PhoenixDownI();
            for (int j = 0; j < army[i]->phoenixdownI; j++)
                army[i]->bag->insertFirst(item);
        }
        if (army[i]->antidote != 0 && army[i]->knightType != DRAGON)
        {
            item = new Antidote();
            for (int j = 0; j < army[i]->antidote; j++)
                army[i]->bag->insertFirst(item);
        }
    }
}

ArmyKnights::~ArmyKnights()
{
    for (int i = 0; i < armyNum; i++)
        delete army[i];
    delete[] army;
}

bool ArmyKnights::fight(BaseOpponent *opponent)
{
    if (armyNum == 0)
        return false;
    int id = armyNum - 1;
    int tempHP = army[id]->hp;
    if (opponent->OpponentType == "MadBear" || opponent->OpponentType == "Bandit" || opponent->OpponentType == "LordLupin" || opponent->OpponentType == "Elf" || opponent->OpponentType == "Troll")
    {
        if (army[id]->level < opponent->levelO && army[id]->knightType != LANCELOT && army[id]->knightType != PALADIN)
            army[id]->hp -= opponent->baseDamage * (opponent->levelO - army[id]->level);
        else if (army[id]->knightType == LANCELOT || army[id]->knightType == PALADIN || army[id]->level >= opponent->levelO)
            army[id]->gil += opponent->gil;
    }
    else if (opponent->OpponentType == "Tornbery")
    {
        if (army[id]->level >= opponent->levelO)
        {
            army[id]->poisened = false;
            army[id]->level++;
        }
        else if (army[id]->knightType != DRAGON)
            army[id]->poisened = true;
        if (army[id]->poisened == true)
        {
            if (army[id]->bag->get(ANTIDOTE) == nullptr)
            {
                if (army[id]->bag->countItem() <= 3)
                {
                    int del = army[id]->bag->countItem();
                    for (int i = 0; i < del; i++)
                        army[id]->bag->deleteItem(army[id]->bag->head->data);
                }
                else
                    for (int i = 0; i < 3; i++)
                        army[id]->bag->deleteItem(army[id]->bag->head->data);
                army[id]->hp -= 10;
            }
        }
    }
    else if (opponent->OpponentType == "QueenofCards")
    {
        if (army[id]->level >= opponent->levelO)
            army[id]->gil *= 2;
        else if (army[id]->knightType != PALADIN)
            army[id]->gil = int(army[id]->gil / 2);
    }
    else if (opponent->OpponentType == "NinadeRings")
    {
        if (army[id]->gil >= 50 || army[id]->knightType == PALADIN)
            if (army[id]->hp < int((army[id]->maxhp) / 3))
            {
                if (army[id]->knightType != PALADIN)
                    army[id]->gil -= 50;
                army[id]->hp += int((army[id]->maxhp) / 5);
            }
    }
    else if (opponent->OpponentType == "DurianGarden")
        army[id]->hp = army[id]->maxhp;
    else if (opponent->OpponentType == "OmegaWeapon" && opponent->appear == false)
    {
        if ((army[id]->hp == army[id]->maxhp && army[id]->level == 10) || army[id]->knightType == DRAGON)
        {
            army[id]->level = 10;
            army[id]->gil = 999;
            opponent->appear = true;
        }
        else
            army[id]->hp = 0;
    }
    else if (opponent->OpponentType == "Hades" && opponent->appear == false)
    {
        if ((army[id]->level == 10) || (army[id]->knightType == PALADIN && army[id]->level >= 8))
        {
            if (this->PaladinShield == false)
                this->PaladinShield = true;
            opponent->appear = true;
        }
        else
            army[id]->hp = 0;
    }
    if (army[id]->bag->countItem() > 0)
    {
        Node *tempNode = army[id]->bag->head;
        while (tempNode != nullptr)
        {
            if ((army[id]->hp < tempHP && tempNode->data->itemType != ANTIDOTE) || tempNode->data->itemType == ANTIDOTE)
            {
                if (tempNode->data->canUse(army[id]) == true)
                {
                    tempNode->data->use(army[id]);
                    BaseItem *data = tempNode->data;
                    tempNode = tempNode->next;
                    army[id]->bag->deleteItem(data);
                    break;
                }
                else
                    tempNode = tempNode->next;
            }
            else
                tempNode = tempNode->next;
        }
    }
    if (army[id]->hp <= 0 && army[id]->hp < tempHP)
        if (army[id]->gil >= 100)
        {
            army[id]->gil -= 100;
            army[id]->hp = int(army[id]->maxhp / 2);
        }
    if (army[id]->hp > 999)
        army[id]->hp = 999;
    if (army[id]->level > 10)
        army[id]->level = 10;

    if (army[id]->gil > 999)
    {
        int t = 1;
        int excessiveGil = army[id]->gil - 999;
        army[id]->gil = 999;
        while (excessiveGil > 0)
        {
            if (t > id)
                break;
            int excessive = 999 - army[id - t]->gil;
            if (excessiveGil <= excessive)
            {
                army[id - t]->gil += excessiveGil;
                break;
            }
            else
            {
                army[id - t]->gil = 999;
                excessiveGil -= excessive;
            }
            t++;
        }
    }
    if (army[id]->phoenixdownI > 5)
    {
        int t = 1;
        int excessivePDI = army[id]->phoenixdownI - 5;
        army[id]->phoenixdownI = 5;
        while (excessivePDI > 0)
        {
            if (t > id)
                break;
            int excessive = 5 - army[id - t]->phoenixdownI;
            if (excessivePDI <= excessive)
            {
                army[id - t]->phoenixdownI += excessivePDI;
                break;
            }
            else
            {
                army[id - t]->phoenixdownI = 5;
                excessivePDI -= excessive;
            }
            t++;
        }
    }
    if (army[id]->antidote > 5)
    {
        int t = 1;
        int excessiveAntidote = army[id]->antidote - 5;
        army[id]->antidote = 5;
        while (excessiveAntidote > 0)
        {
            if (t > id)
                break;
            int excessive = 5 - army[id - t]->antidote;
            if (excessiveAntidote <= excessive)
            {
                army[id - t]->antidote += excessiveAntidote;
                break;
            }
            else
            {
                army[id - t]->antidote = 5;
                excessiveAntidote -= excessive;
            }
            t++;
        }
    }

    if (army[id]->hp <= 0)
        return false;
    return true;
}

bool ArmyKnights::adventure(Events *events)
{
    BaseItem *item;
    BaseOpponent *opponent;
    bool appearOmegaWeapon = false;
    bool appearHades = false;
    int i = 0;
    while (i < events->evntnum)
    {
        int eveID = events->get(i);
        if (eveID >= 1 && eveID <= 11)
        {
            switch (eveID)
            {
            case 1:
                opponent = new MadBear(i);
                break;
            case 2:
                opponent = new Bandit(i);
                break;
            case 3:
                opponent = new LordLupin(i);
                break;
            case 4:
                opponent = new Elf(i);
                break;
            case 5:
                opponent = new Troll(i);
                break;
            case 6:
                opponent = new Tornbery(i);
                break;
            case 7:
                opponent = new QueenofCards(i);
                break;
            case 8:
                opponent = new NinaDeRings();
                break;
            case 9:
                opponent = new DurianGarden();
                break;
            case 10:
                opponent = new OmegaWeapon(appearOmegaWeapon);
                break;
            case 11:
                opponent = new Hades(appearHades);
                break;
            default:
                break;
            }
            if ((eveID == 10 && appearOmegaWeapon == true) || (eveID == 11 && appearHades == true))
            {
                i++;
                printInfo();
                continue;
            }
            if (fight(opponent) == false)
            {
                if (armyNum >= 1)
                {
                    delete army[armyNum - 1];
                    armyNum--;
                }
                printInfo();
                if (armyNum == 0)
                    return false;
                i++;
            }
            else
            {
                if (opponent->OpponentType == "Hades" && opponent->appear == true)
                    appearHades = true;
                if (opponent->OpponentType == "OmegaWeapon" && opponent->appear == true)
                    appearOmegaWeapon = true;
                printInfo();
                i++;
            }
        }
        else
        {
            int id = this->armyNum - 1;
            switch (eveID)
            {
            case 112:
                item = new PhoenixDownII();
                if (army[id]->bag->insertFirst(item) == false)
                {
                    int k = 1;
                    while (k <= id)
                    {
                        if (army[id - k]->bag->insertFirst(item) == false)
                            k++;
                        else
                            break;
                    }
                }
                break;
            case 113:
                item = new PhoenixDownIII();
                if (army[id]->bag->insertFirst(item) == false)
                {
                    int k = 1;
                    while (k <= id)
                    {
                        if (army[id - k]->bag->insertFirst(item) == false)
                            k++;
                        else
                            break;
                    }
                }
                break;
            case 114:
                item = new PhoenixDownIV();
                if (army[id]->bag->insertFirst(item) == false)
                {
                    int k = 1;
                    while (k <= id)
                    {
                        if (army[id - k]->bag->insertFirst(item) == false)
                            k++;
                        else
                            break;
                    }
                }
                break;
            case 95:
                this->PaladinShield = true;
                break;
            case 96:
                this->LancelotSpear = true;
                break;
            case 97:
                this->GuinevereHair = true;
                break;
            case 98:
                if (PaladinShield == true && LancelotSpear == true && GuinevereHair == true)
                    this->ExcaliburSword = true;
                else
                    this->ExcaliburSword = false;
                break;
            case 99:
                opponent = new Ultimecia;
                if (ExcaliburSword == true)
                {
                    printInfo();
                    return true;
                }
                else if (LancelotSpear == true && PaladinShield == true && GuinevereHair == true)
                {
                    int i = this->armyNum - 1;
                    while (i >= 0)
                    {
                        if (army[i]->knightType != NORMAL)
                        {
                            double knightBaseDamage;
                            if (army[i]->knightType == DRAGON)
                                knightBaseDamage = 0.075;
                            else if (army[i]->knightType == PALADIN)
                                knightBaseDamage = 0.06;
                            else if (army[i]->knightType == LANCELOT)
                                knightBaseDamage = 0.05;
                            int UltiDamage = army[i]->hp * army[i]->level * knightBaseDamage;
                            opponent->UltiHP -= UltiDamage;
                            if (opponent->UltiHP > 0)
                            {
                                if (i < armyNum - 1)
                                    for (int j = i; j < this->armyNum - 1; j++)
                                        army[j] = army[j + 1];
                                i--;
                                this->armyNum--;
                            }
                            if (opponent->UltiHP <= 0)
                            {
                                printInfo();
                                return true;
                            }
                        }
                        else
                            i--;
                    }
                    if (opponent->UltiHP > 0)
                    {
                        this->armyNum = 0;
                        printInfo();
                        return false;
                    }
                }
                else
                {
                    this->armyNum = 0;
                    printInfo();
                    return false;
                }
                break;
            default:
                break;
            }
            printInfo();
            i++;
        }
    }
    if (armyNum > 0 && army[armyNum - 1]->hp > 0)
        return true;
    return false;
}
int ArmyKnights::count() const { return this->armyNum; }
BaseKnight *ArmyKnights::lastKnight() const { return army[armyNum - 1]; }
bool ArmyKnights::hasPaladinShield() const
{
    if (this->PaladinShield == true)
        return true;
    return false;
}
bool ArmyKnights::hasLancelotSpear() const
{
    if (this->LancelotSpear == true)
        return true;
    return false;
}
bool ArmyKnights::hasGuinevereHair() const
{
    if (this->GuinevereHair == true)
        return true;
    return false;
}
bool ArmyKnights::hasExcaliburSword() const
{
    if (this->ExcaliburSword == true)
        return true;
    return false;
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

void ArmyKnights::printResult(bool win) const { cout << (win ? "WIN" : "LOSE") << endl; }
/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure()
{
    armyKnights = nullptr;
    events = nullptr;
}

void KnightAdventure::loadArmyKnights(const string &file_armyknights) { armyKnights = new ArmyKnights(file_armyknights); }
void KnightAdventure::loadEvents(const string &file_events) { events = new Events(file_events); }
void KnightAdventure::run()
{
    if (armyKnights->adventure(events) == true)
        armyKnights->printResult(true);
    else
        armyKnights->printResult(false);
    armyKnights->~ArmyKnights();
    events->~Events();
}

/* * * END implementation of class KnightAdventure * * */