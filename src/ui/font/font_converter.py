#!/usr/bin/env python3
# font bitmap whatever converter
from PIL import Image
import sys

CHAR_WIDTH = 5 # how wide a character is

if len(sys.argv) < 4:
    # meson moment kind of
    print(f"{sys.argv[0]} input_file output_file array_name", file=sys.stderr)
    sys.exit(-1)

img = Image.open(sys.argv[1])
# image must be 8 px tall - 1 column = 1 byte
assert img.height == 8
# rotate 270deg so columns become rows and the first column becomes the first row
img = img.transpose(Image.Transpose.ROTATE_270)

with (sys.stdout if sys.argv[2] == "-" else open(sys.argv[2], "w")) as out_f:
    print(f"#include <stdint.h>\nconst uint8_t {sys.argv[3]}[] = {{", file=out_f)
    data = img.getdata(band=0)
    for i in range(img.height):
        if i % CHAR_WIDTH == 0:
            print(f"\t// '{chr((i//CHAR_WIDTH) + 33)}'", file=out_f)
        
        # get pixels from current line
        line = (data[i * img.width + (7-bit)] for bit in range(img.width))
        # pack the bits together
        byte = 0
        for bit, v in enumerate(line):
            if v == 0: # black pixels - set bit
                byte |= 1 << bit
        
        print(f"\t0b{byte:0>8b},", file=out_f)
    print("};", file=out_f)
