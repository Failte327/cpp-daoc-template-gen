#include <iostream>
#include <vector>

int bonusCap = 104;
int currentStr { };
int currentCon { };
int currentDex { };
int currentQui { };
int currentAcu { };
bool needStr { };
bool needCon { };
bool needDex { };
bool needQui { };
bool needAcu { };
std::string templateName{ };
std::vector allStats{"str", "con", "dex", "qui", "acu"};
std::vector resists{"crush", "slash", "thrust", "heat", "cold", "matter", "energy", "body", "spirit"};

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

int getNeededStats() 
{

    std::string strAnswer { };

    std::string conAnswer { };

    std::string dexAnswer { };

    std::string quiAnswer { };

    std::string acuAnswer { };

    std::cout << "Would you like to cap Strength? (y/n)" << '\n';

    std::cin >> strAnswer;

    if (strAnswer == "y" || "Y" || "yes" || "Yes")
        needStr = true;
    else
        needStr = false;

    std::cout << "Would you like to cap Constitution? (y/n)" << '\n';

    std::cin >> conAnswer;

    if (conAnswer == "y" || "Y" || "yes" || "Yes")
        needCon = true;
    else
        needCon = false;

    std::cout << "Would you like to cap Dexterity? (y/n)" << '\n';

    std::cin >> dexAnswer;

    if (dexAnswer == "y" || "Y" || "yes" || "Yes")
        needDex = true;
    else
        needDex = false;

    std::cout << "Would you like to cap Quickness? (y/n)" << '\n';

    std::cin >> quiAnswer;

    if (quiAnswer == "y" || "Y" || "yes" || "Yes")
        needQui = true;
    else
        needQui = false;

    std::cout << "Would you like to cap Acuity? (y/n)" << '\n';

    std::cin >> acuAnswer;

    if (acuAnswer == "y" || "Y" || "yes" || "Yes")
        needAcu = true;
    else
        needAcu = false;

    return 0;
}

int getCurrentStats() 
{

    std::cout << "Enter current Strength bonus: " << '\n';

    std::cin >> currentStr;

    std::cout << '\n';

    std::cout << "Enter current Constitution bonus: " << '\n';

    std::cin >> currentCon;

    std::cout << '\n';

    std::cout << "Enter current Quickness bonus: ";

    return 0;
}

int getTemplateTitle() {

    std::cout << "What would you like to name this template? " << '\n';

    std::cin >> templateName;

    std::cout << "Creating " << templateName << " template" << '\n';
    
    return 0;
};

int main()
{
    // Template building program that uses your current stats + your number of gear pieces to calculate what gems you need

    displayIntroText();

    getTemplateTitle();

    getNumberOfGearPieces();

    return 0;
}