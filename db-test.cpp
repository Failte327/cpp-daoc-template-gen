#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <string>
#include <iostream>

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

int main() 
{
    auto sqlite3 = std::make_unique<dbo::backend::Sqlite3>("daoc-eden-item-db.sqlite3");
    dbo::Session session;
    session.setConnection(std::move(sqlite3));
    session.mapClass<Items>("items");
    dbo::Transaction transaction(session);
    int count = session.query<int>("select count(*) from items");
    dbo::ptr<Items> item = session.find<Items>().where("name = ?").bind("Wintery Seekers Vest");
    std::cout << std::to_string(count) + "\n";
    std::cout << "Item Slot: " << item->slot << std::endl;
    return 0;
}