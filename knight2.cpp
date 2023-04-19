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
        c++;
}

int Events::count() const
{
    return this->evntnum;
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
BaseOpponent::BaseOpponent(string OpponentType, int baseDamage, int gil, int eventid) : OpponentType(OpponentType), baseDamage(baseDamage), gil(gil), eventid(eventid), appear(0) {}
MadBear::MadBear(int i) : BaseOpponent("MadBear", 10, 100, 1) { this->levelO = (i + this->eventid) % 10 + 1; }
Bandit::Bandit(int i) : BaseOpponent("Bandit", 15, 150, 2) { this->levelO = (i + this->eventid) % 10 + 1; }
LordLupin::LordLupin(int i) : BaseOpponent("LordLupin", 45, 450, 3) { this->levelO = (i + this->eventid) % 10 + 1; }
Elf::Elf(int i) : BaseOpponent("Elf", 75, 750, 4) { this->levelO = (i + this->eventid) % 10 + 1; }
Troll::Troll(int i) : BaseOpponent("Troll", 95, 800, 5) { this->levelO = (i + this->eventid) % 10 + 1; }
Tornbery::Tornbery(int i) : BaseOpponent("Tornbery", 0, 0, 6) { this->levelO = (i + this->eventid) % 10 + 1; }
QueenofCards::QueenofCards(int i) : BaseOpponent("QueenofCards", 0, 0, 7) { this->levelO = (i + this->eventid) % 10 + 1; }
NinaDeRings::NinaDeRings() : BaseOpponent("NinadeRings", 0, 0, 8) {}
DurianGarden::DurianGarden() : BaseOpponent("DurianGarden", 0, 0, 9) {}
OmegaWeapon::OmegaWeapon() : BaseOpponent("OmegaWeapon", 0, 0, 10) {}
Hades::Hades() : BaseOpponent("Hades", 0, 0, 11) {}
Ultimecia::Ultimecia() : BaseOpponent("Ultimecia", 0, 0, 99) { UltiHP = 5000; }
/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class BaseKnight * * */
BaseKnight::BaseKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote, KnightType knightType) : id(id), maxhp(maxhp), level(level), gil(gil), antidote(antidote), phoenixdownI(phoenixdownI), hp(maxhp), knightType(knightType), poisened(false) {}
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
BaseKnight *BaseKnight::create(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote)
{
    BaseKnight *knight;
    if (snt(maxhp) == 1)
        knight = new PaladinKnight(id, maxhp, level, phoenixdownI, gil, antidote, PALADIN);
    else if (maxhp == 888)
        knight = new LancelotKnight(id, maxhp, level, phoenixdownI, gil, antidote, LANCELOT);
    else if (pythagoras(maxhp))
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
    // the numbers of Antidote in BaseBag of a knight can't bigger than 5
    if (knight->antidote >= 5)
        return false;
    else
        return true;
}
void Antidote::use(BaseKnight *knight)
{
    if (knight->antidote >= 1 && knight->poisened == true)
        knight->poisened = false;
}
PhoenixDownI::PhoenixDownI() : BaseItem(PHOENIXI) {}
bool PhoenixDownI::canUse(BaseKnight *knight)
{
    if (knight->hp <= 0)
        return true;
    else
        return false;
}
void PhoenixDownI::use(BaseKnight *knight)
{
    if (knight->phoenixdownI >= 1 && canUse(knight) == true)
        knight->hp = knight->maxhp;
}
PhoenixDownII::PhoenixDownII() : BaseItem(PHOENIXII) {}
bool PhoenixDownII::canUse(BaseKnight *knight)
{
    if (knight->hp < int((knight->hp) / 4))
        return true;
    else
        return false;
}
void PhoenixDownII::use(BaseKnight *knight)
{
    if (canUse(knight) == true)
        knight->hp = knight->maxhp;
}
PhoenixDownIII::PhoenixDownIII() : BaseItem(PHOENIXIII) {}
bool PhoenixDownIII::canUse(BaseKnight *knight)
{
    if (knight->hp < int((knight->maxhp) / 3))
        return true;
    else
        return false;
}
void PhoenixDownIII::use(BaseKnight *knight)
{
    if (canUse(knight) == true)
    {
        if (knight->hp <= 0)
            knight->hp = int((knight->maxhp) / 3);
        else
            knight->hp += int((knight->maxhp) / 4);
    }
}
PhoenixDownIV::PhoenixDownIV() : BaseItem(PHOENIXIV) {}
bool PhoenixDownIV::canUse(BaseKnight *knight)
{
    if (knight->hp < int((knight->maxhp) / 2))
        return true;
    else
        return false;
}
void PhoenixDownIV::use(BaseKnight *knight)
{
    if (canUse(knight) == true)
    {
        if (knight->hp <= 0)
            knight->hp = int((knight->maxhp) / 2);
        else
            knight->hp += int((knight->maxhp) / 5);
    }
}
/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class BaseBag * * */
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

