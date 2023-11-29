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

    std::cout << "Would you like to cap Strength? (y/n)";

    std::cin >> strAnswer;

    if (strAnswer == "y")
    {
        needStr = true;
    }
    else
    {
        needStr = false;
    }
        

    std::cout << '\n';

    std::cout << "Would you like to cap Constitution? (y/n)";

    std::cin >> conAnswer;

    if (conAnswer == "y")
    {
        needCon = true;
    }
    else
    {
        needCon = false;
    }

    std::cout << '\n';
    
    std::cout << "Would you like to cap Dexterity? (y/n)";

    std::cin >> dexAnswer;

    if (dexAnswer == "y")
    {
        needDex = true;
    }
    else
    {
        needDex = false;
    }
    std::cout << '\n';
    
    std::cout << "Would you like to cap Quickness? (y/n)";

    std::cin >> quiAnswer;

    if (quiAnswer == "y")
    {
        needQui = true;
    }
    else
    {
        needQui = false;
    }

    std::cout << '\n';
    
    std::cout << "Would you like to cap Acuity? (y/n)";

    std::cin >> acuAnswer;

    if (acuAnswer == "y")
    {
        needAcu = true;
    }
    else
    {
        needAcu = false;
    }

    std::cout << '\n';
    
    std::cout << "Need Strength = " << needStr << '\n';

    std::cout << "Need Constitution = " << needCon << '\n';

    std::cout << "Need Dexterity = " << needDex << '\n';

    std::cout << "Need Quickness = " << needQui << '\n';

    std::cout << "Need Acuity = " << needAcu << '\n';

    return 0;
}

int getCurrentStats() 
{

    if (needStr)
    {
        std::cout << "Enter current Strength bonus: ";

        std::cin >> currentStr;

        std::cout << '\n';
    }
        
    if (needCon)
    {
        std::cout << "Enter current Constitution bonus: ";

        std::cin >> currentCon;

        std::cout << '\n';
    }

    if (needDex)
    {
        std::cout << "Enter current Dexterity bonus: ";

        std::cin >> currentDex;

        std::cout << '\n';
    }

    if (needQui)
    {
        std::cout << "Enter current Quickness bonus: ";

        std::cin >> currentQui;

        std::cout << '\n';
    }

    if (needAcu)
    {
        std::cout << "Enter current Acuity bonus: ";

        std::cin >> currentAcu;

        std::cout << '\n';
    }

    return 0;
}

int getTemplateTitle() {

    std::cout << "What would you like to name this template? " << '\n';

    std::cin >> templateName;

    std::cout << "Creating " << templateName << " template" << '\n';
    
    return 0;
};

int logCurrStats() 
{
    if (needStr)
        std::cout << "Current Strength = " << currentStr << '\n';

    if (needCon)
        std::cout << "Current Constitution = " << currentCon << '\n';

    if (needDex)
        std::cout << "Current Dexterity = " << currentDex << '\n';

    if (needQui)
        std::cout << "Current Quickness = " << currentQui << '\n';

    if (needAcu)
        std::cout << "Current Acuity = " << currentAcu << '\n';

    return 0;
}

int main()
{
    // Template building program that uses your current stats + your number of gear pieces to calculate what gems you need

    displayIntroText();

    getTemplateTitle();

    getNumberOfGearPieces();

    getNeededStats();

    getCurrentStats();

    logCurrStats();

    return 0;
}