@echo off
set BAT_BASE_PATH=%~dp0
set PRJ_BASE_PATH=%BAT_BASE_PATH%
set BIN_PATH=%PRJ_BASE_PATH%\bin\
set SRC_PATH=%PRJ_BASE_PATH%\src\
set INC_PATH=%PRJ_BASE_PATH%\include\

md %BIN_PATH%

clang.exe -o %BIN_PATH%\set_test.exe %SRC_PATH%\Sets\sets.c %SRC_PATH%\SinglyLinkedList\linkedlist.c %SRC_PATH%\Sets\test_sets.c -I %INC_PATH%

echo Set build completed!