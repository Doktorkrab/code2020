from typing import List
from json import dumps


class Judge:
    def __init__(self):
        self.url: str = ''
        self.username: str = ''
        self.passwords: str = ''
        self.label: str = ''

    def __str__(self):
        return f"Judge(url={self.url}, contests={self.contests}, username={self.username}, passwords={self.passwords}, label={self.label})"
    def __repr__(self):
        return str(self)
