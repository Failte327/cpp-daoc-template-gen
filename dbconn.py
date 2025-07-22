from fastsql import *
from dataclasses import dataclass

@dataclass
class Items:
    name:str
    item_type:str
    slot:str
    level_requirement:int
    realm:str
    utility:int
    utility_single:int
    bonus_types:str
    bonus_values:str
    proc1_json:str
    proc2_json:str
    use1_json:str
    use2_json:str
    passive_json:str
    react1_json:str
    react2_json:str
    id:int=None


# Original data class from CPP
# int:id
# str:name
# str:item_type
# std::string slot;
# int level_requirement;
# std::string realm;
# int utility;
# int utility_single;
# std::string bonus_types;
# std::string bonus_values;
# std::string proc1_json;
# std::string proc2_json;
# std::string use1_json;
# std::string use2_json;
# std::string passive_json;
# std::string react1_json;
# std::string react2_json;