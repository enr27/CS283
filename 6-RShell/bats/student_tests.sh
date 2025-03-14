#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

@test "Example: check ls runs without errors" {
    run ./dsh <<EOF                
ls
EOF

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Check pwd runs without errors" {
    run ./dsh <<EOF                
pwd
EOF
    [ "$status" -eq 0 ]
}

@test "Check echo runs without errors" {
    run ./dsh <<EOF                
echo "Hello World!"
EOF
    [ "$status" -eq 0 ]
}

@test "Handle empty commands" {
    run ./dsh <<EOF

EOF
    [[ "$output" == *"warning: no commands provided"* ]]
}

@test "Handle invalid commands" {
    run ./dsh <<EOF                
invalidcommand
EOF
    [ "$status" -eq 0 ]
    [[ "$output" =~ "execution failed: No such file or directory" ]]
}

@test "One pipe" {
    run ./dsh <<EOF                
ls | grep ".c"
EOF
    [ "$status" -eq 0 ]
    [[ "$output" == *".c"* ]]
}

@test "Two pipes" {
    run ./dsh <<EOF                
ls | grep ".c" | wc -l
EOF
    [ "$status" -eq 0 ]
}

@test "Exit command terminates shell" {
    run ./dsh <<EOF                
exit
EOF
    [ "$status" -eq 0 ]
}

@test "cd into an existing directory" {
    mkdir -p testdir
    run ./dsh <<EOF
cd testdir
pwd
EOF

    [ "$status" -eq 0 ]
    [[ "$output" =~ "$PWD/testdir" ]]  
    rmdir testdir  
}

@test "cd with no arguments (should not change directory)" {
    current_dir=$(pwd)
    run ./dsh <<EOF
cd
pwd
EOF
    [ "$status" -eq 0 ]
    [[ "$output" =~ "$current_dir" ]]
}

@test "cd into a non-existent directory" {
    run ./dsh <<EOF
cd /this/does/not/exist
EOF
    [ "$status" -eq 0 ]  
    [[ "$output" =~ "cd failed: No such file or directory" ]]
}
