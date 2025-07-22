from fasthtml.common import *
from sqlalchemy import text
from dbconn import Items
from fastsql import *

app, rt = fast_app()
db = Database('sqlite:///daoc-eden-item-db.sqlite3')
items = db.create(Items)
print(items(where="name LIKE 'Frigid%%'"))

@rt("/")
def get():
    return Titled("DAOC Eden EasyTemplate", P("Speedrunning a template"), P())

@rt("/login")
def get():
    return Titled("DAOC Eden EasyTemplate", P("Login"))

@rt("/items")
def get():
    return Titled("DAOC Eden EasyTemplate", P(items_string))

serve()