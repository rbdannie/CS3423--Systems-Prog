import sys
import re

# skipping validation for brevity

# pattern = r"^([^:]*):[^:]*:[^:]*:[^:]*:([^:]*):[^:]*:([^:]*)$"
delimiter = ":"

try:
    with open(sys.argv[1], 'r') as passwd:
        for line in passwd:
            tokens = re.split(delimiter, line.rstrip())
            if tokens:
                print(tokens[4] + "'s username is " +
                      tokens[0] + " and they use " +
                      tokens[6] + " as their shell.")
except IOError:
    print("Error opening file")
    sys.exit(1)
