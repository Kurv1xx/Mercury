@echo off

if exist build (
    rmdir /s /q build
    echo INFO: Cleaned build directory
) else (
    echo INFO: Nothing to clean
)
