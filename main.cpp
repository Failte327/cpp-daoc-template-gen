#include <iostream>
#include <vector>
#include <map>
#include <tabulate/table.hpp>
#include <math.h> 
#include <stdio.h> 

std::map<int, std::string> gemToStatsMap { };
std::map<int, std::string> gemToResistsMap { };
std::map<int, std::string> gemToHitsMap { };
std::map<int, std::string> gemToPowerMap { };
std::map<int, std::string> gemToSkillMap { };
std::map<std::string, int> statRankingsMap { };
std::map<std::string, std::string> statsMap { };
std::map<std::string, std::string> resistsMap { };
std::map<std::string, int> currentResistsMap { };
std::map<std::string, std::string> bonusMap { };
std::map<std::string, std::vector<std::string>> scPiecesGems { };

int bonusCap = 104;
double imbueCap = 37.5;
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
std::vector<std::string> neededStats{ };

std::string templateName{ };
std::vector allStats{"str", "con", "dex", "qui", "acu"};
std::vector resists{"crush", "slash", "thrust", "heat", "cold", "matter", "energy", "body", "spirit"};

int getCurrentResists()
{
    for (auto const entry : resists)
    {
        int resist {};
        std::cout << "Enter current " << entry << " resist";
        std::cin >> resist;
        currentResistsMap[entry] = resist;
    }

    tabulate::Table resistsTable{ };
    int tableRows = 1;

    resistsTable.add_row({"Resist", "Value"});
    resistsTable.row(0).format()
      .font_color(tabulate::Color::white)
      .font_align(tabulate::FontAlign::center)
      .font_style({tabulate::FontStyle::bold});

    for(auto const [key, val] : currentResistsMap)
    {
        resistsTable.add_row({key, std::to_string(val)});
        tableRows++;
    }

    for(int i = 1; i < tableRows; i++)
    {
        resistsTable.row(i).format()
            .font_color(tabulate::Color::green)
            .font_align(tabulate::FontAlign::center)
            .font_style({tabulate::FontStyle::bold});
    }

    std::cout << resistsTable;

    return 0;
}

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

    statsMap["str"] = "fiery essence";
    statsMap["dex"] = "vapor essence";
    statsMap["qui"] = "airy essence";
    statsMap["con"] = "earthen essence";
    statsMap["int"] = "dusty essence";
    statsMap["pie"] = "watery essence";
    statsMap["emp"] = "heated essence";
    statsMap["cha"] = "icy essence";

    resistsMap["body"] = "dusty shielding";
    resistsMap["cold"] = "icy shielding";
    resistsMap["heat"] = "heated shielding";
    resistsMap["energy"] = "light shielding";
    resistsMap["matter"] = "earthen shielding";
    resistsMap["spirit"] = "vapor shielding";
    resistsMap["thrust"] = "airy shielding";
    resistsMap["crush"] = "fiery shielding";
    resistsMap["slash"] = "watery shielding";

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

    bonusMap["hits"] = "blood essence";
    bonusMap["power"] = "mystic essence";

    gemToSkillMap[1] = "raw";
    gemToSkillMap[2] = "uncut";
    gemToSkillMap[3] = "rough";
    gemToSkillMap[4] = "flawed";
    gemToSkillMap[5] = "imperfect";
    gemToSkillMap[6] = "polished";
    gemToSkillMap[7] = "faceted";
    gemToSkillMap[8] = "precious";

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
        neededStats.push_back("Strength");
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
        neededStats.push_back("Constitution");
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
        neededStats.push_back("Dexterity");
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
        neededStats.push_back("Quickness");
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
        neededStats.push_back("Acuity");
        needAcu = true;
    }
    else
    {
        needAcu = false;
    }

    std::cout << '\n';

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
    std::getline(std::cin, templateName);
    std::cout << "Creating " << templateName << " template" << '\n';
    
    return 0;
};

int createTemplateTable()
{

    tabulate::Table statsTable{ };

    int tableRows = 1;

    statsTable.add_row({"Stat", "Value"});
    statsTable.row(0).format()
      .font_color(tabulate::Color::white)
      .font_align(tabulate::FontAlign::center)
      .font_style({tabulate::FontStyle::bold});

    if (needStr)
    {
        tableRows++;
        statsTable.add_row({"Strength", std::to_string(currentStr)});
    }
        
    if (needCon)
    {
        tableRows++;
        statsTable.add_row({"Constitution", std::to_string(currentCon)});
    }
        
    if (needDex)
    {
        tableRows++;
        statsTable.add_row({"Dexterity", std::to_string(currentDex)});
    }

    if (needQui)
    {
        tableRows++;
        statsTable.add_row({"Quickness", std::to_string(currentQui)});
    }
        
    if (needAcu)
    {
        tableRows++;
        statsTable.add_row({"Acuity", std::to_string(currentAcu)});
    }
        
    for(int i = 1; i < tableRows; i++)
    {
        statsTable.row(i).format()
        .font_color(tabulate::Color::green)
        .font_align(tabulate::FontAlign::center)
        .font_style({tabulate::FontStyle::bold});
    }

    std::cout << statsTable << '\n';

    return 0;
}

double calcImbueCostStat(int bonusValue)
{

    double imbueCost = (bonusValue - 1) * 2 / 3 + 1;

    return imbueCost;
}

double calcImbueCostPower(int bonusValue)
{

    double imbueCost = (bonusValue * 2) - 2;

    return imbueCost;
}

double calcImbueCostHealth(int bonusValue)
{

    double imbueCost = bonusValue / 4;

    return imbueCost;
}

