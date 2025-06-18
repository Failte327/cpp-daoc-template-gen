-- SQLite
CREATE TABLE Items (
    id INTEGER,
    name TEXT DEFAULT(NULL),
    item_type TEXT DEFAULT(NULL),
    slot TEXT DEFAULT(NULL),
    level_requirement INTEGER DEFAULT(NULL),
    realm TEXT DEFAULT(NULL),
    utility INTEGER DEFAULT(NULL),
    utility_single INTEGER DEFAULT(NULL),
    allowed_classes TEXT DEFAULT(NULL),
    bonus_types TEXT DEFAULT(NULL),
    bonus_values TEXT DEFAULT(NULL),
    proc1_json BLOB DEFAULT(NULL),
    proc2_json BLOB DEFAULT(NULL),
    use1_json BLOB DEFAULT(NULL),
    use2_json BLOB DEFAULT(NULL),
    passive_json BLOB DEFAULT(NULL),
    react1_json BLOB DEFAULT(NULL),
    react2_json BLOB DEFAULT(NULL),
    PRIMARY KEY (id)
);