1. Your shell forks multiple child processes when executing piped commands. How does your implementation ensure that all child processes complete before the shell continues accepting user input? What would happen if you forgot to call waitpid() on all child processes?

My implementation ensures that all child processes complete before the shell continues accepting user input by using waitpid() in a loop to wait for each child in the pipeline. If waitpid() is not called on all child processes, those child processes would turn into zombie processes, and this could cause resource leaks and unexpected behavior. 

2. The dup2() function is used to redirect input and output file descriptors. Explain why it is necessary to close unused pipe ends after calling dup2(). What could go wrong if you leave pipes open?

It's necessary to close unused pipe ends after calling dup2() to prevent resource leaks. If unused pipes remain open, the system may not detect when a process has finished, and this could cause processes to hang indefinitely. 

3. Your shell recognizes built-in commands (cd, exit, dragon). Unlike external commands, built-in commands do not require execvp(). Why is cd implemented as a built-in rather than an external command? What challenges would arise if cd were implemented as an external process?

Cd is implemented as a built-in rather than an external command because its purpose is to change the shell's working directory, which belongs to the parent process. If cd were implemented as an external process, it would run in a child process and any directory change wouldn't affect the parent shell. 

4. Currently, your shell supports a fixed number of piped commands (CMD_MAX). How would you modify your implementation to allow an arbitrary number of piped commands while still handling memory allocation efficiently? What trade-offs would you need to consider?

I would modify my implementation to dynamically allocate the pipe array depending on the number of commands by using malloc() and free(). Some trade-offs to consider would be added complexity in error handling and an increase in memory usage. 
