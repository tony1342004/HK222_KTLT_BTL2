#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

class Events
{
    int evntnum;
    int *evnt;

public:
    Events(const string &file_events);
    int count() const;
    int get(int i) const;
    ~Events();
};

class BaseOpponent
{
};
class MadBear : public BaseOpponent
{
};
class Bandit : public BaseOpponent
{
};
class LordLupin : public BaseOpponent
{
};
class Elf : public BaseOpponent
{
};
class Troll : public BaseOpponent
{
};
class Tornbery : public BaseOpponent
{
};
class QueenofCards : public BaseOpponent
{
};
class NinaDeRings : public BaseOpponent
{
};
class DurianGarden : public BaseOpponent
{
};
class OmegaWeapon : public BaseOpponent
{
};
class Hades : public BaseOpponent
{
};

class BaseKnight
{
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag *bag;
    KnightType knightType;
    int phoenixdownI;

public:
    static int snt(int a);
    static int pythagoras(int n);
    static BaseKnight *create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    KnightType getType() const;
};
enum ItemType
{
    Antidote = 1,
    PhoenixI,
    PhoenixII,
    PhoenixIII,
    PhoenixIV
};

class BaseItem
{
public:
    virtual bool canUse(BaseKnight *knight) = 0;
    virtual void use(BaseKnight *knight) = 0;
};

class Antidote : public BaseItem
{
};
class PhoenixDownI : public BaseItem
{
};
class PhoenixDownII : public BaseItem
{
};
class PhoenixDownIII : public BaseItem
{
};
class PhoenixDownIV : public BaseItem
{
};

// Making a node struct containing an int data and a pointer
// to next node
struct Node
{
    string data;
    Node *next;
    // Parameterised constructor with default argument
    Node(string val) : data(val), next(nullptr) {}
    // Parameterise constructor
    Node(string val, Node *tempNext) : data(val), next(tempNext) {}
};

class LinkedList
{
    // Head pointer
    Node *head;

public:
    // default constructor. Initializing head pointer
    LinkedList() : head(nullptr) {}

    // inserting elements (At start of the list)
    void insert(string val);

    // loop over the list. return true if element found
    bool search(string val);
    void remove(string val);
    void display();
};

class BaseBag
{
    BaseKnight *knight;

public:
    virtual bool insertFirst(BaseItem *item);
    virtual BaseItem *get(ItemType itemType);
    virtual string toString() const;
};

enum KnightType
{
    PALADIN = 1,
    LANCELOT,
    DRAGON,
    NORMAL
};

class PaladinKnight : public BaseKnight
{
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        this->phoenixdownI = phoenixdownI;
        this->knightType = PALADIN;
    }
};
class LancelotKnight : public BaseKnight
{
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        this->phoenixdownI = phoenixdownI;
        this->knightType = LANCELOT;
    }
};
class DragonKnight : public BaseKnight
{
public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        this->phoenixdownI = phoenixdownI;
        this->knightType = DRAGON;
    }
};
class NormalKnight : public BaseKnight
{
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    {
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->level = level;
        this->gil = gil;
        this->antidote = antidote;
        this->phoenixdownI = phoenixdownI;
        this->knightType = NORMAL;
    }
};

class ArmyKnights
{
    BaseKnight **army;
    int armyNum;

public:
    ArmyKnights(const string &file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent *opponent);
    bool adventure(Events *events);
    int count() const;
    BaseKnight *lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class KnightAdventure
{
private:
    ArmyKnights *armyKnights;
    Events *events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__