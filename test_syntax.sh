#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Minishell executable path (change this to your minishell path)
MINISHELL="./minishell"

# Test cases - all should produce syntax error
TEST_CASES=(
    "echo oi |"
    "| echo oi"
    "| |"
    "| $"
    "| >"
    ">"
    ">>"
    ">>>"
    "<"
    "<<"
    "echo hi <"
    "cat    <| ls"
    "echo hi | >"
    "echo hi | > >>"
    "echo hi | < |"
    "echo hi |   |"
)

# command not found test cases
# "echo hi |  \"|\""  ☑️ 


# Function to check for syntax error
check_syntax_error() 
{
    output=$(echo "$1" | $MINISHELL 2>&1)

    # Strip ANSI escape sequences (color codes)
    clean_output=$(echo "$output" | sed $'s/\x1b\\[[0-9;]*m//g')

    if [[ "$clean_output" == *"❌ error: Syntax Tokenizer"* ]]; then
        return 0
    else
        return 1
    fi
}

# Function to run tests
run_tests() {
    echo "Testing minishell syntax error detection..."
    echo "-------------------------------------------"
    
    pass_count=0
    fail_count=0
    
    for cmd in "${TEST_CASES[@]}"; do
        echo -n "Testing: '$cmd' - "
        
        if check_syntax_error "$cmd"; then
            echo -e "${GREEN}PASS${NC}"
            ((pass_count++))
        else
            echo -e "${RED}FAIL${NC}"
            echo "  Minishell output: '$output'"
            ((fail_count++))
        fi
    done
    
    echo "-------------------------------------------"
    echo "Results:"
    echo -e "${GREEN}PASSED: $pass_count${NC}"
    echo -e "${RED}FAILED: $fail_count${NC}"
    echo "-------------------------------------------"
    
    if [ $fail_count -eq 0 ]; then
        echo -e "${GREEN}All syntax error tests passed!${NC}"
    else
        echo -e "${RED}Some tests failed - check the output above${NC}"
    fi
}

# Run tests
run_tests