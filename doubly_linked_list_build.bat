@echo off
set BAT_BASE_PATH=%~dp0
set PRJ_BASE_PATH=%BAT_BASE_PATH%
set BIN_PATH=%PRJ_BASE_PATH%\bin\
set SRC_PATH=%PRJ_BASE_PATH%\src\
set INC_PATH=%PRJ_BASE_PATH%\include\

md %BIN_PATH%

clang.exe -o %BIN_PATH%\doubly_linked_list_test.exe %SRC_PATH%\DoublyLinkedList\doublylinkedlist.c %SRC_PATH%\DoublyLinkedList\test_doubly.c -I %INC_PATH%

echo DoublyLinkedList build completed!