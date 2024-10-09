// TO BUILD, RUN: g++ -I tabulate/include/ -o main main.cpp

#include <iostream>
#include <vector>
#include <map>
#include <tabulate/table.hpp>

std::map<int, std::string> gemToStatsMap { };
std::map<int, std::string> gemToResistsMap { };
std::map<int, std::string> gemToHitsMap { };
std::map<int, std::string> gemToPowerMap { };
std::map<int, std::string> gemToSkillMap { };
std::map<std::string, int> statRankingsMap { };
std::map<std::string, int> resistRankingsMap { };
std::map<std::string, std::string> statsMap { };
std::map<std::string, int> statsToCurrentDeficitMap { };
std::map<std::string, int> resistsToCurrentDeficitMap { };
std::map<std::string, std::string> statsToCurrentMap { };
std::map<std::string, std::string> resistsMap { };
std::map<std::string, int> currentResistsMap { };
std::map<std::string, std::string> bonusMap { };
std::map<std::string, std::vector<std::string>> scPiecesGems { };

int bonusCap = 104;
double imbueCap = 37.5;
int resistCap = 26;
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
std::vector resists{"crush", "slash", "thrust", "heat", "cold", "matter", "energy", "body", "spirit"};
std::vector tanks{"warrior", "berserker", "savage", "shadowblade", "blademaster", "hero", "nightshade", "armsman", "infiltrator", "mercenary"};
std::vector hybrids{"friar", "heretic", "minstrel", "paladin", "reaver", "champion", "warden", "valewalker", "skald", "thane", "valkyrie"};
std::vector casters{"cabalist", "necromancer", "sorcerer", "theurgist", "wizard", "animist", "bainshee", "eldritch", "enchanter", "mentalist", "bonedancer", "runemaster", "spiritmaster"};
std::vector supports{"cleric", "healer", "shaman", "bard", "druid"};
std::vector archers{"hunter", "scout", "ranger"};

struct greater
{
    template<class T>
    bool operator()(T const &a, T const &b) const { return a > b; }
};

int createTemplateTable()
{

    tabulate::Table statsTable{ };
    tabulate::Table resistsTable{ };

    int tableRows = 1;

    statsTable.add_row({"Stat", "Value"});
    statsTable.row(0).format()
      .font_color(tabulate::Color::white)
      .font_align(tabulate::FontAlign::center)
      .font_style({tabulate::FontStyle::bold});
    resistsTable.add_row({"Resist", "Value"});
    resistsTable.row(0).format()
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

    for(auto const [resist, value] : currentResistsMap)
    {
        int row = 1;
        resistsTable.add_row({resist, std::to_string(value)});
    }

    std::cout << statsTable << '\n';
    std::cout << resistsTable << '\n';

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

    statsMap["Strength"] = "fiery essence";
    statsMap["Dexterity"] = "vapor essence";
    statsMap["Quickness"] = "airy essence";
    statsMap["Constitution"] = "earthen essence";
    // placeholder for acuity being 4 different essences, int is 'dusty essence'
    statsMap["Acuity"] = "acuity essence";
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

    std::cout << "WELCOME TO REKLEWT'S SPELLCRAFT CALCULATOR!" << '\n';

    return 0;
}

int getTemplateTitle() 
{
    std::cout << "What would you like to name this template? " << '\n';
    std::getline(std::cin, templateName);
    std::cout << "Creating " << templateName << " template" << '\n';
    
    return 0;
};

int getClass() 
{

    std::string classAnswer { };
    std::cout << "What class is this template for?\n";
    std::cin >> classAnswer;

    for (int i = 0; i < tanks.size(); i++)
    {
        if (tanks[i] == classAnswer) 
        {
            needStr = true;
            needQui = true;
            needCon = true;
            needDex = true;
            needAcu = false;
        };
    };
    for (int i = 0; i < supports.size(); i++)
    {
        if (supports[i] == classAnswer) 
        {
            needCon = true;
            needDex = true;
            needAcu = true;
            needStr = false;
            needQui = false;
        };
    };
    for (int i = 0; i < casters.size(); i++)
    {
        if (casters[i] == classAnswer) 
        {
            needCon = true;
            needDex = true;
            needAcu = true;
            needStr = false;
            needQui = false;
        }
    };
    for (int i = 0; i < hybrids.size(); i++)
    {
        if (hybrids[i] == classAnswer)
        {
            needStr = true;
            needQui = true;
            needCon = true;
            needDex = true;
            needAcu = true;
        };
    };
    for (int i = 0; i < archers.size(); i++)
    {
        if (archers[i] == classAnswer)
        {
            needStr = true;
            needQui = true;
            needCon = true;
            needDex = true;
            needAcu = false;
        };
    };

    std::cout << "Needed Stats:\n";
    if (needStr)
    {
        std::cout << "Strength\n";
    };
    if (needAcu)
    {
        std::cout << "Acuity\n";
    };
    if (needDex)
    {
        std::cout << "Dexterity\n";
    };
    if (needQui)
    {
        std::cout << "Quickness\n";
    };
    if (needCon)
    {
        std::cout << "Constitution\n";
    };

    return 0;
};

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

int scCalcRecursionStat(int bonus)
{

    int cost = calcImbueCostStat(bonus);

    return cost;
}

int scCalcRecursionResist(int bonus)
{

    int cost = calcImbueCostResist(bonus);

    return cost;
}

