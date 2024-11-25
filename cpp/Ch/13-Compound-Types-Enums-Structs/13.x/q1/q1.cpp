#include <iostream>
#include <string_view>

struct Monster
{
    // Monster types
    enum Type
    {
        ogre,
        dragon,
        orc,
        giant_spider,
        slime,
    };

    Type type{};
    std::string_view name{};
    int health{};
};

constexpr std::string_view getMonsterType(Monster::Type type)
{
    switch (type)
    {
    case Monster::ogre:         return "Ogre";
    case Monster::dragon:       return "dragon";
    case Monster::orc:          return "orc";
    case Monster::giant_spider: return "giant_spider";
    case Monster::slime:        return "slime";
    }

    return "Unknown";
}

void printMonster(const Monster& monster)
{
    std::cout << "This " << getMonsterType(monster.type) <<
        " is named " << monster.name <<
        " and has " << monster.health <<
        " health.\n";
}

int main()
{
    Monster ogre{ Monster::ogre, "Torg", 145 };
    Monster slime{ Monster::slime, "Blurp", 23 };

    printMonster(ogre);
    printMonster(slime);

    return 0;
}
