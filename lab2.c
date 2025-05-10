// Include external headers
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

// Main Function
int main(int argc, char *argv[]) {

	// Create pid_t to store the process ID of the current process
	pid_t process_id;

	// The size of commands used
	const int command_size = 3;

	// List of commands to be run and their arguments
	char *command[][3] = {
		{"ls", "-l", NULL},
		{"mkdir", "someDir", NULL},
		{"touch", "someFile", NULL},
		{"date", NULL, NULL},
		{"history", "1", NULL},
		{"echo", "Hello World", NULL},
		{"time", "echo", "Time Echo"},
		{"echo", "Hello Matt", NULL},
		{"echo", "goodbye", NULL},
		{"ps", NULL, NULL}
	};

	// Command amount to iterate through
	int command_amount = sizeof(command) / sizeof(command[0]);

	// Iterates through the list of commands 
	for (int i = 0; i < command_amount; i++) {
		
		// Gets the return value of fork attempt
		// <0 = failed, 0 = success, >0 for parent
		process_id = fork();

		if (process_id == 0) {

			// If the command executes, print the process ID and the command executing
			printf("[PID %d] executing: %s.\n", getpid(), command[i][0]);
			
			// Execvp replaces the running process with a new one
			// Input command name and arguments
			execvp(command[i][0],command[i]);

			// Only run the following if execvp fails.
			perror("Command Failed.");
			exit(EXIT_FAILURE);

		} else if (process_id < 0) {

			// If the fork creation process fails, exit the program.
			printf("Fork creation failed.\n");
			exit(EXIT_FAILURE);

		}

	}
	
	// Creates a variable for wait() call to use
	// waits for any child processes attached to this
	// process to finish, and then runs the code in the while loop
	// and then waits for the next child process to finish.
	int exit_status;
	// Parent process waits for child processes to finish
	while((process_id = wait(&exit_status)) > 0) {
		// Prints out the process id once finished
		printf("[PID %d] finished.\n", process_id);
	}

	// Exits the program on success.
	return EXIT_SUCCESS;

}