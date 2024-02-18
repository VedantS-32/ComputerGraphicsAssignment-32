@echo
python Setup.py
cd ../vendor/assimp
cmake CMakeLists.txt
cmake --build . --config Release
PAUSE