source ./AutoClickerVenv/Scripts/Activate
python ./main.py

pyinstaller --onefile --windowed --add-data "Resources;Resources" main.py