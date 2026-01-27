@echo off
setlocal enabledelayedexpansion

echo Getting all submodules...
git submodule update --init --recursive --remote

echo DONE!
pause