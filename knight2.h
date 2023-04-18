#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

class BaseKnight;
class BaseBag;
class ArmyKnights;
class Events
{
    int evntnum;
    int *evnt;

public:
    friend ArmyKnights;
    Events(const string &file_events);
    int count() const;
    int get(int i) const;
    ~Events();
};

enum ItemType
{
    ANTIDOTE = 0,
    PHOENIXI,
    PHOENIXII,
    PHOENIXIII,
    PHOENIXIV
};

class BaseItem
{
public: 
    ItemType itemType;
    BaseItem(ItemType itemType);
    virtual bool canUse(BaseKnight *knight) = 0;
    virtual void use(BaseKnight *knight) = 0;
};

class Antidote : public BaseItem
{
public:
    Antidote();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PhoenixDownI : public BaseItem
{
public:
    PhoenixDownI();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PhoenixDownII : public BaseItem
{
public:
    PhoenixDownII();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PhoenixDownIII : public BaseItem
{
public:
    PhoenixDownIII();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PhoenixDownIV : public BaseItem
{
public:
    PhoenixDownIV();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};

enum KnightType
{
    PALADIN = 0,
    LANCELOT,
    DRAGON,
    NORMAL
};

class BaseKnight
{
protected:
    int id, hp, maxhp, level, gil, antidote, phoenixdownI;
    bool poisened;
    BaseBag *bag;
    KnightType knightType;

public:
    BaseKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote, KnightType knightType);
    friend ArmyKnights;
    friend PhoenixDownI;
    friend PhoenixDownII;
    friend PhoenixDownIII;
    friend PhoenixDownIV;
    friend Antidote;
    static int snt(int a);
    static int pythagoras(int n);
    static BaseKnight *create(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote);
    string toString() const;
};

class PaladinKnight : public BaseKnight
{
public:
    PaladinKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote, KnightType knightType);
};
class LancelotKnight : public BaseKnight
{
public:
    LancelotKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote, KnightType knightType);
};
class DragonKnight : public BaseKnight
{
public:
    DragonKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote, KnightType knightType);
};
class NormalKnight : public BaseKnight
{
public:
    NormalKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote, KnightType knightType);
};

class BaseOpponent
{
protected:
    int baseDamage, gil, levelO, eventid, appear, UltiHP;
    string OpponentType;

public:
    friend ArmyKnights;
    friend PhoenixDownI;
    friend PhoenixDownII;
    friend PhoenixDownIII;
    friend PhoenixDownIV;
    friend Antidote;
    BaseOpponent(string OpponentType, int baseDamage, int gil, int eventid);
};
class MadBear : public BaseOpponent
{
public:
    MadBear(int i);
};
class Bandit : public BaseOpponent
{
public:
    Bandit(int i);
};
class LordLupin : public BaseOpponent
{
public:
    LordLupin(int i);
};
class Elf : public BaseOpponent
{
public:
    Elf(int i);
};
class Troll : public BaseOpponent
{
public:
    Troll(int i);
};
class Tornbery : public BaseOpponent
{
public:
    Tornbery(int i);
};
class QueenofCards : public BaseOpponent
{
public:
    QueenofCards(int i);
};
class NinaDeRings : public BaseOpponent
{
public:
    NinaDeRings();
};
class DurianGarden : public BaseOpponent
{
public:
    DurianGarden();
};
class OmegaWeapon : public BaseOpponent
{
public:
    OmegaWeapon();
};
class Hades : public BaseOpponent
{
public:
    Hades();
};
class Ultimecia : public BaseOpponent
{
public:
    Ultimecia();
};

// node in linked list
struct Node
{
    BaseItem *data;
    Node *next;
    // default
    Node(BaseItem *val) : data(val), next(nullptr) {}
    Node(BaseItem *val, Node *Next) : data(val), next(Next) {}
};

class BaseBag
{
    BaseKnight *knight;

protected:
    Node *head;

public:
    friend ArmyKnights;
    BaseBag();
    virtual bool insertFirst(BaseItem *item) = 0;
    BaseItem *get(ItemType itemType);
    string toString();
    void deleteItem(BaseItem *prevX);
    bool search(BaseItem *item);
    int countItem();
};

class PaladinBag : public BaseBag
{
public:
    PaladinBag();
    bool insertFirst(BaseItem *item);
};
class LancelotBag : public BaseBag
{
    int maxItems = 14;

public:
    LancelotBag();
    bool insertFirst(BaseItem *item);
};
class DragonBag : public BaseBag
{
    int maxItems = 16;

public:
    DragonBag();
    bool insertFirst(BaseItem *item);
};
class NormalBag : public BaseBag
{
    int maxItems = 19;

public:
    NormalBag();
    bool insertFirst(BaseItem *item);
};

class ArmyKnights
{
    BaseKnight **army;
    int armyNum;
    bool PaladinShield;
    bool LancelotSpear;
    bool GuinevereHair;
    bool ExcaliburSword;

public:
    ArmyKnights(const string &file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent *opponent);
    bool adventure(Events *events);
    int count() const;
    BaseKnight *lastKnight() const;
    int compare(BaseItem *arr[4]);

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
    // xu ly, cap nhat hp cua hiep si trong event
    ArmyKnights *armyKnights;
    Events *events;

public:
    KnightAdventure();

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__