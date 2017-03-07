#!/bin/bash

dirname=$(dirname "${BASH_SOURCE[0]}")
dirname=$(cd "$dirname" && pwd)

g++ "${dirname}/../source/html2cpp.cpp" -o "${dirname}/../build/html2cpp"