int scCalculator()
{

    for(int i = 0; i < SCPieces; i++)
    {
        double totalImbueCost = 0.0;
        std::vector<std::string> gems{ };
        // Stats
        for(auto const [key, val] : statRankingsMap)
        {
            if ((gems.size() < 3) && (totalImbueCost < imbueCap))
            {
                if(val == 1)
                {
                    for (auto const [key2, val2]: statsToCurrentDeficitMap)
                    {
                        if ((key == key2) && (val2 > 5))
                        {
                            std::string gemPrefix { };
                            std::string gemStat { };
                            std::string gemName { };
                            int bonusValue { };
                            int deficit = val2;
                            int cost { };
                            int bonus { };
                            // If cap can be reached for any stats with exact values starting at 10, consume a gem
                            if (deficit == 10)
                            {
                                gemPrefix = "flawed";
                            }
                            if (deficit == 13)
                            {
                                gemPrefix = "imperfect";
                            }
                            if (deficit == 16)
                            {
                                gemPrefix = "polished";
                            }
                            if (deficit == 19)
                            {
                                gemPrefix = "faceted";
                            }
                            if (deficit == 22)
                            {
                                gemPrefix = "precious";
                            }
                            if (deficit == 25)
                            {
                                gemPrefix = "flawless";
                            }
                            if (deficit == 28)
                            {
                                gemPrefix = "perfect";
                            }
                            else 
                            {
                                // If the deficit is large, pump stats in while imbue points are available, otherwise, increment downward
                                if (deficit >= 50)
                                {
                                    gemPrefix = "precious";
                                }
                                else if (deficit >= 35)
                                {
                                    gemPrefix = "polished";
                                }
                                else if (deficit >= 15)
                                {
                                    gemPrefix = "imperfect";
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (auto const [key3, val3] : statsMap)
                            {
                                if (key == key3)
                                {
                                    gemStat = val3;
                                }
                            }

                            for (auto const [key4, val4]: gemToStatsMap)
                            {
                                if (gemPrefix == val4)
                                {
                                    bonus = key4;
                                    cost = calcImbueCostStat(bonus);
                                }
                            }

                            gemName = gemPrefix + " " + gemStat;
                            if (key == "Strength")
                            {
                                currentStr = currentStr + bonus;
                            }
                            if (key == "Dexterity")
                            {
                                currentDex = currentDex + bonus;
                            }
                            if (key == "Constitution")
                            {
                                currentCon = currentCon + bonus;
                            }
                            if (key == "Quickness")
                            {
                                currentQui = currentQui + bonus;
                            }
                            if (key == "Acuity")
                            {
                                currentAcu = currentAcu + bonus;
                            }

                            totalImbueCost = totalImbueCost + cost;

                            if (totalImbueCost <= imbueCap)
                            {
                                gems.push_back(gemName);
                            }
                            else
                            {
                                bonus = bonus - 6;
                                cost = scCalcRecursionStat(bonus);
                                totalImbueCost = totalImbueCost + cost;
                                if (totalImbueCost <= imbueCap)
                                {
                                    for (auto const [key4, val4]: gemToStatsMap)
                                    {
                                        if (bonus == key4)
                                        {
                                            gemPrefix = val4;
                                        }
                                    }
                                    for (auto const [key3, val3] : statsMap)
                                    {
                                        if (key == key3)
                                        {
                                            gemStat = val3;
                                        }
                                    }
                                    gemName = gemPrefix + " " + gemStat;
                                    if (key == "Strength")
                                    {
                                        currentStr = currentStr + bonus;
                                    }
                                    if (key == "Dexterity")
                                    {
                                        currentDex = currentDex + bonus;
                                    }
                                    if (key == "Constitution")
                                    {
                                        currentCon = currentCon + bonus;
                                    }
                                    if (key == "Quickness")
                                    {
                                        currentQui = currentQui + bonus;
                                    }
                                    if (key == "Acuity")
                                    {
                                        currentAcu = currentAcu + bonus;
                                    }
                                    gems.push_back(gemName);
                                }
                                else
                                {
                                    totalImbueCost = totalImbueCost - bonus;
                                }
                            }
                            
                        }
                    }
                }
                else if(val == 2)
                {
                    for (auto const [key2, val2]: statsToCurrentDeficitMap)
                    {
                        if ((key == key2) && (val2 > 5))
                        {
                            std::string gemPrefix { };
                            std::string gemStat { };
                            std::string gemName { };
                            int bonusValue { };
                            int deficit = val2;
                            // If cap can be reached for any stats with exact values starting at 10, consume a gem
                            if (deficit == 10)
                            {
                                gemPrefix = "flawed";
                            }
                            if (deficit == 13)
                            {
                                gemPrefix = "imperfect";
                            }
                            if (deficit == 16)
                            {
                                gemPrefix = "polished";
                            }
                            if (deficit == 19)
                            {
                                gemPrefix = "faceted";
                            }
                            if (deficit == 22)
                            {
                                gemPrefix = "precious";
                            }
                            if (deficit == 25)
                            {
                                gemPrefix = "flawless";
                            }
                            if (deficit == 28)
                            {
                                gemPrefix = "perfect";
                            }
                            else 
                            {
                                // If the deficit is large, pump stats in while imbue points are available, otherwise, increment downward
                                if (deficit >= 50)
                                {
                                    gemPrefix = "precious";
                                }
                                else if (deficit >= 35)
                                {
                                    gemPrefix = "polished";
                                }
                                else if (deficit >= 15)
                                {
                                    gemPrefix = "imperfect";
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (auto const [key3, val3] : statsMap)
                            {
                                if (key == key3)
                                {
                                    gemStat = val3;
                                }
                            }
                            int cost { };
                            int bonus { };
                            
                            for (auto const [key4, val4]: gemToStatsMap)
                            {
                                if (gemPrefix == val4)
                                {
                                    bonus = key4;
                                    cost = calcImbueCostStat(bonus);
                                }
                            }
                            
                            gemName = gemPrefix + " " + gemStat;
                            if (key == "Strength")
                            {
                                currentStr = currentStr + bonus;
                            }
                            if (key == "Dexterity")
                            {
                                currentDex = currentDex + bonus;
                            }
                            if (key == "Constitution")
                            {
                                currentCon = currentCon + bonus;
                            }
                            if (key == "Quickness")
                            {
                                currentQui = currentQui + bonus;
                            }
                            if (key == "Acuity")
                            {
                                currentAcu = currentAcu + bonus;
                            }
                            totalImbueCost = totalImbueCost + cost;
                            
                            if (totalImbueCost <= imbueCap)
                            {
                                gems.push_back(gemName);
                            }
                            else
                            {
                                bonus = bonus - 6;
                                cost = scCalcRecursionStat(bonus);
                                totalImbueCost = totalImbueCost + cost;
                                if (totalImbueCost <= imbueCap)
                                {
                                    for (auto const [key4, val4]: gemToStatsMap)
                                    {
                                        if (bonus == key4)
                                        {
                                            gemPrefix = val4;
                                        }
                                    }
                                    for (auto const [key3, val3] : statsMap)
                                    {
                                        if (key == key3)
                                        {
                                            gemStat = val3;
                                        }
                                    }
                                    gemName = gemPrefix + " " + gemStat;
                                    if (key == "Strength")
                                    {
                                        currentStr = currentStr + bonus;
                                    }
                                    if (key == "Dexterity")
                                    {
                                        currentDex = currentDex + bonus;
                                    }
                                    if (key == "Constitution")
                                    {
                                        currentCon = currentCon + bonus;
                                    }
                                    if (key == "Quickness")
                                    {
                                        currentQui = currentQui + bonus;
                                    }
                                    if (key == "Acuity")
                                    {
                                        currentAcu = currentAcu + bonus;
                                    }
                                    gems.push_back(gemName);
                                }
                                else
                                {
                                    totalImbueCost = totalImbueCost - bonus;
                                }
                            }
                        }
                    }
                }
                else if(val == 3)
                {
                    for (auto const [key2, val2]: statsToCurrentDeficitMap)
                    {
                        if ((key == key2) && (val2 > 5))
                        {
                            std::string gemPrefix { };
                            std::string gemStat { };
                            std::string gemName { };
                            int bonusValue { };
                            int deficit = val2;
                            // If cap can be reached for any stats with exact values starting at 10, consume a gem
                            if (deficit == 10)
                            {
                                gemPrefix = "flawed";
                            }
                            if (deficit == 13)
                            {
                                gemPrefix = "imperfect";
                            }
                            if (deficit == 16)
                            {
                                gemPrefix = "polished";
                            }
                            if (deficit == 19)
                            {
                                gemPrefix = "faceted";
                            }
                            if (deficit == 22)
                            {
                                gemPrefix = "precious";
                            }
                            if (deficit == 25)
                            {
                                gemPrefix = "flawless";
                            }
                            if (deficit == 28)
                            {
                                gemPrefix = "perfect";
                            }
                            else 
                            {
                                // If the deficit is large, pump stats in while imbue points are available, otherwise, increment downward
                                if (deficit >= 50)
                                {
                                    gemPrefix = "precious";
                                }
                                else if (deficit >= 35)
                                {
                                    gemPrefix = "polished";
                                }
                                else if (deficit >= 15)
                                {
                                    gemPrefix = "imperfect";
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (auto const [key3, val3] : statsMap)
                            {
                                if (key == key3)
                                {
                                    gemStat = val3;
                                }
                            }
                            int cost { };
                            int bonus { };
                            
                            for (auto const [key4, val4]: gemToStatsMap)
                            {
                                if (gemPrefix == val4)
                                {
                                    bonus = key4;
                                    cost = calcImbueCostStat(bonus);
                                }
                            }
                            
                            gemName = gemPrefix + " " + gemStat;
                            if (key == "Strength")
                            {
                                currentStr = currentStr + bonus;
                            }
                            if (key == "Dexterity")
                            {
                                currentDex = currentDex + bonus;
                            }
                            if (key == "Constitution")
                            {
                                currentCon = currentCon + bonus;
                            }
                            if (key == "Quickness")
                            {
                                currentQui = currentQui + bonus;
                            }
                            if (key == "Acuity")
                            {
                                currentAcu = currentAcu + bonus;
                            }
                            totalImbueCost = totalImbueCost + cost;
                            
                            if (totalImbueCost <= imbueCap)
                            {
                                gems.push_back(gemName);
                            }
                            else
                            {
                                bonus = bonus - 6;
                                cost = scCalcRecursionStat(bonus);
                                totalImbueCost = totalImbueCost + cost;
                                if (totalImbueCost <= imbueCap)
                                {
                                    for (auto const [key4, val4]: gemToStatsMap)
                                    {
                                        if (bonus == key4)
                                        {
                                            gemPrefix = val4;
                                        }
                                    }
                                    for (auto const [key3, val3] : statsMap)
                                    {
                                        if (key == key3)
                                        {
                                            gemStat = val3;
                                        }
                                    }
                                    gemName = gemPrefix + " " + gemStat;
                                    if (key == "Strength")
                                    {
                                        currentStr = currentStr + bonus;
                                    }
                                    if (key == "Dexterity")
                                    {
                                        currentDex = currentDex + bonus;
                                    }
                                    if (key == "Constitution")
                                    {
                                        currentCon = currentCon + bonus;
                                    }
                                    if (key == "Quickness")
                                    {
                                        currentQui = currentQui + bonus;
                                    }
                                    if (key == "Acuity")
                                    {
                                        currentAcu = currentAcu + bonus;
                                    }
                                    gems.push_back(gemName);
                                }
                                else
                                {
                                    totalImbueCost = totalImbueCost - bonus;
                                }
                            }
                        }
                    }
                }
                else if(val == 4)
                {
                    for (auto const [key2, val2]: statsToCurrentDeficitMap)
                    {
                        if ((key == key2) && (val2 > 5))
                        {
                            std::string gemPrefix { };
                            std::string gemStat { };
                            std::string gemName { };
                            int bonusValue { };
                            int deficit = val2;
                            // If cap can be reached for any stats with exact values starting at 10, consume a gem
                            if (deficit == 10)
                            {
                                gemPrefix = "flawed";
                            }
                            if (deficit == 13)
                            {
                                gemPrefix = "imperfect";
                            }
                            if (deficit == 16)
                            {
                                gemPrefix = "polished";
                            }
                            if (deficit == 19)
                            {
                                gemPrefix = "faceted";
                            }
                            if (deficit == 22)
                            {
                                gemPrefix = "precious";
                            }
                            if (deficit == 25)
                            {
                                gemPrefix = "flawless";
                            }
                            if (deficit == 28)
                            {
                                gemPrefix = "perfect";
                            }
                            else 
                            {
                                // If the deficit is large, pump stats in while imbue points are available, otherwise, increment downward
                                if (deficit >= 50)
                                {
                                    gemPrefix = "precious";
                                }
                                else if (deficit >= 35)
                                {
                                    gemPrefix = "polished";
                                }
                                else if (deficit >= 15)
                                {
                                    gemPrefix = "imperfect";
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (auto const [key3, val3] : statsMap)
                            {
                                if (key == key3)
                                {
                                    gemStat = val3;
                                }
                            }
                            int cost { };
                            int bonus { };
                            
                            for (auto const [key4, val4]: gemToStatsMap)
                            {
                                if (gemPrefix == val4)
                                {
                                    bonus = key4;
                                    cost = calcImbueCostStat(bonus);
                                }
                            }
                            
                            gemName = gemPrefix + " " + gemStat;
                            if (key == "Strength")
                            {
                                currentStr = currentStr + bonus;
                            }
                            if (key == "Dexterity")
                            {
                                currentDex = currentDex + bonus;
                            }
                            if (key == "Constitution")
                            {
                                currentCon = currentCon + bonus;
                            }
                            if (key == "Quickness")
                            {
                                currentQui = currentQui + bonus;
                            }
                            if (key == "Acuity")
                            {
                                currentAcu = currentAcu + bonus;
                            }
                            totalImbueCost = totalImbueCost + cost;
                            
                            if (totalImbueCost <= imbueCap)
                            {
                                gems.push_back(gemName);
                            }
                            else
                            {
                                bonus = bonus - 6;
                                cost = scCalcRecursionStat(bonus);
                                totalImbueCost = totalImbueCost + cost;
                                if (totalImbueCost <= imbueCap)
                                {
                                    for (auto const [key4, val4]: gemToStatsMap)
                                    {
                                        if (bonus == key4)
                                        {
                                            gemPrefix = val4;
                                        }
                                    }
                                    for (auto const [key3, val3] : statsMap)
                                    {
                                        if (key == key3)
                                        {
                                            gemStat = val3;
                                        }
                                    }
                                    gemName = gemPrefix + " " + gemStat;
                                    if (key == "Strength")
                                    {
                                        currentStr = currentStr + bonus;
                                    }
                                    if (key == "Dexterity")
                                    {
                                        currentDex = currentDex + bonus;
                                    }
                                    if (key == "Constitution")
                                    {
                                        currentCon = currentCon + bonus;
                                    }
                                    if (key == "Quickness")
                                    {
                                        currentQui = currentQui + bonus;
                                    }
                                    if (key == "Acuity")
                                    {
                                        currentAcu = currentAcu + bonus;
                                    }
                                    gems.push_back(gemName);
                                }
                                else
                                {
                                    totalImbueCost = totalImbueCost - bonus;
                                }
                            }
                        }
                    }
                }
                else if(val == 5)
                {
                    for (auto const [key2, val2]: statsToCurrentDeficitMap)
                    {
                        if ((key == key2) && (val2 > 5))
                        {
                            std::string gemPrefix { };
                            std::string gemStat { };
                            std::string gemName { };
                            int bonusValue { };
                            int deficit = val2;
                            // If cap can be reached for any stats with exact values starting at 10, consume a gem
                            if (deficit == 10)
                            {
                                gemPrefix = "flawed";
                            }
                            if (deficit == 13)
                            {
                                gemPrefix = "imperfect";
                            }
                            if (deficit == 16)
                            {
                                gemPrefix = "polished";
                            }
                            if (deficit == 19)
                            {
                                gemPrefix = "faceted";
                            }
                            if (deficit == 22)
                            {
                                gemPrefix = "precious";
                            }
                            if (deficit == 25)
                            {
                                gemPrefix = "flawless";
                            }
                            if (deficit == 28)
                            {
                                gemPrefix = "perfect";
                            }
                            else 
                            {
                                // If the deficit is large, pump stats in while imbue points are available, otherwise, increment downward
                                if (deficit >= 50)
                                {
                                    gemPrefix = "precious";
                                }
                                else if (deficit >= 35)
                                {
                                    gemPrefix = "polished";
                                }
                                else if (deficit >= 15)
                                {
                                    gemPrefix = "imperfect";
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (auto const [key3, val3] : statsMap)
                            {
                                if (key == key3)
                                {
                                    gemStat = val3;
                                }
                            }
                            int cost { };
                            int bonus { };
                            
                            for (auto const [key4, val4]: gemToStatsMap)
                            {
                                if (gemPrefix == val4)
                                {
                                    bonus = key4;
                                    cost = calcImbueCostStat(bonus);
                                }
                            }
                            
                            gemName = gemPrefix + " " + gemStat;
                            if (key == "Strength")
                            {
                                currentStr = currentStr + bonus;
                            }
                            if (key == "Dexterity")
                            {
                                currentDex = currentDex + bonus;
                            }
                            if (key == "Constitution")
                            {
                                currentCon = currentCon + bonus;
                            }
                            if (key == "Quickness")
                            {
                                currentQui = currentQui + bonus;
                            }
                            if (key == "Acuity")
                            {
                                currentAcu = currentAcu + bonus;
                            }
                            totalImbueCost = totalImbueCost + cost;
                            
                            if (totalImbueCost <= imbueCap)
                            {
                                gems.push_back(gemName);
                            }
                            else
                            {
                                bonus = bonus - 6;
                                cost = scCalcRecursionStat(bonus);
                                totalImbueCost = totalImbueCost + cost;
                                if (totalImbueCost <= imbueCap)
                                {
                                    for (auto const [key4, val4]: gemToStatsMap)
                                    {
                                        if (bonus == key4)
                                        {
                                            gemPrefix = val4;
                                        }
                                    }
                                    for (auto const [key3, val3] : statsMap)
                                    {
                                        if (key == key3)
                                        {
                                            gemStat = val3;
                                        }
                                    }
                                    gemName = gemPrefix + " " + gemStat;
                                    if (key == "Strength")
                                    {
                                        currentStr = currentStr + bonus;
                                    }
                                    if (key == "Dexterity")
                                    {
                                        currentDex = currentDex + bonus;
                                    }
                                    if (key == "Constitution")
                                    {
                                        currentCon = currentCon + bonus;
                                    }
                                    if (key == "Quickness")
                                    {
                                        currentQui = currentQui + bonus;
                                    }
                                    if (key == "Acuity")
                                    {
                                        currentAcu = currentAcu + bonus;
                                    }
                                    gems.push_back(gemName);
                                }
                                else
                                {
                                    totalImbueCost = totalImbueCost - bonus;
                                }
                            }
                        }
                    }
                }
            }
        }
        // Resists
        for (auto const [key, val] : resistRankingsMap) 
        {
            if ((gems.size() < 6) && (totalImbueCost < imbueCap))
            {
                if(val == 1)
                {
                    for (auto const [key2, val2]: resistsToCurrentDeficitMap)
                    {
                        if ((key == key2) && (val2 > 3))
                        {
                            std::string gemPrefix { };
                            std::string gemResist { };
                            std::string gemName { };
                            int bonusValue { };
                            int deficit = val2;
                            int cost { };
                            int bonus { };
                            // If cap can be reached for any stats with exact values starting at 10, consume a gem
                            if (deficit == 5)
                            {
                                gemPrefix = "flawed";
                            }
                            if (deficit == 7)
                            {
                                gemPrefix = "imperfect";
                            }
                            if (deficit == 9)
                            {
                                gemPrefix = "polished";
                            }
                            if (deficit == 11)
                            {
                                gemPrefix = "faceted";
                            }
                            if (deficit == 13)
                            {
                                gemPrefix = "precious";
                            }
                            else 
                            {
                                // If the deficit is large, pump stats in while imbue points are available, otherwise, increment downward
                                if (deficit >= 17)
                                {
                                    gemPrefix = "precious";
                                }
                                else if (deficit >= 13)
                                {
                                    gemPrefix = "polished";
                                }
                                else if (deficit >= 9)
                                {
                                    gemPrefix = "flawed";
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (auto const [key3, val3] : resistsMap)
                            {
                                if (key == key3)
                                {
                                    gemResist = val3;
                                }
                            }

                            for (auto const [key4, val4]: gemToResistsMap)
                            {
                                if (gemPrefix == val4)
                                {
                                    bonus = key4;
                                    cost = calcImbueCostResist(bonus);
                                }
                            }

                            gemName = gemPrefix + " " + gemResist;
                            std::cout << gemName << '\n';

                            totalImbueCost = totalImbueCost + cost;

                            if (totalImbueCost <= imbueCap)
                            {
                                gems.push_back(gemName);
                                for (auto const [currResist, value] : currentResistsMap)
                                {
                                    if (key == currResist)
                                    {
                                        currentResistsMap[currResist] = value + bonus;
                                    }
                                }
                            }
                            else
                            {
                                bonus = bonus - 4;
                                cost = scCalcRecursionResist(bonus);
                                totalImbueCost = totalImbueCost + cost;
                                if (totalImbueCost <= imbueCap)
                                {
                                    for (auto const [key4, val4]: gemToResistsMap)
                                    {
                                        if (bonus == key4)
                                        {
                                            gemPrefix = val4;
                                        }
                                    }
                                    for (auto const [key3, val3] : resistsMap)
                                    {
                                        if (key == key3)
                                        {
                                            gemResist = val3;
                                        }
                                    }
                                    gemName = gemPrefix + " " + gemResist;
                                    for (auto const [currResist, value] : currentResistsMap)
                                    {
                                        if (key == currResist)
                                        {
                                            currentResistsMap[currResist] = value + bonus;
                                        }
                                    }
                                    gems.push_back(gemName);
                                    for (auto const [currResist, value] : currentResistsMap)
                                    {
                                        if (key == currResist)
                                        {
                                            currentResistsMap[currResist] = value + bonus;
                                        }
                                    }
                                }
                                else
                                {
                                    totalImbueCost = totalImbueCost - bonus;
                                }
                            }
                            
                        }
                    }
                }
                if(val == 2)
                {
                    for (auto const [key2, val2]: resistsToCurrentDeficitMap)
                    {
                        if ((key == key2) && (val2 > 3))
                        {
                            std::string gemPrefix { };
                            std::string gemResist { };
                            std::string gemName { };
                            int bonusValue { };
                            int deficit = val2;
                            int cost { };
                            int bonus { };
                            // If cap can be reached for any stats with exact values starting at 10, consume a gem
                            if (deficit == 5)
                            {
                                gemPrefix = "flawed";
                            }
                            if (deficit == 7)
                            {
                                gemPrefix = "imperfect";
                            }
                            if (deficit == 9)
                            {
                                gemPrefix = "polished";
                            }
                            if (deficit == 11)
                            {
                                gemPrefix = "faceted";
                            }
                            if (deficit == 13)
                            {
                                gemPrefix = "precious";
                            }
                            else 
                            {
                                // If the deficit is large, pump stats in while imbue points are available, otherwise, increment downward
                                if (deficit >= 17)
                                {
                                    gemPrefix = "precious";
                                }
                                else if (deficit >= 13)
                                {
                                    gemPrefix = "polished";
                                }
                                else if (deficit >= 9)
                                {
                                    gemPrefix = "flawed";
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (auto const [key3, val3] : resistsMap)
                            {
                                if (key == key3)
                                {
                                    gemResist = val3;
                                }
                            }

                            for (auto const [key4, val4]: gemToResistsMap)
                            {
                                if (gemPrefix == val4)
                                {
                                    bonus = key4;
                                    cost = calcImbueCostResist(bonus);
                                }
                            }

                            gemName = gemPrefix + " " + gemResist;
                            for (auto const [currResist, value] : currentResistsMap)
                            {
                                if (key == currResist)
                                {
                                    currentResistsMap[currResist] = value + bonus;
                                }
                            }

                            totalImbueCost = totalImbueCost + cost;

                            if (totalImbueCost <= imbueCap)
                            {
                                gems.push_back(gemName);
                            }
                            else
                            {
                                bonus = bonus - 4;
                                cost = scCalcRecursionResist(bonus);
                                totalImbueCost = totalImbueCost + cost;
                                if (totalImbueCost <= imbueCap)
                                {
                                    for (auto const [key4, val4]: gemToResistsMap)
                                    {
                                        if (bonus == key4)
                                        {
                                            gemPrefix = val4;
                                        }
                                    }
                                    for (auto const [key3, val3] : resistsMap)
                                    {
                                        if (key == key3)
                                        {
                                            gemResist = val3;
                                        }
                                    }
                                    gemName = gemPrefix + " " + gemResist;
                                    for (auto const [currResist, value] : currentResistsMap)
                                    {
                                        if (key == currResist)
                                        {
                                            currentResistsMap[currResist] = value + bonus;
                                        }
                                    }
                                    gems.push_back(gemName);
                                }
                                else
                                {
                                    totalImbueCost = totalImbueCost - bonus;
                                }
                            }
                            
                        }
                    }
                }
                if(val == 3)
                {
                    for (auto const [key2, val2]: resistsToCurrentDeficitMap)
                    {
                        if ((key == key2) && (val2 > 3))
                        {
                            std::string gemPrefix { };
                            std::string gemResist { };
                            std::string gemName { };
                            int bonusValue { };
                            int deficit = val2;
                            int cost { };
                            int bonus { };
                            // If cap can be reached for any stats with exact values starting at 10, consume a gem
                            if (deficit == 5)
                            {
                                gemPrefix = "flawed";
                            }
                            if (deficit == 7)
                            {
                                gemPrefix = "imperfect";
                            }
                            if (deficit == 9)
                            {
                                gemPrefix = "polished";
                            }
                            if (deficit == 11)
                            {
                                gemPrefix = "faceted";
                            }
                            if (deficit == 13)
                            {
                                gemPrefix = "precious";
                            }
                            else 
                            {
                                // If the deficit is large, pump stats in while imbue points are available, otherwise, increment downward
                                if (deficit >= 17)
                                {
                                    gemPrefix = "precious";
                                }
                                else if (deficit >= 13)
                                {
                                    gemPrefix = "polished";
                                }
                                else if (deficit >= 9)
                                {
                                    gemPrefix = "flawed";
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (auto const [key3, val3] : resistsMap)
                            {
                                if (key == key3)
                                {
                                    gemResist = val3;
                                }
                            }

                            for (auto const [key4, val4]: gemToResistsMap)
                            {
                                if (gemPrefix == val4)
                                {
                                    bonus = key4;
                                    cost = calcImbueCostResist(bonus);
                                }
                            }

                            gemName = gemPrefix + " " + gemResist;
                            for (auto const [currResist, value] : currentResistsMap)
                            {
                                if (key == currResist)
                                {
                                    currentResistsMap[currResist] = value + bonus;
                                }
                            }

                            totalImbueCost = totalImbueCost + cost;

                            if (totalImbueCost <= imbueCap)
                            {
                                gems.push_back(gemName);
                            }
                            else
                            {
                                bonus = bonus - 4;
                                cost = scCalcRecursionResist(bonus);
                                totalImbueCost = totalImbueCost + cost;
                                if (totalImbueCost <= imbueCap)
                                {
                                    for (auto const [key4, val4]: gemToResistsMap)
                                    {
                                        if (bonus == key4)
                                        {
                                            gemPrefix = val4;
                                        }
                                    }
                                    for (auto const [key3, val3] : resistsMap)
                                    {
                                        if (key == key3)
                                        {
                                            gemResist = val3;
                                        }
                                    }
                                    gemName = gemPrefix + " " + gemResist;
                                    for (auto const [currResist, value] : currentResistsMap)
                                    {
                                        if (key == currResist)
                                        {
                                            currentResistsMap[currResist] = value + bonus;
                                        }
                                    }
                                    gems.push_back(gemName);
                                }
                                else
                                {
                                    totalImbueCost = totalImbueCost - bonus;
                                }
                            }
                            
                        }
                    }
                }
                if(val == 4)
                {
                    for (auto const [key2, val2]: resistsToCurrentDeficitMap)
                    {
                        if ((key == key2) && (val2 > 3))
                        {
                            std::string gemPrefix { };
                            std::string gemResist { };
                            std::string gemName { };
                            int bonusValue { };
                            int deficit = val2;
                            int cost { };
                            int bonus { };
                            // If cap can be reached for any stats with exact values starting at 10, consume a gem
                            if (deficit == 5)
                            {
                                gemPrefix = "flawed";
                            }
                            if (deficit == 7)
                            {
                                gemPrefix = "imperfect";
                            }
                            if (deficit == 9)
                            {
                                gemPrefix = "polished";
                            }
                            if (deficit == 11)
                            {
                                gemPrefix = "faceted";
                            }
                            if (deficit == 13)
                            {
                                gemPrefix = "precious";
                            }
                            else 
                            {
                                // If the deficit is large, pump stats in while imbue points are available, otherwise, increment downward
                                if (deficit >= 17)
                                {
                                    gemPrefix = "precious";
                                }
                                else if (deficit >= 13)
                                {
                                    gemPrefix = "polished";
                                }
                                else if (deficit >= 9)
                                {
                                    gemPrefix = "flawed";
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (auto const [key3, val3] : resistsMap)
                            {
                                if (key == key3)
                                {
                                    gemResist = val3;
                                }
                            }

                            for (auto const [key4, val4]: gemToResistsMap)
                            {
                                if (gemPrefix == val4)
                                {
                                    bonus = key4;
                                    cost = calcImbueCostResist(bonus);
                                }
                            }

                            gemName = gemPrefix + " " + gemResist;
                            for (auto const [currResist, value] : currentResistsMap)
                            {
                                if (key == currResist)
                                {
                                    currentResistsMap[currResist] = value + bonus;
                                }
                            }

                            totalImbueCost = totalImbueCost + cost;

                            if (totalImbueCost <= imbueCap)
                            {
                                gems.push_back(gemName);
                            }
                            else
                            {
                                bonus = bonus - 4;
                                cost = scCalcRecursionResist(bonus);
                                totalImbueCost = totalImbueCost + cost;
                                if (totalImbueCost <= imbueCap)
                                {
                                    for (auto const [key4, val4]: gemToResistsMap)
                                    {
                                        if (bonus == key4)
                                        {
                                            gemPrefix = val4;
                                        }
                                    }
                                    for (auto const [key3, val3] : resistsMap)
                                    {
                                        if (key == key3)
                                        {
                                            gemResist = val3;
                                        }
                                    }
                                    gemName = gemPrefix + " " + gemResist;
                                    for (auto const [currResist, value] : currentResistsMap)
                                    {
                                        if (key == currResist)
                                        {
                                            currentResistsMap[currResist] = value + bonus;
                                        }
                                    }
                                    gems.push_back(gemName);
                                }
                                else
                                {
                                    totalImbueCost = totalImbueCost - bonus;
                                }
                            }
                            
                        }
                    }
                }
                if(val == 5)
                {
                    for (auto const [key2, val2]: resistsToCurrentDeficitMap)
                    {
                        if ((key == key2) && (val2 > 3))
                        {
                            std::string gemPrefix { };
                            std::string gemResist { };
                            std::string gemName { };
                            int bonusValue { };
                            int deficit = val2;
                            int cost { };
                            int bonus { };
                            // If cap can be reached for any stats with exact values starting at 10, consume a gem
                            if (deficit == 5)
                            {
                                gemPrefix = "flawed";
                            }
                            if (deficit == 7)
                            {
                                gemPrefix = "imperfect";
                            }
                            if (deficit == 9)
                            {
                                gemPrefix = "polished";
                            }
                            if (deficit == 11)
                            {
                                gemPrefix = "faceted";
                            }
                            if (deficit == 13)
                            {
                                gemPrefix = "precious";
                            }
                            else 
                            {
                                // If the deficit is large, pump stats in while imbue points are available, otherwise, increment downward
                                if (deficit >= 17)
                                {
                                    gemPrefix = "precious";
                                }
                                else if (deficit >= 13)
                                {
                                    gemPrefix = "polished";
                                }
                                else if (deficit >= 9)
                                {
                                    gemPrefix = "flawed";
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (auto const [key3, val3] : resistsMap)
                            {
                                if (key == key3)
                                {
                                    gemResist = val3;
                                }
                            }

                            for (auto const [key4, val4]: gemToResistsMap)
                            {
                                if (gemPrefix == val4)
                                {
                                    bonus = key4;
                                    cost = calcImbueCostResist(bonus);
                                }
                            }

                            gemName = gemPrefix + " " + gemResist;
                            for (auto const [currResist, value] : currentResistsMap)
                            {
                                if (key == currResist)
                                {
                                    currentResistsMap[currResist] = value + bonus;
                                }
                            }

                            totalImbueCost = totalImbueCost + cost;

                            if (totalImbueCost <= imbueCap)
                            {
                                gems.push_back(gemName);
                            }
                            else
                            {
                                bonus = bonus - 4;
                                cost = scCalcRecursionResist(bonus);
                                totalImbueCost = totalImbueCost + cost;
                                if (totalImbueCost <= imbueCap)
                                {
                                    for (auto const [key4, val4]: gemToResistsMap)
                                    {
                                        if (bonus == key4)
                                        {
                                            gemPrefix = val4;
                                        }
                                    }
                                    for (auto const [key3, val3] : resistsMap)
                                    {
                                        if (key == key3)
                                        {
                                            gemResist = val3;
                                        }
                                    }
                                    gemName = gemPrefix + " " + gemResist;
                                    for (auto const [currResist, value] : currentResistsMap)
                                    {
                                        if (key == currResist)
                                        {
                                            currentResistsMap[currResist] = value + bonus;
                                        }
                                    }
                                    gems.push_back(gemName);
                                }
                                else
                                {
                                    totalImbueCost = totalImbueCost - bonus;
                                }
                            }
                            
                        }
                    }
                }
                if(val == 6)
                {
                    for (auto const [key2, val2]: resistsToCurrentDeficitMap)
                    {
                        if ((key == key2) && (val2 > 3))
                        {
                            std::string gemPrefix { };
                            std::string gemResist { };
                            std::string gemName { };
                            int bonusValue { };
                            int deficit = val2;
                            int cost { };
                            int bonus { };
                            // If cap can be reached for any stats with exact values starting at 10, consume a gem
                            if (deficit == 5)
                            {
                                gemPrefix = "flawed";
                            }
                            if (deficit == 7)
                            {
                                gemPrefix = "imperfect";
                            }
                            if (deficit == 9)
                            {
                                gemPrefix = "polished";
                            }
                            if (deficit == 11)
                            {
                                gemPrefix = "faceted";
                            }
                            if (deficit == 13)
                            {
                                gemPrefix = "precious";
                            }
                            else 
                            {
                                // If the deficit is large, pump stats in while imbue points are available, otherwise, increment downward
                                if (deficit >= 17)
                                {
                                    gemPrefix = "precious";
                                }
                                else if (deficit >= 13)
                                {
                                    gemPrefix = "polished";
                                }
                                else if (deficit >= 9)
                                {
                                    gemPrefix = "flawed";
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (auto const [key3, val3] : resistsMap)
                            {
                                if (key == key3)
                                {
                                    gemResist = val3;
                                }
                            }

                            for (auto const [key4, val4]: gemToResistsMap)
                            {
                                if (gemPrefix == val4)
                                {
                                    bonus = key4;
                                    cost = calcImbueCostResist(bonus);
                                }
                            }

                            gemName = gemPrefix + " " + gemResist;
                            for (auto const [currResist, value] : currentResistsMap)
                            {
                                if (key == currResist)
                                {
                                    currentResistsMap[currResist] = value + bonus;
                                }
                            }

                            totalImbueCost = totalImbueCost + cost;

                            if (totalImbueCost <= imbueCap)
                            {
                                gems.push_back(gemName);
                            }
                            else
                            {
                                bonus = bonus - 4;
                                cost = scCalcRecursionResist(bonus);
                                totalImbueCost = totalImbueCost + cost;
                                if (totalImbueCost <= imbueCap)
                                {
                                    for (auto const [key4, val4]: gemToResistsMap)
                                    {
                                        if (bonus == key4)
                                        {
                                            gemPrefix = val4;
                                        }
                                    }
                                    for (auto const [key3, val3] : resistsMap)
                                    {
                                        if (key == key3)
                                        {
                                            gemResist = val3;
                                        }
                                    }
                                    gemName = gemPrefix + " " + gemResist;
                                    for (auto const [currResist, value] : currentResistsMap)
                                    {
                                        if (key == currResist)
                                        {
                                            currentResistsMap[currResist] = value + bonus;
                                        }
                                    }
                                    gems.push_back(gemName);
                                }
                                else
                                {
                                    totalImbueCost = totalImbueCost - bonus;
                                }
                            }
                            
                        }
                    }
                }
                if(val == 7)
                {
                    for (auto const [key2, val2]: resistsToCurrentDeficitMap)
                    {
                        if ((key == key2) && (val2 > 3))
                        {
                            std::string gemPrefix { };
                            std::string gemResist { };
                            std::string gemName { };
                            int bonusValue { };
                            int deficit = val2;
                            int cost { };
                            int bonus { };
                            // If cap can be reached for any stats with exact values starting at 10, consume a gem
                            if (deficit == 5)
                            {
                                gemPrefix = "flawed";
                            }
                            if (deficit == 7)
                            {
                                gemPrefix = "imperfect";
                            }
                            if (deficit == 9)
                            {
                                gemPrefix = "polished";
                            }
                            if (deficit == 11)
                            {
                                gemPrefix = "faceted";
                            }
                            if (deficit == 13)
                            {
                                gemPrefix = "precious";
                            }
                            else 
                            {
                                // If the deficit is large, pump stats in while imbue points are available, otherwise, increment downward
                                if (deficit >= 17)
                                {
                                    gemPrefix = "precious";
                                }
                                else if (deficit >= 13)
                                {
                                    gemPrefix = "polished";
                                }
                                else if (deficit >= 9)
                                {
                                    gemPrefix = "flawed";
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (auto const [key3, val3] : resistsMap)
                            {
                                if (key == key3)
                                {
                                    gemResist = val3;
                                }
                            }

                            for (auto const [key4, val4]: gemToResistsMap)
                            {
                                if (gemPrefix == val4)
                                {
                                    bonus = key4;
                                    cost = calcImbueCostResist(bonus);
                                }
                            }

                            gemName = gemPrefix + " " + gemResist;
                            for (auto const [currResist, value] : currentResistsMap)
                            {
                                if (key == currResist)
                                {
                                    currentResistsMap[currResist] = value + bonus;
                                }
                            }

                            totalImbueCost = totalImbueCost + cost;

                            if (totalImbueCost <= imbueCap)
                            {
                                gems.push_back(gemName);
                            }
                            else
                            {
                                bonus = bonus - 4;
                                cost = scCalcRecursionResist(bonus);
                                totalImbueCost = totalImbueCost + cost;
                                if (totalImbueCost <= imbueCap)
                                {
                                    for (auto const [key4, val4]: gemToResistsMap)
                                    {
                                        if (bonus == key4)
                                        {
                                            gemPrefix = val4;
                                        }
                                    }
                                    for (auto const [key3, val3] : resistsMap)
                                    {
                                        if (key == key3)
                                        {
                                            gemResist = val3;
                                        }
                                    }
                                    gemName = gemPrefix + " " + gemResist;
                                    for (auto const [currResist, value] : currentResistsMap)
                                    {
                                        if (key == currResist)
                                        {
                                            currentResistsMap[currResist] = value + bonus;
                                        }
                                    }
                                    gems.push_back(gemName);
                                }
                                else
                                {
                                    totalImbueCost = totalImbueCost - bonus;
                                }
                            }
                            
                        }
                    }
                }
                if(val == 8)
                {
                    for (auto const [key2, val2]: resistsToCurrentDeficitMap)
                    {
                        if ((key == key2) && (val2 > 3))
                        {
                            std::string gemPrefix { };
                            std::string gemResist { };
                            std::string gemName { };
                            int bonusValue { };
                            int deficit = val2;
                            int cost { };
                            int bonus { };
                            // If cap can be reached for any stats with exact values starting at 10, consume a gem
                            if (deficit == 5)
                            {
                                gemPrefix = "flawed";
                            }
                            if (deficit == 7)
                            {
                                gemPrefix = "imperfect";
                            }
                            if (deficit == 9)
                            {
                                gemPrefix = "polished";
                            }
                            if (deficit == 11)
                            {
                                gemPrefix = "faceted";
                            }
                            if (deficit == 13)
                            {
                                gemPrefix = "precious";
                            }
                            else 
                            {
                                // If the deficit is large, pump stats in while imbue points are available, otherwise, increment downward
                                if (deficit >= 17)
                                {
                                    gemPrefix = "precious";
                                }
                                else if (deficit >= 13)
                                {
                                    gemPrefix = "polished";
                                }
                                else if (deficit >= 9)
                                {
                                    gemPrefix = "flawed";
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (auto const [key3, val3] : resistsMap)
                            {
                                if (key == key3)
                                {
                                    gemResist = val3;
                                }
                            }

                            for (auto const [key4, val4]: gemToResistsMap)
                            {
                                if (gemPrefix == val4)
                                {
                                    bonus = key4;
                                    cost = calcImbueCostResist(bonus);
                                }
                            }

                            gemName = gemPrefix + " " + gemResist;
                            for (auto const [currResist, value] : currentResistsMap)
                            {
                                if (key == currResist)
                                {
                                    currentResistsMap[currResist] = value + bonus;
                                }
                            }

                            totalImbueCost = totalImbueCost + cost;

                            if (totalImbueCost <= imbueCap)
                            {
                                gems.push_back(gemName);
                            }
                            else
                            {
                                bonus = bonus - 4;
                                cost = scCalcRecursionResist(bonus);
                                totalImbueCost = totalImbueCost + cost;
                                if (totalImbueCost <= imbueCap)
                                {
                                    for (auto const [key4, val4]: gemToResistsMap)
                                    {
                                        if (bonus == key4)
                                        {
                                            gemPrefix = val4;
                                        }
                                    }
                                    for (auto const [key3, val3] : resistsMap)
                                    {
                                        if (key == key3)
                                        {
                                            gemResist = val3;
                                        }
                                    }
                                    gemName = gemPrefix + " " + gemResist;
                                    for (auto const [currResist, value] : currentResistsMap)
                                    {
                                        if (key == currResist)
                                        {
                                            currentResistsMap[currResist] = value + bonus;
                                        }
                                    }
                                    gems.push_back(gemName);
                                }
                                else
                                {
                                    totalImbueCost = totalImbueCost - bonus;
                                }
                            }
                            
                        }
                    }
                }
                if(val == 9)
                {
                    for (auto const [key2, val2]: resistsToCurrentDeficitMap)
                    {
                        if ((key == key2) && (val2 > 3))
                        {
                            std::string gemPrefix { };
                            std::string gemResist { };
                            std::string gemName { };
                            int bonusValue { };
                            int deficit = val2;
                            int cost { };
                            int bonus { };
                            // If cap can be reached for any stats with exact values starting at 10, consume a gem
                            if (deficit == 5)
                            {
                                gemPrefix = "flawed";
                            }
                            if (deficit == 7)
                            {
                                gemPrefix = "imperfect";
                            }
                            if (deficit == 9)
                            {
                                gemPrefix = "polished";
                            }
                            if (deficit == 11)
                            {
                                gemPrefix = "faceted";
                            }
                            if (deficit == 13)
                            {
                                gemPrefix = "precious";
                            }
                            else 
                            {
                                // If the deficit is large, pump stats in while imbue points are available, otherwise, increment downward
                                if (deficit >= 17)
                                {
                                    gemPrefix = "precious";
                                }
                                else if (deficit >= 13)
                                {
                                    gemPrefix = "polished";
                                }
                                else if (deficit >= 9)
                                {
                                    gemPrefix = "flawed";
                                }
                                else
                                {
                                    break;
                                }
                            }
                            for (auto const [key3, val3] : resistsMap)
                            {
                                if (key == key3)
                                {
                                    gemResist = val3;
                                }
                            }

                            for (auto const [key4, val4]: gemToResistsMap)
                            {
                                if (gemPrefix == val4)
                                {
                                    bonus = key4;
                                    cost = calcImbueCostResist(bonus);
                                }
                            }

                            gemName = gemPrefix + " " + gemResist;
                            for (auto const [currResist, value] : currentResistsMap)
                            {
                                if (key == currResist)
                                {
                                    currentResistsMap[currResist] = value + bonus;
                                }
                            }

                            totalImbueCost = totalImbueCost + cost;

                            if (totalImbueCost <= imbueCap)
                            {
                                gems.push_back(gemName);
                            }
                            else
                            {
                                bonus = bonus - 4;
                                cost = scCalcRecursionResist(bonus);
                                totalImbueCost = totalImbueCost + cost;
                                if (totalImbueCost <= imbueCap)
                                {
                                    for (auto const [key4, val4]: gemToResistsMap)
                                    {
                                        if (bonus == key4)
                                        {
                                            gemPrefix = val4;
                                        }
                                    }
                                    for (auto const [key3, val3] : resistsMap)
                                    {
                                        if (key == key3)
                                        {
                                            gemResist = val3;
                                        }
                                    }
                                    gemName = gemPrefix + " " + gemResist;
                                    for (auto const [currResist, value] : currentResistsMap)
                                    {
                                        if (key == currResist)
                                        {
                                            currentResistsMap[currResist] = value + bonus;
                                        }
                                    }
                                    gems.push_back(gemName);
                                }
                                else
                                {
                                    totalImbueCost = totalImbueCost - bonus;
                                }
                            }
                            
                        }
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
    createSCMaps();
    displayIntroText();
    getTemplateTitle();
    getClass();
    // createTemplateTable();
    // scCalculator();

    return 0;
}