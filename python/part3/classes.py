import re

string = "xzi415 is not my student ID. I wonder who it belongs to."

# find lines beginning with an abc123 id
if re.search(r"^[a-zA-Z][a-zA-Z][a-zA-Z]\d\d\d", string):
    print("'" + string + "' begins with a valid student ID")
else:
    print("'" + string + "' doesn't begin with a valid student ID")
