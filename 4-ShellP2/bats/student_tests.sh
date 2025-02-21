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

@test "Built-in: pwd runs without errors" {
    run ./dsh <<EOF                
pwd
EOF

    [ "$status" -eq 0 ]
    [ -n "$output" ]  
}

@test "Built-in: echo with quoted string" {
    run ./dsh <<EOF                
echo "hello    world"
EOF

    [ "$status" -eq 0 ]
    [[ "$output" =~ "hello    world" ]]  
}

@test "Built-in: echo without arguments" {
    run ./dsh <<EOF                
echo
EOF

    [ "$status" -eq 0 ]
}

@test "External: ls with arguments" {
    run ./dsh <<EOF                
ls -l
EOF

    [ "$status" -eq 0 ]
}

@test "Built-in: cd into an existing directory" {
    mkdir -p testdir
    run ./dsh <<EOF
cd testdir
pwd
EOF

    [ "$status" -eq 0 ]
    [[ "$output" =~ "$PWD/testdir" ]]  
    rmdir testdir  
}

@test "Built-in: cd with no arguments (should not change directory)" {
    current_dir=$(pwd)
    run ./dsh <<EOF
cd
pwd
EOF

    [ "$status" -eq 0 ]
    [[ "$output" =~ "$current_dir" ]]
}

@test "Built-in: cd into a non-existent directory" {
    run ./dsh <<EOF
cd /this/does/not/exist
EOF

    [ "$status" -eq 0 ]  
    [[ "$output" =~ "cd failed: No such file or directory" ]]
}

@test "Parsing: handling of an invalid command" {
    run ./dsh <<EOF                
invalidcommand
EOF

    [ "$status" -eq 0 ]
    [[ "$output" =~ "Execution failed: No such file or directory" ]]
}

@test "Built-in: exit command" {
    run ./dsh <<EOF
exit
EOF

    [ "$status" -eq 0 ]
}
