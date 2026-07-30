import sys
import struct
import zlib

bin_file = "./Debug/Boot_App_Test.bin"
c_file = "./Debug/ota_image.h"
array_name = "ota_image_bin"

# --- CONFIG : ton header OTA ---
MAGIC       = 0xDEADBEEF
VERSION     = 0x9E98FC31

# --- Lecture du binaire ---
with open(bin_file, "rb") as f:
    app_data = f.read()

IMAGE_SIZE = len(app_data)

# --- Calcul CRC32 sur l'application ---
CRC = zlib.crc32(app_data) & 0xFFFFFFFF

# --- Construction du header OTA ---
ota_header = struct.pack("<IIII", MAGIC, IMAGE_SIZE, CRC, VERSION)

# --- Fusion header + application ---
full_image = ota_header + app_data

# --- Génération du fichier C ---
with open(c_file, "w") as f:
    f.write(f"const unsigned char {array_name}[] = {{\n")

    for i, b in enumerate(full_image):
        f.write(f"0x{b:02X}, ")
        if (i + 1) % 12 == 0:
            f.write("\n")

    f.write("\n};\n")
    f.write(f"const unsigned int {array_name}_len = {len(full_image)};\n")
