import zlib

APP_BIN_PATH = "./application.bin"

with open(APP_BIN_PATH, "rb") as f:
    app_data = f.read()

crc32 = zlib.crc32(app_data) & 0xFFFFFFFF

print(f"CRC32 of {APP_BIN_PATH}: {crc32:08X}")
print(f"size of {APP_BIN_PATH}: {len(app_data)} bytes")