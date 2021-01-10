from typing import Dict, List
from judge import Judge
from json import dump, load

USERS_FILE = 'users.db'


class Base(object):
    def __init__(self):
        self.users: Dict[int, List[Judge]] = dict()
        self.load()

    def save(self):
        to_save = dict()
        print(self.users)
        for k in self.users:
            v = self.users[k]
            to_save[k] = [x.__dict__ for x in v]
        with open(USERS_FILE, "w") as f:
            dump(to_save, f)

    def load(self):
        try:
            with open(USERS_FILE, "r") as f:
                loaded = load(f)
                for x in loaded:
                    y = loaded[x]
                    line = []
                    for z in y:
                        e = Judge()
                        e.__dict__ = z
                        line.append(e)
                    self.users[x] = line
        except FileNotFoundError as e:
            print(e)

    def __str__(self):
        return f"Users:\n" + '\n'.join(list(map(lambda x: '\t' + str(x), self.users)))

    def __repr__(self):
        return str(self)
