if exist "_cmake" rmdir /s /q _cmake
mkdir _cmake
cd _cmake
cmake .. -G "Visual Studio 16 2019"
cd ..
pause