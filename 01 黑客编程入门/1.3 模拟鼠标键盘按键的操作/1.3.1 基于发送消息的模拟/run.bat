@echo off

cmake .
msbuild refresh.sln -m
debug\refresh