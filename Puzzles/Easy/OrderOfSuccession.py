import sys
import math


class Person:
    def __init__(self, name, parent, birth, death, religion, gender):
        self.name = name
        self.parent = parent
        self.birth = int(birth)
        self.death = int(death) if death != '-' else None
        self.religion = religion
        self.isfemale = gender == 'F'
        self.children = []

    def addChild(self, child):
        if child.parent == self.name:
            self.children += [child]
        else:
            for royal in self.children:
                royal.addChild(child)

    def traverse(self):
        succession = []

        # Exclude dead and catholic royals.
        if not self.death and self.religion == 'Anglican':
            succession += [self]

        # Ordering rules.
        sortedChildren = sorted(self.children, key=lambda child: (child.isfemale, child.birth))

        # Traverse subnodes.
        for child in sortedChildren:
            succession += child.traverse()

        return succession


n = int(input())

# Queen
queen = Person(*input().split())

for i in range(n-1):
    royal = Person(*input().split())
    queen.addChild(royal)

for p in queen.traverse():
    print(p.name)
