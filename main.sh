#!/bin/bash

# Set the build folder name and executable name
BUILD_FOLDER="build"
EXECUTABLE_NAME="Labs_System"

# 0. Informing the user that the lab is compiling
echo "Compiling all files..."

# 1. Create build folder or delete its contents if it exists
if [ -d "$BUILD_FOLDER" ]; then
    echo "Deleting contents of $BUILD_FOLDER..."
    rm -rf "$BUILD_FOLDER"/*
else
    echo "Creating $BUILD_FOLDER folder..."
    mkdir "$BUILD_FOLDER"
fi

# 2. Compiling main.cpp and every cpp file found by find into the build folder
gcc main.c functions.c -o "$BUILD_FOLDER/$EXECUTABLE_NAME" -Wall -Wextra

# 3. Checking if compilation worked.
if [ $? -eq 0 ]; then
    # 4. Launching the object file if everything worked.
    "./$BUILD_FOLDER/$EXECUTABLE_NAME"
    # read -p "Type any key to exit."
else
    # 5. If the compilation failed, inform the user.
    read -p "Compilation failed. Type any key to exit."
    # read -n 1 -s
fi