bool BaseBag::search(BaseItem *item)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data->itemType == item->itemType)
            return true;
        temp = temp->next;
    }
    return false;
}

BaseItem *BaseBag::get(ItemType itemType)
{
    Node *item;
    if (search(item->data) == 0)
        return nullptr;

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
    Node *prevX;
    prevX->data = data;
    Node *currX = prevX;
    currX = currX->next;
    // Swap next pointers
    Node *temp = head;
    head = currX->next;
    currX->next = temp;
    // delete head
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
LancelotBag::LancelotBag() : BaseBag() {}
bool LancelotBag::insertFirst(BaseItem *item)
{
    int count = countItem();
    if (count >= maxItems)
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
        return true;
    }
}
DragonBag::DragonBag() : BaseBag() {}
bool DragonBag::insertFirst(BaseItem *item)
{
    int count = countItem();
    if (count >= maxItems)
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
        return true;
    }
}
NormalBag::NormalBag() : BaseBag() {}
bool NormalBag::insertFirst(BaseItem *item)
{
    int count = countItem();
    if (count >= maxItems)
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
        return true;
    }
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
                (army[i]->bag)->insertFirst(item);
        }
        if (army[i]->antidote != 0)
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
int ArmyKnights::compare(BaseItem *arr[4])
{
    int n;
    for (int i = 0; i < 3; i++)
    {
        if (arr[i] != nullptr)
            n++;
        else
        {
            BaseItem *temp1 = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp1;
        }
        for (int j = i + 1; j < 4; j++)
        {
            if (arr[i] > arr[j] && arr[j] != nullptr)
            {
                BaseItem *temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return n;
}

bool ArmyKnights::fight(BaseOpponent *opponent)
{
    int id = armyNum - 1;
    if (opponent->OpponentType == "MadBear" || opponent->OpponentType == "Bandit" || opponent->OpponentType == "LordLupin" || opponent->OpponentType == "Elf" || opponent->OpponentType == "Troll")
    {
        cout<<endl;
        if (army[id]->level < opponent->levelO && army[id]->knightType != LANCELOT)
            army[id]->hp -= opponent->baseDamage * (opponent->levelO - army[id]->level);
        else if (army[id]->level < opponent->levelO && army[id]->knightType == LANCELOT)
            army[id]->gil += opponent->gil;
        else if (army[id]->level >= opponent->levelO)
            army[id]->gil += opponent->gil;
    }
    else if (opponent->OpponentType == "Tornbery")
    {
        cout<<endl;
        if (army[id]->level >= opponent->levelO)
            army[id]->level++;
        else
            army[id]->poisened = true;
        if (army[id]->poisened == true)
        {
            if (army[id]->bag->get(ANTIDOTE) != nullptr)
                army[id]->poisened = false;
        }
        else
        {
            if (army[id]->bag->countItem() <= 3)
                army[id]->bag = nullptr;
            else
            {
                army[id]->bag->deleteItem(army[id]->bag->head->data);
                army[id]->bag->deleteItem(army[id]->bag->head->data);
                army[id]->bag->deleteItem(army[id]->bag->head->data);
                army[id]->hp -= 10;
            }
        }
    }
    else if (opponent->OpponentType == "QueenofCards")
    {
        if (army[id]->level >= opponent->levelO)
        {
            army[id]->gil *= 2;
            if (army[id]->gil > 999)
            {
                int t = 1;
                int excessive = army[id]->gil - 999;
                while (excessive > 0)
                {
                    army[id - t]->gil += excessive;
                    army[id]->gil = 999;
                    excessive = army[id - t]->gil - 999;
                    t++;
                    if (t > armyNum)
                        continue;
                }
            }
        }
        else
            army[id]->gil /= 2;
    }
    else if (opponent->OpponentType == "NinadeRings")
    {
        if (army[id]->gil >= 50)
            if (army[id]->hp < int((army[id]->maxhp) / 3))
            {
                army[id]->gil -= 50;
                army[id]->hp += int((army[id]->maxhp) / 5);
            }
    }
    else if (opponent->OpponentType == "DurianGarden")
        army[id]->hp = army[id]->maxhp;
    else if (opponent->OpponentType == "OmegaWeapon")
    {
        if (opponent->appear == 0)
        {
            if ((army[id]->hp == army[id]->maxhp && army[id]->level == 10) || army[id]->knightType == DRAGON)
            {
                opponent->appear = 1;
                army[id]->level = 10;
                army[id]->gil = 999;
            }
            else
                army[id]->hp = 0;
        }
    }
    else if (opponent->OpponentType == "Hades")
    {
        if (opponent->appear == 0)
        {
            if ((army[id]->level == 10) || (army[id]->knightType == PALADIN && army[id]->level >= 8))
            {
                opponent->appear = 1;
                if (this->PaladinShield == false)
                    this->PaladinShield = true;
            }
            else
                army[id]->hp = 0;
        }
    }

    BaseItem *temp1 = army[id]->bag->get(PHOENIXI);
    BaseItem *temp2 = army[id]->bag->get(PHOENIXII);
    BaseItem *temp3 = army[id]->bag->get(PHOENIXIII);
    BaseItem *temp4 = army[id]->bag->get(PHOENIXIV);
    BaseItem *arr[4] = {temp1, temp2, temp3, temp4};
    int n = compare(arr);
    cout<<n<<endl;
    /*for (int i = 0; i < n; i++)
    {
        if (arr[i]->canUse(army[id]) == true)
        {
            arr[i]->use(army[id]);
            Node *prevX;
            prevX->data = army[id]->bag->get(arr[i]->itemType);
            army[id]->bag->deleteItem(prevX->data);
        }
    }*/

    if (army[id]->hp <= 0)
        return false;
    return true;
}

bool ArmyKnights::adventure(Events *events)
{
    BaseItem *item;
    BaseOpponent *opponent;
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
                opponent = new OmegaWeapon();
                break;
            case 11:
                opponent = new Hades();
                break;
            }
            if (fight(opponent) == false)
            {
                delete army[armyNum - 1];
                armyNum--;
            }
            else
            {
                printInfo();
                i++;
            }
        }
        else
        {
            switch (eveID)
            {
            case 112:
                item = new PhoenixDownII;
                army[i]->bag->insertFirst(item);
                break;
            case 113:
                item = new PhoenixDownIII;
                army[i]->bag->insertFirst(item);
                break;
            case 114:
                item = new PhoenixDownIV;
                army[i]->bag->insertFirst(item);
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
                this->ExcaliburSword = true;
                break;
            default:
                opponent = new Ultimecia;
                if (hasExcaliburSword() == true)
                {
                    printInfo();
                    return true;
                }
                else if (hasLancelotSpear() == true && hasPaladinShield() == true && hasGuinevereHair() == true)
                {
                    while (this->armyNum > 0)
                    {
                        int i = this->armyNum - 1;
                        if (army[i]->knightType == DRAGON || army[i]->knightType == PALADIN || army[i]->knightType == LANCELOT)
                        {
                            double knightBaseDamage;
                            if (army[i]->knightType == DRAGON)
                                knightBaseDamage = 0.075;
                            else if (army[i]->knightType == PALADIN)
                                knightBaseDamage = 0.06;
                            else
                                knightBaseDamage = 0.05;
                            int UltiDamage = army[i]->hp * army[i]->level * knightBaseDamage;
                            opponent->UltiHP -= UltiDamage;
                            if (opponent->UltiHP >= 0)
                                this->armyNum--;
                            if (opponent->UltiHP <= 0 && this->armyNum > 0)
                            {
                                printInfo();
                                return true;
                            }
                            // coi lai tai de xay ra con tro lo lung
                        }
                    }
                }
                break;
            }
            printInfo();
            i++;
        }
    }
    return false;
}
int ArmyKnights::count() const
{
    return this->armyNum;
}
BaseKnight *ArmyKnights::lastKnight() const
{
    return army[armyNum - 1];
}
bool ArmyKnights::hasPaladinShield() const
{
    if (this->PaladinShield == true)
        return true;
    else
        return false;
}
bool ArmyKnights::hasLancelotSpear() const
{
    if (this->LancelotSpear == true)
        return true;
    else
        return false;
}
bool ArmyKnights::hasGuinevereHair() const
{
    if (this->GuinevereHair == true)
        return true;
    else
        return false;
}
bool ArmyKnights::hasExcaliburSword() const
{
    if (this->ExcaliburSword == true)
        return true;
    else
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

void KnightAdventure::loadArmyKnights(const string &file_armyknights)
{
    armyKnights = new ArmyKnights(file_armyknights);
}
void KnightAdventure::loadEvents(const string &file_events)
{
    events = new Events(file_events);
}
void KnightAdventure::run()
{
    if (armyKnights->adventure(events) == true)
        armyKnights->printResult(true);
    else
        armyKnights->printResult(false);
}

/* * * END implementation of class KnightAdventure * * */