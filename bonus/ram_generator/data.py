from typing import List


class Link:
    def __init__(self, name1: str, pin1: int, name2: str, pin2: int):
        self.name1 = name1
        self.pin1 = pin1
        self.name2 = name2
        self.pin2 = pin2

    def str(self):
        return f"{self.name1}:{self.pin1} {self.name2}:{self.pin2}"


class Chipset:
    def __init__(self, type: str, name: str):
        self.type = type
        self.name = name

    def str(self):
        return f"{self.type} {self.name}"


class Data:
    def __init__(self, name: str):
        self.name = name
        self.chipsets: List[Chipset] = []
        self.links: List[Link] = []

    def add_chipset(self, type: str, name: str) -> None:
        for chipset in self.chipsets:
            if chipset.name == name:
                raise ValueError("Program tried to create two components with the same name in the same file.")
        self.chipsets.append(Chipset(type, name))

    def add_link(self, name1: str, pin1: int, name2: str, pin2: int):
        self.links.append(Link(name1, pin1, name2, pin2))

    def str_chipsets(self):
        res: str = "circuit " + self.name + "\n"

        for chipset in self.chipsets:
            res += chipset.str()
            res += "\n"

        return res

    def str_links(self):
        res: str = ""

        for link in self.links:
            res += link.str()
            res += "\n"

        return res

    def str(self) -> str:
        res = ".chipsets:\n"
        res += self.str_chipsets()
        res += "\n.links:\n"
        res += self.str_links()

        return res
