#include <iostream>
#include <vector>
#include <cpr/cpr.h>

int bonusCap = 104;
std::vector tankStats{"str", "con", "dex", "qui"};
std::vector casterStats{"con", "dex", "acu"};
std::vector hybridStats{"str", "con", "dex", "qui", "acu"};
std::vector resists{"crush", "slash", "thrust", "heat", "cold", "matter", "energy", "body", "spirit"};
std::vector casterClasses{"Animist", "Bonedancer","Runemaster", "Cabalist", "Cleric", "Bainshee", "Healer", "Druid", "Bard","Shaman", "Spiritmaster","Enchanter", "Mentalist", "Eldritch", "Necromancer", "Sorcerer", "Theurgist", "Wizard"};
std::vector tankClasses{"Infiltrator", "Mercenary", "Armsman", "Savage", "Berserker", "Blademaster", "Shadowblade", "Hero", "Nightshade","Warrior", "Paladin"};
std::vector hybridClasses{"Friar",  "Heretic", "Hunter",  "Champion", "Minstrel", "Skald",  "Thane", "Reaver","Valkyrie","Ranger", "Valewalker", "Warden", "Scout"};
int SCPieces{ };

int displayIntroText()
{

    std::cout << "WELCOME TO INTERSTELLAR'S SPELLCRAFT CALCULATOR!" << '\n';
    std::cout << "Inspired by Loki, this simple program will calculate optimal gem combinations based on only a few simple inputs from the user. Enjoy!" << '\n';

    return 0;
}

int getNumberOfGearPieces()
{

    std::cout << "How many gear pieces will be spellcrafted? ";

    std::cin >> SCPieces;

    std::cout << "Spellcrafting " << SCPieces << " pieces";

    std::cout << '\n';

    return 0;
};

int getNecessaryStats() {

    std::cout << "What class would you like to generate a template for? ";

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

    std::cout << '\n';
    
    return 0;
};

int main()
{
    // Template building program that uses your current stats + your number of gear pieces to calculate what gems you need

    displayIntroText();

    getNecessaryStats();

    getNumberOfGearPieces();

    return 0;
}