double calcImbueCostResist(int bonusValue)
{
    double imbueCost = (bonusValue * 2) - 2;

    return imbueCost;
}

double calcImbueCostSkill(int bonusValue)
{
    double imbueCost = (bonusValue - 1) * 5;

    return imbueCost;
}

int scCalculator()
{

    for(int i = 0; i < SCPieces; i++)
    {
        double totalImbueCost = 0.0;
        std::vector<std::string> gems{ };
        for(int n = 0; n < neededStats.size(); n++)
        {
            if (neededStats[n] == "Strength")
            {
                std::cout << "Need " << bonusCap - currentStr << " strength from " << SCPieces << " sc pieces" << '\n';
                for (auto const [key, val] : gemToStatsMap)
                {
                    double gemCost = calcImbueCostStat(key);
                    if (((bonusCap - (currentStr + key)) == 0) && (imbueCap >= (totalImbueCost + gemCost)))
                    {
                        gems.push_back(val + " fiery essence");
                        currentStr = currentStr + key;
                        totalImbueCost = totalImbueCost + gemCost;
                        break;
                    }
                    if (((bonusCap - (currentStr + key)) > 9) && (key >= 16) && (imbueCap >= (totalImbueCost + gemCost)))
                    {
                        gems.push_back(val + " fiery essence");
                        currentStr = currentStr + key;
                        totalImbueCost = totalImbueCost + gemCost;
                        break;
                    }
                }
            }
            if (neededStats[n] == "Dexterity")
            {
                std::cout << "Need " << bonusCap - currentDex << " dexterity from " << SCPieces << " sc pieces" << '\n';
                for (auto const [key, val] : gemToStatsMap)
                {
                    double gemCost = calcImbueCostStat(key);
                    if (((bonusCap - (currentDex + key)) == 0) && (imbueCap >= (totalImbueCost + gemCost)))
                    {
                        gems.push_back(val + " vapor essence");
                        currentDex = currentDex + key;
                        totalImbueCost = totalImbueCost + gemCost;
                        break;
                    }
                    if (((bonusCap - (currentDex + key)) > 9) && (key >= 16) && (imbueCap >= (totalImbueCost + gemCost)))
                    {
                        gems.push_back(val + " vapor essence");
                        currentDex = currentDex + key;
                        totalImbueCost = totalImbueCost + gemCost;
                        break;
                    }
                }
            }
            if (neededStats[n] == "Quickness")
            {
                std::cout << "Need " << bonusCap - currentQui << " quickness from " << SCPieces << " sc pieces" << '\n';
                for (auto const [key, val] : gemToStatsMap)
                {
                    double gemCost = calcImbueCostStat(key);
                    if (((bonusCap - (currentQui + key)) == 0) && (imbueCap >= (totalImbueCost + gemCost)))
                    {
                        gems.push_back(val + " airy essence");
                        currentQui = currentQui + key;
                        totalImbueCost = totalImbueCost + gemCost;
                        break;
                    }
                    if (((bonusCap - (currentQui + key)) > 9) && (key >= 16) && (imbueCap >= (totalImbueCost + gemCost)))
                    {
                        gems.push_back(val + " airy essence");
                        currentQui = currentQui + key;
                        totalImbueCost = totalImbueCost + gemCost;
                        break;
                    }
                }
            }
            if (neededStats[n] == "Constitution")
            {
                std::cout << "Need " << bonusCap - currentCon << " constitution from " << SCPieces << " sc pieces" << '\n';
                for (auto const [key, val] : gemToStatsMap)
                {
                    double gemCost = calcImbueCostStat(key);
                    if (((bonusCap - (currentCon + key)) == 0) && (imbueCap >= (totalImbueCost + gemCost)))
                    {
                        gems.push_back(val + " earthen essence");
                        currentCon = currentCon + key;
                        totalImbueCost = totalImbueCost + gemCost;
                        break;
                    }
                    if (((bonusCap - (currentCon + key)) > 9) && (key >= 16))
                    {
                        gems.push_back(val + " earthen essence");
                        currentCon = currentCon + key;
                        totalImbueCost = totalImbueCost + gemCost;
                        break;
                    }
                }
            }
            if (neededStats[n] == "Acuity")
            {
                std::cout << "Need " << bonusCap - currentAcu << " acuity from " << SCPieces << " sc pieces" << '\n';
                for (auto const [key, val] : gemToStatsMap)
                {
                    double gemCost = calcImbueCostStat(key);
                    if (((bonusCap - (currentAcu + key)) == 0) && (imbueCap >= (totalImbueCost + gemCost)))
                    {
                        gems.push_back(val + " dusty essence");
                        currentAcu = currentAcu + key;
                        totalImbueCost = totalImbueCost + gemCost;
                        break;
                    }
                    if (((bonusCap - (currentAcu + key)) > 9) && (key >= 16) && (imbueCap >= (totalImbueCost + gemCost)))
                    {
                        gems.push_back(val + " dusty essence");
                        currentAcu = currentAcu + key;
                        totalImbueCost = totalImbueCost + gemCost;
                        break;
                    }
                }
            }
        }
        
        createTemplateTable();
        std::cout << "SC Piece #" << i + 1 << '\n';
        for(auto const entry : gems)
        {
            std::cout << entry << '\n';
        }
        std::cout << "End Imbue Cost = " << totalImbueCost << '\n';
    }

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
    getCurrentResists();
    createTemplateTable();
    scCalculator();

    return 0;
}