from data import Data
from elements.decoder import generate_decoder
from elements.utils import save_file
from elements.basic_logic import generate_or_comp
import math


def generate_ram(name: str, num_bytes: int, filename: str):
    # I/O:
    # [1, num_inputs] -> decoder inputs
    # num_inputs + 1 -> clock
    # num_inputs + 2 -> Write Enable (WE)
    # ]num_inputs + 2, num_inputs + 10] -> A0 - A7 bit inputs
    # num_inputs + 11 -> Output Enable (OE)
    # ]num_inputs + 11, num_inputs + 19] -> Q0 - Q7 bit outputs
    data = Data(name)

    num_inputs = math.ceil(math.log2(num_bytes))
    # Creating decoder
    decoder_name = "GEN_decoder_" + str(num_inputs) + "_to_" + str(2 ** num_inputs)
    generate_decoder(decoder_name, num_inputs, f"./output_files/{decoder_name}.nts")

    data.add_chipset(decoder_name, "decoder")

    for i in range(1, num_inputs + 1):
        data.add_link(name, i, "decoder", i)

    # Creating ram bytes
    for i in range(num_bytes):
        data.add_chipset("ram_byte", "byte_" + str(i))

    # Creating AND gate for Write Enable and Clock
    data.add_chipset("and", "and_clock")
    data.add_link("and_clock", 1, name, num_inputs + 1)         # Linking to RAM clock input
    data.add_link("and_clock", 2, name, num_inputs + 2)         # Linking to RAM WE input (Write Enable)

    # Creating AND gates for conditional clock, and linking them
    for i in range(num_bytes):
        data.add_chipset("and", "and_" + str(i))                        # Creating
        data.add_link("and_" + str(i), 3, "byte_" + str(i), 9)     # Linking to Byte
        data.add_link("and_clock", 3, "and_" + str(i), 1)   # Linking to Clock input of RAM
        data.add_link("decoder", num_inputs + i + 1,  "and_" + str(i), 2)   # Linking to decoder output

    # Linking data inputs to Bytes
    for i in range(8):
        for j in range(num_bytes):
            data.add_link("byte_" + str(j), i + 1, name, num_inputs + i + 3)

    # Creating Byte OEs and linking their inputs
    for i in range(num_bytes):
        data.add_chipset("byte_oe", "byte_oe_" + str(i))
        data.add_link("decoder", num_inputs + i + 1, "byte_oe_" + str(i), 1)    # Linking decoder to SEL
        # input of Byte OE
        data.add_link(name, num_inputs + 11, "byte_oe_" + str(i), 2)    # Linking to RAM OE input
        for j in range(8):
            data.add_link("byte_" + str(i), j + 10, "byte_oe_" + str(i), j + 3)     # Linking all outputs of Byte to OE

    # Creating OR components for each bit value
    or_name = str(num_bytes) + "_or_GEN"
    generate_or_comp(or_name, num_bytes, f"./output_files/{or_name}.nts")

    for i in range(8):
        data.add_chipset(or_name, "or_" + str(i))

    # Link OR components to each Byte OE output
    for i in range(8):
        for j in range(num_bytes):
            data.add_link("or_" + str(i), j + 1, "byte_oe_" + str(j), i + 11)

    # Link OR components outputs to RAM outputs
    for i in range(8):
        data.add_link("or_" + str(i), num_bytes + 1, name, num_inputs + 12 + i)

    save_file(filename, data.str())
