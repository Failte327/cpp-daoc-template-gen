#include <iostream>
#include <vector>
#include <map>

std::map<int, std::string> gemToStatsMap { };
std::map<int, std::string> gemToResistsMap { };
std::map<int, std::string> gemToHitsMap { };
std::map<int, std::string> gemToPowerMap { };
std::map<int, std::string> gemToSkillMap { };
std::map<std::string, int> statRankingsMap { };
std::map<std::string, std::string> statsMap { };
std::map<std::string, std::string> resistsMap { };
std::map<std::string, std::string> bonusMap { };

int bonusCap = 104;
int SCPieces{ };
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

int createSCMaps()
{
    gemToStatsMap[1] = "raw";
    gemToStatsMap[4] = "uncut";
    gemToStatsMap[7] = "rough";
    gemToStatsMap[10] = "flawed";
    gemToStatsMap[13] = "imperfect";
    gemToStatsMap[16] = "polished";
    gemToStatsMap[19] = "faceted";
    gemToStatsMap[22] = "precious";
    gemToStatsMap[25] = "flawless";
    gemToStatsMap[28] = "perfect";

    for (auto const [key, val] : gemToStatsMap)
    {
        std::cout << key << ": " << val << '\n';
    }

    statsMap["str"] = "fiery essence";
    statsMap["dex"] = "vapor essence";
    statsMap["qui"] = "airy essence";
    statsMap["con"] = "earthen essence";
    statsMap["int"] =  "dusty essence";
    statsMap["pie"] = "watery essence";
    statsMap["emp"] = "heated essence";
    statsMap["cha"] = "icy essence";

    for (auto const [key, val] : statsMap)
    {
        std::cout << key << ": " << val << '\n';
    }

    resistsMap["body"] = "dusty shielding";
    resistsMap["cold"] = "icyshielding";
    resistsMap["heat"] = "heated shielding";
    resistsMap["energy"] = "light shielding";
    resistsMap["matter"] = "earthen shielding";
    resistsMap["spirit"] = "vapor shielding";
    resistsMap["thrust"] = "airy shielding";
    resistsMap["crush"] = "fiery shielding";
    resistsMap["slash"] = "watery shielding";

    for(auto const [key, val] : resistsMap)
    {
        std::cout << key << ": " << val << '\n';
    }

    gemToResistsMap[1] = "raw";
    gemToResistsMap[2] = "uncut";
    gemToResistsMap[3] = "rough";
    gemToResistsMap[5] = "flawed";
    gemToResistsMap[7] = "imperfect";
    gemToResistsMap[9] = "polished";
    gemToResistsMap[11] = "faceted";
    gemToResistsMap[13] = "precious";
    gemToResistsMap[15] = "flawless";
    gemToResistsMap[17] = "perfect";

    for(auto const [key, val] : gemToResistsMap)
    {
        std::cout << key << ": " << val << '\n';
    }

    gemToHitsMap[4] = "raw";
    gemToHitsMap[12] = "uncut";
    gemToHitsMap[20] = "rough";
    gemToHitsMap[28] = "flawed";
    gemToHitsMap[36] = "imperfect";
    gemToHitsMap[44] = "polished";
    gemToHitsMap[52] = "faceted";
    gemToHitsMap[60] = "precious";
    gemToHitsMap[68] = "flawless";
    gemToHitsMap[76] = "perfect";

    for(auto const [key, val] : gemToHitsMap)
    {
        std::cout << key << ": " << val << '\n';
    }

    gemToPowerMap[1] = "raw";
    gemToPowerMap[2] = "uncut";
    gemToPowerMap[3] = "rough";
    gemToPowerMap[5] = "flawed";
    gemToPowerMap[7] = "imperfect";
    gemToPowerMap[9] = "polished";
    gemToPowerMap[11] = "faceted";
    gemToPowerMap[13] = "precious";
    gemToPowerMap[15] = "flawless";
    gemToPowerMap[17] = "perfect";

    for(auto const [key, val] : gemToPowerMap)
    {
        std::cout << key << ": " << val << '\n';
    }

    bonusMap["hits"] = "blood essence";
    bonusMap["power"] = "mystic essence";

    for(auto const [key, val] : bonusMap)
    {
        std::cout << key << ": " << val << '\n';
    }

    gemToSkillMap[1] = "raw";
    gemToSkillMap[2] = "uncut";
    gemToSkillMap[3] = "rough";
    gemToSkillMap[4] = "flawed";
    gemToSkillMap[5] = "imperfect";
    gemToSkillMap[6] = "polished";
    gemToSkillMap[7] = "faceted";
    gemToSkillMap[8] = "precious";

    for(auto const [key, val] : gemToSkillMap)
    {
        std::cout << key << ": " << val << '\n';
    }

    return 0;
}

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

int getStatRankings()
{

    int strRank{ };
    int conRank{ };
    int dexRank{ };
    int quiRank{ };
    int acuRank{ };

    if(needStr)
    {
        std::cout << "Rank strength in regards to importance (1 being the most important)";
        std::cin >> strRank;
        statRankingsMap["str"] = strRank;
        std::cout << '\n';
    }

    if(needCon)
    {
        std::cout << "Rank constitution in regards to importance (1 being the most important)";
        std::cin >> conRank;
        statRankingsMap["con"] = conRank;
        std::cout << '\n';
    }

    if(needDex)
    {
        std::cout << "Rank dexterity in regards to importance (1 being the most important)";
        std::cin >> dexRank;
        statRankingsMap["dex"] = dexRank;
        std::cout << '\n';
    }

    if(needQui)
    {
        std::cout << "Rank quickness in regards to importance (1 being the most important)";
        std::cin >> quiRank;
        statRankingsMap["qui"] = quiRank;
        std::cout << '\n';
    }

    if(needAcu)
    {
        std::cout << "Rank acuity in regards to importance (1 being the most important)";
        std::cin >> acuRank;
        statRankingsMap["acu"] = acuRank;
        std::cout << '\n';
    }

    for(auto const& [key, val] : statRankingsMap)
    {
        std::cout << key << ": " << val << '\n';
    }

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
    createSCMaps();
    displayIntroText();
    getTemplateTitle();
    getNumberOfGearPieces();
    getNeededStats();
    getCurrentStats();
    logCurrStats();
    getStatRankings();

    return 0;
}