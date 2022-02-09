#!/bin/bash

#RED="\e[41m"
#GREEN="\e[42m"
#BOLD="\e[1m"
#DEFAULT="\e[0m"

FILE=$1
failed=0

if [ ! -e "$FILE" ]; then
    echo -e "Given file does not exist - $FILE"
    exit 1
fi

function check()
{
    if [ "$1" != 0 ]; then
        echo -e ❌ $RED "FAILED ON" "$@" $DEFAULT
        ((failed+=1))
    else
        echo -e ✅ $GREEN "FOUND" $DEFAULT
    fi
}

function negative_check()
{
    if [ "$1" == 0 ]; then
        echo -e ❌ $RED "FAILED ON" "$@" $DEFAULT
        ((failed+=1))
    else
        echo -e ✅ $GREEN "NOT FOUND" $DEFAULT
    fi
}

function positive_lookup()
{
    echo -e "---"
    echo -e 🔍 $BOLD "CHECKING: $1" $DEFAULT
    pcregrep -M "$2" "$FILE"
    check $? $1
}

function negative_lookup()
{
    echo -e "---"
    echo -e 🔍 $BOLD "CHECKING: $1" $DEFAULT
    pcregrep -M "$2" "$FILE"
    negative_check $? $1
}

function does_file_exist()
{
    echo -e "---"
    echo -e 🔍 $BOLD "CHECKING: $1" $DEFAULT
    if [[ -f "$1" ]]; then
        echo -e ✅ $GREEN "FILE EXISTS" $DEFAULT
    else
        echo -e ❌ $RED "FILE DOES NOT EXIST" $DEFAULT
        ((failed+=1))
    fi
}

echo -e $BOLD "Performing checks on $FILE" $DEFAULT

# Part 1
positive_lookup "\${PROJECT_NAME}" "[$]\{PROJECT_NAME\}"
positive_lookup "source files list in the variable named with UPPERCASE_WITH_UNDERSCORE convention" "set\([A-Z_]*\s+(.*cpp\s+)+\)"
positive_lookup "static library with source files list or cpp files mentioned directly" "add_library\(.*STATIC.*(\s.*cpp)+\)|add_library\(.*STATIC\s+([\$\{A-Z_\}]*)\)"
negative_lookup "static library should not have main.cpp" "add_library\(.*STATIC(\s.*\.cpp)*(\s+main\.cpp)+\)"
positive_lookup "executable with main.cpp" "add_executable\([$]{PROJECT_NAME}\s+(.*)?main\.cpp\)"
positive_lookup "executable should be linked with the library" "target_link_libraries\([\$]\{PROJECT_NAME\}\s.+\)"
does_file_exist ".github/workflows/main.yml"

# Part 2
positive_lookup "binary with tests exist" "add_executable\([\$]\{PROJECT_NAME\}-ut(\s+[[:word:]]+\.cpp)+\)|add_executable\([\$]\{PROJECT_NAME\}-ut\s+([\$\{A-Z_\}]*)\)"
positive_lookup "test binary added to ctest" "gtest_discover_tests|add_test\(NAME.*\s+COMMAND\s+[\$]\{PROJECT_NAME\}-ut\)"
positive_lookup "testing is enabled" "enable_testing\(\)"

echo -e "==="

if [ $failed == 0 ]; then
    echo -e 💚💚💚 $GREEN "ALL CHECKS PASSED" 💚💚💚 $DEFAULT
else
    echo -e ❗️❗️❗️ $RED $failed "CHECKS FAILED" ❗️❗️❗️ $DEFAULT
fi

exit $failed
