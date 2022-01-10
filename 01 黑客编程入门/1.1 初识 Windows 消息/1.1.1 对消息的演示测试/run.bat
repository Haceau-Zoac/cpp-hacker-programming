@echo off

cmake .
msbuild notepad.sln -m
debug\notepad