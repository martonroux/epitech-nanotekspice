#!/usr/bin/python3
import sys

from elements.basic_logic import generate_and_comp, generate_or_comp
from elements.decoder import generate_decoder
from elements.ram import generate_ram


def main():
    if len(sys.argv) == 1:
        print("Usage: ./generate_ram [number of bytes]")

    try:
        if int(sys.argv[1]) < 0:
            print("Argument at position 1 should be a positive integer")
            exit(84)
        print("Generating", sys.argv[1], "bytes of RAM...")
        generate_ram("ram_GEN", int(sys.argv[1]), "./output_files/ram_GEN.nts")
        print("Done generating RAM! Files can be found at: ./output_files/")
    except ValueError:
        print("Argument at position 1 should be a positive integer")
        exit(84)


if __name__ == "__main__":
    main()
