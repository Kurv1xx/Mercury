@echo off
echo Cleaning build directory...

if exist build (
    rmdir /s /q build
    echo Build cleaned.
) else (
    echo Nothing to clean.
)

pause
