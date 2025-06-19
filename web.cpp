#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WWebWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WBoxLayout.h>
#include <Wt/WComboBox.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <string>
#include <iostream>
#include <vector>
#include <curl/curl.h>
#include <cstdlib>

namespace dbo = Wt::Dbo;

class Items {
public:
    int id;
    std::string name;
    std::string item_type;
    std::string slot;
    int level_requirement;
    std::string realm;
    int utility;
    int utility_single;
    std::string bonus_types;
    std::string bonus_values;
    std::string proc1_json;
    std::string proc2_json;
    std::string use1_json;
    std::string use2_json;
    std::string passive_json;
    std::string react1_json;
    std::string react2_json;

    template<class Action>
    void persist(Action& a)
    {
        dbo::field(a, id, "id");
        dbo::field(a, name, "name");
        dbo::field(a, item_type, "item_type");
        dbo::field(a, slot, "slot");
        dbo::field(a, level_requirement, "level_requirement");
        dbo::field(a, realm, "realm");
        dbo::field(a, utility, "utility");
        dbo::field(a, utility_single, "utility_single");
        dbo::field(a, bonus_types, "bonus_types");
        dbo::field(a, bonus_values, "bonus_values");
        dbo::field(a, proc1_json, "proc1_json");
        dbo::field(a, proc2_json, "proc2_json");
        dbo::field(a, use1_json, "use1_json");
        dbo::field(a, use2_json, "use2_json");
        dbo::field(a, passive_json, "passive_json");
        dbo::field(a, react1_json, "react1_json");
        dbo::field(a, react2_json, "react2_json");
    }
};

using namespace Wt;

class WebApplication : public Wt::WApplication
{
    public:
        WebApplication(const Wt::WEnvironment& env);
    
    private:
        Wt::WText *title_;
        Wt::WLineEdit *templateName_;
        Wt::WLineEdit *characterName_;
        Wt::WText *chestPiece_;
        Wt::WText *arms_;
        Wt::WText *legs_;
        Wt::WText *boots_;
        Wt::WText *hands_;
        Wt::WText *helm_;
        Wt::WText *mythirian_;
        Wt::WText *necklace_;
        Wt::WText *jewel_;
        Wt::WText *leftRing_;
        Wt::WText *leftBracer_;
        Wt::WText *rightRing_;
        Wt::WText *rightBracer_;
        Wt::WText *cloak_;
        Wt::WText *belt_;
        Wt::WText *oneHandWeapon_;
        Wt::WText *offHandWeapon_;
        Wt::WText *twoHandWeapon_;
        Wt::WText *rangedWeapon_;
        Wt::WComboBox *classSelector_;
        Wt::WLineEdit *searchBar_;
        Wt::WPushButton *searchButton_;
};

