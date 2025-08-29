#!/bin/bash

# Path to your minishell executable
MINISHELL=./minishell

# Colors for output
GREEN="\e[32m"
RED="\e[31m"
NC="\e[0m"

# Test cases: ("command" expected_exit_code)
tests=(
  "true 0"
  "false 1"
  "exit 42 42"
  "exit 256 0"
  "exit -257 255" # Overflow test fails ❌
  "exit -1 255" 
  "exit a 255"
  "nonexistent_command 127"
)

# Temp file to capture shell output
TMP_OUTPUT=$(mktemp)

pass_count=0
fail_count=0

echo "Running minishell exit code tests..."

for test_case in "${tests[@]}"; do
  cmd=$(echo "$test_case" | awk '{$NF=""; print $0}' | sed 's/ *$//')
  expected=$(echo "$test_case" | awk '{print $NF}')

  # Run minishell with the command
  echo "$cmd" | $MINISHELL > /dev/null 2>&1
  actual=$?

  if [[ "$actual" == "$expected" ]]; then
    echo -e "[${GREEN}PASS${NC}] '$cmd' => Exit code: $actual"
    ((pass_count++))
  else
    echo -e "[${RED}FAIL${NC}] '$cmd' => Got: $actual, Expected: $expected"
    ((fail_count++))
  fi
done

echo
echo "Total: $((pass_count + fail_count)), Passed: $pass_count, Failed: $fail_count"

# Cleanup
rm -f "$TMP_OUTPUT"
