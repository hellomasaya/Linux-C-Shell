# Shell
## OS Assignment 2
### Harshita Sharma (20171099)

**To run the shell, enter the following commands:**
	1. make
	2. ./adda

*Tested and runs on Mac.*

**MODULES:**

	1. run
	This contains the infinite loop for the shell to run.
	2. readandsplit
	This consists of the read function used continuously by run and tokenizes the input.
	3. check
	checks wether process is background or not.
	4. builtin
	Implements built in commands cd, echo, pwd and calls ls function.
	5. ls
	This implements ls command along with the flags -a and -l.
	6. pinfo
	Implements pinfo command.
	7. notbuiltin
	Implements regular shell functions using exec.
	8. displayprompt
	Displays the prompt

**SPECIFICATIONS:**

    # Specification 1: Display requirement
    When code is executed in shell, a shell prompt similar to the following appears: <username@system_name:curr_dir>
    # Specification 2: Built-in Commands : cd, echo, pwd
    # Specification 3: ls command with -l -a -la/-al flags
    # Specification 4: System commands with and without arguments(foreground and background)
    # Specification 5: pinfo command
    # Specification 6: Finished Background Processes

