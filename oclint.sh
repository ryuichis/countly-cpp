#! /bin/sh -e

rm -rf oclint_build
mkdir oclint_build
cd oclint_build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
cd ..
cp oclint_build/compile_commands.json .
oclint-json-compilation-database
