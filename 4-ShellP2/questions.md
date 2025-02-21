1. Can you think of why we use `fork/execvp` instead of just calling `execvp` directly? What value do you think the `fork` provides?

    > **Answer**: We use fork/execvp instead because execvp replaces the current program, so if we were to call execvp directly, the program would just disappear. Fork on the other hand creates a child process, which allows the parent to keep running and manage the new process.

2. What happens if the fork() system call fails? How does your implementation handle this scenario?

    > **Answer**: If the fork() system call fails, it returns -1. My implementation handles this by checking the return value of fork() and then prints an error message.  

3. How does execvp() find the command to execute? What system environment variable plays a role in this process?

    > **Answer**: It looks for the command in the directories listed in the PATH environment variable, and it goes through each directory in PATH until it finds the executable. 

4. What is the purpose of calling wait() in the parent process after forking? What would happen if we didn’t call it?

    > **Answer**: Calling wait() ensures that the parent process will wait for the child process to finish. If we didn't call it, this would lead to a zombie process, and resource leaks would occur. 

5. In the referenced demo code we used WEXITSTATUS(). What information does this provide, and why is it important?

    > **Answer**: WEXITSTATUS() extracts the exit status of a terminated child process. This is important because the parent process will be able to check if the child process completed successfully or if there was an error. 

6. Describe how your implementation of build_cmd_buff() handles quoted arguments. Why is this necessary?

    > **Answer**: My build_cmd_buff() recognizes quoted arguments as a single unit by preserving spaces within the quotes. This is necessary because it ensures that commands with spaces are correctly processed.  

7. What changes did you make to your parsing logic compared to the previous assignment? Were there any unexpected challenges in refactoring your old code?

    > **Answer**: I modified my logic to better handle quoted arguments, ensuring proper spacing and command parsing. I did not have unexpected challenges while refactoring my old code. 

8. For this quesiton, you need to do some research on Linux signals. You can use [this google search](https://www.google.com/search?q=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&oq=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&gs_lcrp=EgZjaHJvbWUyBggAEEUYOdIBBzc2MGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8) to get started.

- What is the purpose of signals in a Linux system, and how do they differ from other forms of interprocess communication (IPC)?

    > **Answer**: Signals in a Linux system are a basic form of interprocess communication used to notify a process about events. Signals differ from other forms of IPC since they are primarily used for simple notifcations and they can't transfer large amounts of data. 

- Find and describe three commonly used signals (e.g., SIGKILL, SIGTERM, SIGINT). What are their typical use cases?

    > **Answer**: SIGKILL is used to immediately terminate a process and can't be blocked or ignored, SIGTERM is used to politely ask a process to terminate but can be blocked and ignored, and SIGINT is used to interrupt a process but can be caught or ignored.

- What happens when a process receives SIGSTOP? Can it be caught or ignored like SIGINT? Why or why not?

    > **Answer**: When a process receives SIGSTOP, it is immediately paused, and it can't be caught or ignored like SIGINT because it's implemented to be an unconditional stop signal. 
