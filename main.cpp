#include <iostream>
#include <vector>

int bonusCap = 104;
std::vector tankStats{"str", "con", "dex", "qui"};
std::vector casterStats{"con", "dex", "acu"};
std::vector hybridStats{"str", "con", "dex", "qui", "acu"};
std::vector resists{"crush", "slash", "thrust", "heat", "cold", "matter", "energy", "body", "spirit"};
std::vector casterClasses{"Animist", "Bonedancer","Runemaster", "Cabalist", "Cleric", "Bainshee", "Healer", "Druid", "Bard","Shaman", "Spiritmaster","Enchanter", "Mentalist", "Eldritch", "Necromancer", "Sorcerer", "Theurgist", "Wizard"};
std::vector tankClasses{"Infiltrator", "Mercenary", "Armsman", "Savage", "Berserker", "Blademaster", "Shadowblade", "Hero", "Nightshade","Warrior", "Paladin"};
std::vector hybridClasses{"Friar",  "Heretic", "Hunter",  "Champion", "Minstrel", "Skald",  "Thane", "Reaver","Valkyrie","Ranger", "Valewalker", "Warden", "Scout"};

std::string chestpiece{ };
std::string arms{ };
std::string legs{ };
std::string helm{ };
std::string hands{ };
std::string boots{ };

int getNecessaryStats() {

    std::cout << "Enter the class you would like to generate a template for: ";

    std::string className{};
    std::cin >> className;

    std::size_t casterClassesLength { casterClasses.size() };
    std::size_t casterStatsLength { casterStats.size() };

    std::size_t tankClassesLength { tankClasses.size() };
    std::size_t tankStatsLength { tankStats.size() };

    std::size_t hybridClassesLength { hybridClasses.size() };
    std::size_t hybridStatsLength { hybridStats.size() };

    for (std::size_t index{ 0 }; index < casterClassesLength; ++index) 
    {
        if (casterClasses[index] == className)
        {
            std::cout << "Necessary Stats: " << '\n';
            for (std::size_t index2{ 0 }; index2 < casterStatsLength; ++index2)
                std::cout << casterStats[index2] << " ";
        }
        else
        {
            std::cout << "";
        }
            
    }
        

    for (std::size_t index{ 0 }; index < tankClassesLength; ++index)
    {
        if (tankClasses[index] == className)
        {
            std::cout << "Necessary Stats: " << '\n';
            for (std::size_t index2{ 0 }; index2 < tankStatsLength; ++index2)
                std::cout << tankStats[index2] << " ";
        }
        else
        {
            std::cout << "";
        }
    }
        

    for (std::size_t index{ 0 }; index < hybridClassesLength; ++index) 
    {
        if (hybridClasses[index] == className)
        {
            std::cout << "Necessary Stats: " << '\n';
            for (std::size_t index2{ 0 }; index2 < hybridStatsLength; ++index2)
                std::cout << hybridStats[index2] << " ";
        }
        else
        {
            std::cout << "";
        }
            
    }
        
    
    return 0;
};

int getGear()
{
    std::cout << "Enter Chestpiece here (if crafted, enter 'Crafted'): ";

    std::cin >> chestpiece;

    std::cout << "Enter Arms here (if crafted, enter 'Crafted'): ";

    std::cin >> arms;

    std::cout << "Enter Legs here (if crafted, enter 'Crafted'): ";

    std::cin >> legs;

    std::cout << "Enter Helm here (if crafted, enter 'Crafted'): ";

    std::cin >> helm;

    std::cout << "Enter Hands here (if crafted, enter 'Crafted'): ";

    std::cin >> hands;

    std::cout << "Enter Boots here (if crafted, enter 'Crafted'): ";

    std::cin >> boots;

    std::cout << "Gear: " << '\n' << chestpiece << '\n' << arms << '\n' << legs << '\n' << helm << '\n' << hands << '\n' << boots << '\n';

    return 0;
};

int main()
{
    // Template building program that uses https://eden-daoc.net to look up the items that you input and build your SC

    // getNecessaryStats();

    getGear();

    return 0;
}