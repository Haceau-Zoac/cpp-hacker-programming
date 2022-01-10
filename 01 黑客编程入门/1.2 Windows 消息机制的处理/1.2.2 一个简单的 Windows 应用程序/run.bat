@echo off

cmake .
msbuild app.sln -m
debug\app