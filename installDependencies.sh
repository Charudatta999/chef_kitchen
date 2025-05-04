#!/bin/bash

# install_dependencies.sh
# Installs dependencies for C++ project compilation, testing, coverage, and call graph generation

set -e  # Exit on any error

echo "Updating package index..."
sudo apt-get update

echo "Installing core development tools..."
sudo apt-get install -y \
    g++ \
    libgtest-dev \
    libpthread-stubs0-dev \
    lcov \
    gcovr \
    graphviz \
    valgrind \
    kcachegrind \
    perl \
    wget

echo "Checking for egypt installation..."
if ! command -v egypt &> /dev/null; then
    echo "egypt not found, installing manually..."
    wget http://www.gson.org/egypt/download/egypt-1.11.tar.gz -O /tmp/egypt-1.11.tar.gz || {
        echo "Error: Failed to download egypt-1.11.tar.gz. Please check the URL or download manually from http://www.gson.org/egypt/"
        exit 1
    }
    tar -xzf /tmp/egypt-1.11.tar.gz -C /tmp
    cd /tmp/egypt-1.11
    perl Makefile.PL
    make
    sudo make install
    cd -
    rm -rf /tmp/egypt-1.11 /tmp/egypt-1.11.tar.gz
else
    echo "egypt is already installed."
fi

echo "Verifying installations..."
for cmd in g++ dot egypt valgrind kcachegrind lcov gcovr perl wget; do
    if command -v $cmd &> /dev/null; then
        echo "$cmd: Installed"
    else
        echo "$cmd: Not installed, please check manually"
        exit 1
    fi
done

# Verify Google Test
if [ -f /usr/src/gtest/lib/libgtest.a ] || [ -f /usr/lib/libgtest.a ]; then
    echo "Google Test: Installed"
else
    echo "Google Test: Not found, attempting to build..."
    sudo mkdir -p /usr/src/gtest/build
    cd /usr/src/gtest/build
    sudo cmake ..
    sudo make
    sudo cp lib/*.a /usr/lib/
    cd -
fi

echo "All dependencies installed successfully!"
echo "You can now run 'make' to build the project, 'make test' to run tests, 'make coverage' for coverage reports, and 'make callgraph' or 'make callgrind' for call graphs."