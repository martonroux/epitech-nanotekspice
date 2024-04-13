from data import Data
from elements.utils import save_file


def generate_and_comp(name: str, num_inputs: int, filename: str) -> str:
    data = Data(name)

    for i in range(num_inputs - 1):
        data.add_chipset("and", "and_" + str(i))

    data.add_link(name, 1, "and_0", 1)
    for i in range(num_inputs - 1):
        data.add_link(name, i + 2, "and_" + str(i), 2)
        if i > 0:
            data.add_link("and_" + str(i - 1), 3, "and_" + str(i), 1)
    data.add_link("and_" + str(num_inputs - 2), 3, name, num_inputs + 1)

    res = data.str()

    save_file(filename=filename, data=res)
    return res


def generate_or_comp(name: str, num_inputs: int, filename: str) -> str:
    data = Data(name)

    for i in range(num_inputs - 1):
        data.add_chipset("or", "or_" + str(i))

    data.add_link(name, 1, "or_0", 1)
    for i in range(num_inputs - 1):
        data.add_link(name, i + 2, "or_" + str(i), 2)
        if i > 0:
            data.add_link("or_" + str(i - 1), 3, "or_" + str(i), 1)
    data.add_link("or_" + str(num_inputs - 2), 3, name, num_inputs + 1)

    res = data.str()

    save_file(filename=filename, data=res)
    return res
