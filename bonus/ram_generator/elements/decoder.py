from data import Data
from elements.basic_logic import generate_and_comp
from elements.utils import save_file


def generate_decoder(name: str, input_size: int, filename: str):
    data = Data(name)
    num_outputs = 2 ** input_size

    and_name = str(input_size) + "_and_GEN"
    generate_and_comp(and_name, input_size, f"./output_files/{and_name}.nts")

    for i in range(num_outputs):
        data.add_chipset(and_name, "and_" + str(i))

    for i in range(input_size):
        data.add_chipset("not", "not_" + str(i))
        data.add_link(name, i + 1, "not_" + str(i), 1)

    for i in range(input_size):
        for j in range(num_outputs):
            if (j // (2 ** i)) % 2 == 0:
                data.add_link("not_" + str(i), 2, "and_" + str(j), i + 1)
            else:
                data.add_link(name, i + 1, "and_" + str(j), i + 1)

    for i in range(num_outputs):
        data.add_link(name, i + input_size + 1, "and_" + str(i), input_size + 1)
    save_file(filename, data.str())
