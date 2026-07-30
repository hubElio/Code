import struct
import sys

BOOT_START = 0x08000000
APP_HEADER_ADDR = 0x08008000
APP_START_ADDR = 0x0800C000

bin_path = sys.argv[1] if len(sys.argv) > 1 else "full.bin"

with open(bin_path, "rb") as f:
    image = f.read()

header_offset = APP_HEADER_ADDR - BOOT_START
app_offset = APP_START_ADDR - BOOT_START

if len(image) < header_offset + 20:
    raise SystemExit(f"{bin_path} is too small to contain the application header")

header = image[header_offset:header_offset + 20]
_, magic_number, app_version, app_size, app_crc = struct.unpack_from("<5I", header)

print(f"file: {bin_path}")
print(f"app_size from header: {app_size}")
print(f"stored app_crc: 0x{app_crc:08X}")

if app_size == 0xFFFFFFFF:
    app_size = 1368

if app_size <= 0:
    raise SystemExit("app_size is invalid")

max_size = len(image) - app_offset
if app_size > max_size:
    app_size = max_size

app_data = image[app_offset:app_offset + app_size]

# Reproduce exactly the C implementation from crc.c
crc = 0xFFFFFFFF
for b in app_data:
    crc ^= b
    for _ in range(8):
        if crc & 1:
            crc = (crc >> 1) ^ 0xEDB88320
        else:
            crc >>= 1

calc_crc = (~crc) & 0xFFFFFFFF

print(f"calc_crc: 0x{calc_crc:08X}")
print(f"match: {calc_crc == app_crc}")