WebApplication::WebApplication(const Wt::WEnvironment& env) : Wt::WApplication(env)
{
    std::vector<std::string> tanks{"warrior", "berserker", "savage", "shadowblade", "blademaster", "hero", "nightshade", "armsman", "infiltrator", "mercenary"};
    std::vector<std::string> hybrids{"friar", "heretic", "minstrel", "paladin", "reaver", "champion", "warden", "valewalker", "skald", "thane", "valkyrie", "occultist"};
    std::vector<std::string> casters{"cabalist", "necromancer", "sorcerer", "theurgist", "wizard", "animist", "bainshee", "eldritch", "enchanter", "mentalist", "bonedancer", "runemaster", "spiritmaster"};
    std::vector<std::string> supports{"cleric", "healer", "shaman", "bard", "druid"};
    std::vector<std::string> archers{"hunter", "scout", "ranger"};


    setTitle("Reklewt's Ultimate Site");
    setCssTheme("bootstrap");

    title_ = root()->addNew<WText>("Reklewt's Template Calculator");
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WText>("Template Name: ");
    templateName_ = root()->addNew<Wt::WLineEdit>();
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WText>("Character Name: ");
    characterName_ = root()->addNew<Wt::WLineEdit>();
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WText>("Class: ");
    classSelector_ = root()->addNew<Wt::WComboBox>();
    for (int i = 0; i < tanks.size(); i++)
    {
        classSelector_->addItem(tanks[i]);
    }
    for (int i = 0; i < hybrids.size(); i++)
    {
        classSelector_->addItem(hybrids[i]);
    }
    for (int i = 0; i < casters.size(); i++)
    {
        classSelector_->addItem(casters[i]);
    }
    for (int i = 0; i < supports.size(); i++)
    {
        classSelector_->addItem(supports[i]);
    }
    for (int i = 0; i < archers.size(); i++)
    {
        classSelector_->addItem(archers[i]);
    }
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WText>("Chest Piece: ");
    chestPiece_ = root()->addNew<Wt::WText>();
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WText>("Arms: ");
    arms_ = root()->addNew<Wt::WText>();
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WText>("Legs: ");
    legs_ = root()->addNew<Wt::WText>();
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WText>("Boots: ");
    boots_= root()->addNew<Wt::WText>();
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WText>("Hands: ");
    hands_ = root()->addNew<Wt::WText>();
    root()->addNew<Wt::WBreak>();
    root()-> addNew<Wt::WText>("Helm: ");
    helm_= root()->addNew<Wt::WText>();
    root()->addNew<Wt::WBreak>();
    root()-> addNew<Wt::WText>("Mythirian: ");
    mythirian_= root()->addNew<Wt::WText>();
    root()->addNew<Wt::WBreak>();
    root()-> addNew<Wt::WText>("Necklace: ");
    necklace_= root()->addNew<Wt::WText>();
    root()->addNew<Wt::WBreak>();
    root()-> addNew<Wt::WText>("Jewel: ");
    jewel_= root()->addNew<Wt::WText>();
    root()->addNew<Wt::WBreak>();
    root()-> addNew<Wt::WText>("Left Ring: ");
    leftRing_= root()->addNew<Wt::WText>();
    root()->addNew<Wt::WBreak>();
    root()-> addNew<Wt::WText>("Left Bracer: ");
    leftBracer_= root()->addNew<Wt::WText>();
    root()->addNew<Wt::WBreak>();
    root()-> addNew<Wt::WText>("Right Ring: ");
    rightRing_= root()->addNew<Wt::WText>();
    root()->addNew<Wt::WBreak>();
    root()-> addNew<Wt::WText>("Right Bracer: ");
    rightBracer_= root()->addNew<Wt::WText>();
    root()->addNew<Wt::WBreak>();
    root()-> addNew<Wt::WText>("Belt: ");
    belt_= root()->addNew<Wt::WText>();
    root()->addNew<Wt::WBreak>();
    root()-> addNew<Wt::WText>("Cloak: ");
    cloak_= root()->addNew<Wt::WText>();

    // Whitespace
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WBreak>();
    searchBar_ = root()->addNew<Wt::WLineEdit>();
    searchButton_ = root()->addNew<Wt::WPushButton>("Search");

    // Whitespace
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WBreak>();
    root()->addNew<Wt::WBreak>();

    auto search = [this]{
        auto sqlite3 = std::make_unique<dbo::backend::Sqlite3>("daoc-eden-item-db.sqlite3");
        auto searchText = searchBar_->text();
        dbo::Session session;
        session.setConnection(std::move(sqlite3));
        session.mapClass<Items>("items");
        dbo::Transaction transaction(session);
        std::vector<dbo::ptr<Items>> resultList;
        int counter = 0;
        dbo::collection<dbo::ptr<Items>> itemResults = session.find<Items>().where("name LIKE ?").bind(searchText.toUTF8().c_str()).resultList();
        for (dbo::collection<dbo::ptr<Items>>::iterator iter = itemResults.begin(); iter != itemResults.end(); ++iter)
        {
            ++counter;
            resultList.push_back(*iter);
        }
        for (int i = 0; i < resultList.size(); i++)
        {
            Wt::WString text = "Item Name: " + resultList[i]->name + "\nItem Type: " + resultList[i]->item_type + "\nItem Slot: " + resultList[i]->slot + "\nRealm: " + resultList[i]->realm + "\nUtility: " + std::to_string(resultList[i]->utility) + "\n";
            root()->addNew<Wt::WText>(text);
            root()->addNew<Wt::WPushButton>("Equip");
            // root()->addNew<Wt::WPushButton>("Equip")->clicked().connect([this, resultList, i, text]
            // {
            //     std::string slot_ = resultList[i]->slot;
            //     if (slot_ == "Chest")
            //     {
            //         chestPiece_->setText(text);
            //     } else if (slot_ == "Right Hand")
            //     {
            //         oneHandWeapon_->setText(text);
            //     } else if (slot_ == "Cloak")
            //     {
            //         cloak_->setText(text);
            //     } else if (slot_ == "Jewel")
            //     {
            //         jewel_->setText(text);
            //     } else if (slot_ == "Two Handed")
            //     {
            //         twoHandWeapon_->setText(text);
            //     } else if (slot_ == "Legs")
            //     {
            //         legs_->setText(text);
            //     } else if (slot_ == "Left Hand")
            //     {
            //         offHandWeapon_->setText(text);
            //     } else if (slot_ == "Boots")
            //     {
            //         boots_->setText(text);
            //     } else if (slot_ == "Arms")
            //     {
            //         arms_->setText(text);
            //     } else if (slot_ == "Helm")
            //     {
            //         helm_->setText(text);
            //     } else if (slot_ == "Belt")
            //     {
            //         belt_->setText(text);
            //     } else if (slot_ == "Gloves")
            //     {
            //         hands_->setText(text);
            //     } else if (slot_ == "Bracer")
            //     {
            //         leftBracer_->setText(text);
            //     } else if (slot_ == "Ring")
            //     {
            //         leftRing_->setText(text);
            //     } else if (slot_ == "Necklace")
            //     {
            //         necklace_->setText(text);
            //     } else if (slot_ == "Mythirian")
            //     {
            //         mythirian_->setText(text);
            //     };
            // });
            root()->addNew<Wt::WBreak>();
        }
    };
    searchButton_->clicked().connect(search);

};

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<WebApplication>(env);
    });
};

// Build:  g++ -std=c++14 -o web web.cpp -lwthttp -lwt -lwtdbo -lwtdbosqlite3
// Run: ./web --docroot . --http-address 0.0.0.0 --http-port 3000