/***************************************************************************//**
@author Xu Wang
@cite : Stephen Brennan's main.c
		from https://brennan.io/2015/01/16/write-a-shell-in-c/
*******************************************************************************/
#define _POSIX_C_SOURCE 200112L
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

/*
Function Declarations for builtin shell commands:
*/
int kapish_cd(char **args);
int kapish_setenv(char **args);
int kapish_exit(char **args);
int kapish_unsetenv(char **args);	
/*
List of builtin commands, followed by their corresponding functions.
*/
char *builtin_cmd[] = {
	"cd",
	"setenv",
	"exit",
	"unsetenv"
};
int (*builtin_func[]) (char **) = {
	&kapish_cd,
	&kapish_setenv,
	&kapish_exit,
	&kapish_unsetenv
};
int kapish_num_builtins() {
	return sizeof(builtin_cmd) / sizeof(char *);
	}
/*
Builtin function implementations.
*/
int kapish_setenv(char** args){

	if(setenv(args[1],args[2],1)!=0){
		perror("-kaish");
		return EXIT_FAILURE;
	}
	return 1;
	
}

int kapish_unsetenv(char **args){
	
	if(unsetenv(args[1])!=0){
		perror("-kaish");
		return EXIT_FAILURE;
	}
	return 1;
}
/**
@brief Bultin command: change directory.
@param args List of args. args[0] is "cd". args[1] is the directory.
@return Always returns 1, to continue executing.
*/
int kapish_cd(char **args)
{
	if(args[1] == NULL){
		//home
		char path[512];
		strcpy(path, getenv("HOME"));
		//getenv("HOME");
		chdir(path);
		//chdir("$HOME");
	}	
	 else {
		if (chdir(args[1]) != 0) {
			perror("-kaish");
		}
	}
	return 1;
}

/**
@brief Builtin command: exit.
@param args List of args. Not examined.
@return Always returns 0, to terminate execution.
*/
int kapish_exit(char **args)
{
	return 0;
}

/**
@brief Execute shell built-in or launch program.
@param args Null terminated list of arguments.
@return 1 if the shell should continue running, 0 if it should terminate
*/
int kapish_execute(char **args)
{
	int i;
	if (args[0] == NULL) {
	// An empty command was entered.
	return 1;
	}
	for (i = 0; i < kapish_num_builtins(); i++) {
		if (strcmp(args[0], builtin_cmd[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}

	pid_t pid;
	int status;
	pid = fork();
	if (pid == 0) {
	// Child process
		signal(SIGINT,SIG_DFL);//reset signal: run Ctrl-C
		if (execvp(args[0], args) == -1) {
			perror("-kapish");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
	// Error forking
	perror("-kapish");
	} else {
	// Parent process
		do {
		waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

/**
@brief Read a line of input from stdin.
@return The line from stdin.
*/
char *kapish_read_line(void)
{
	int bufsize = 512;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;
	if (!buffer) {
		fprintf(stderr, "kapish: allocation error\n");
		exit(EXIT_FAILURE);
	}
	while (1) {
	// Read a character
		c = getchar();
		if (c == EOF) {
		exit(EXIT_SUCCESS);
		} else if (c == '\n') {
			buffer[position] = '\0';
			return buffer;
		} else {
			buffer[position] = c;
		}
		position++;
		// If we have exceeded the buffer, reallocate.
		if (position >= bufsize) {
			exit(EXIT_SUCCESS);
		}
	}
}
#define LSH_TOK_BUFSIZE 512
#define LSH_TOK_DELIM " \t\r\n\a"
/**
@brief Split a line into tokens (very naively).
@param line The line.
@return Null-terminated array of tokens.
*/
char **kapish_split_line(char *line)
{
	int bufsize = LSH_TOK_BUFSIZE;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token, **tokens_backup;
	if (!tokens) {
		fprintf(stderr, "-kapish: allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, LSH_TOK_DELIM);
	while (token != NULL) {
		tokens[position] = token;
		position++;
		if (position >= bufsize) {
			bufsize += LSH_TOK_BUFSIZE;
			tokens_backup = tokens;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				free(tokens_backup);
				fprintf(stderr, "-kapish: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, LSH_TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}
/**
@brief Loop getting input and executing it.
*/
void kapish_loop(void)
{
signal(SIGINT,SIG_IGN);//ignore Ctrl-C
	char *line;
	char **args;
	int status;
	do {
		printf("? ");
		line = kapish_read_line();
		args = kapish_split_line(line);
		status = kapish_execute(args);
		free(line);
		free(args);
		} while (status);
}
/**
@brief Main entry point.
@param argc Argument count.
@param argv Argument vector.
@return status code
*/
int main(int argc, char **argv)
{
//read .kapishrc and printf
	char *path_kapishrc = getenv("HOME");
	int str_len = strlen(path_kapishrc);

	char *node_path_kapishrc = (char *)malloc(str_len*sizeof(char));
	strcpy(node_path_kapishrc, path_kapishrc);

	strcat(node_path_kapishrc, "/.kapishrc");

	FILE *fp = fopen(node_path_kapishrc,"r");
	if(fp==NULL){
		perror("-kapish");
	}
	else{
		printf("? ");
		int c;
		//////////////
		char **args;
		int bufsize = 512;
		int position = 0;
		char *buffer = malloc(sizeof(char) * bufsize);
		if (!buffer) {
		fprintf(stderr, "kapish: allocation error\n");
		exit(EXIT_FAILURE);
	}
		///////////////////
		while(1){
			c=fgetc(fp);
			if(feof(fp)){
				printf("\n");
				break;
			}
			else if(c=='\n'){
				printf("\n");
				buffer[position] = '\0';
				
				args = kapish_split_line(buffer);
				kapish_execute(args);
		
				free(buffer);
				free(args);
				char *buffer = malloc(sizeof(char) * bufsize);
				if (!buffer) {
					fprintf(stderr, "kapish: allocation error\n");
					exit(EXIT_FAILURE);
				}
				position = -1;
				//
				printf("? ");
				
			}
			else{
				printf("%c",c);
				buffer[position] = c;
			}
			position++;
		}
		fclose(fp);
	}
	free(node_path_kapishrc);
	
	// Load config files, if any.
	// Run command loop.
	kapish_loop();
	// Perform any shutdown/cleanup.
	return EXIT_SUCCESS;
}

