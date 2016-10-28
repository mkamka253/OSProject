/*
 * main.c
 *
 *  Created on: Dec 5, 2015
 *      Author: kmorris
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 64
#define DELIMETER " \t\r\n\a"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void runLoop();
char* readInput();
char** parseInput(char* line);
int executeCommand(char** cmd);

#define NUM_BUILT_INS 5

int main(int argc, char* argv[])
{
	runLoop();

	return 0;
}
void runLoop()
{
	int status;
	status = 1;

	char* line;
	char** args;

	do
	{
		//1. prompt
		printf("> ");

		//2. read
		line = readInput();

		//3. parse
		args = parseInput(line);

		//4. execute
		status = executeGamesCommand(args);

		//cleanup
		free(line);
		free(args);

	} while(status == 1);
}

int executeGamesCommand(char** cmd)
{
	int i;

	if(cmd[0] == NULL)
		return 1;

	//checks if a built in command is entered
	for(i = 0; i < NUM_BUILT_INS; i++)
	{
		if(strcmp(cmd[0], builtInStrings[i]) == 0)
			return (*builtInFunctions[i])(cmd);
	}

	return executeCommand(cmd);
}

int executeCommand(char** cmd)
{
	//Executes the basic shell commands
	pid_t x;
	int status = 1;

	x = fork();

	if(x == -1)
	{
		perror("fork error\n");
	}
	else if(x == 0)
	{
		//Process to execute commands

		status = execvp(cmd[0], cmd);
		_exit(0);
	}
	else if(x > 0)
	{
		//Code for the parent would go here if needed

	}

	pid_t y;
	for(;;)
	{
		//will wait for all children created.
		y = wait(NULL);
		if(y == -1)
		{
			int num = errno;
			if(num == ECHILD)
			{
				break;
				//should do nothing but allow the program to continue
			}
			else if(num == EINTR)
			{
				printf("The process was interrupted");
				break;
			}
		}
	}
	return status;
}

char* readInput()
{
	//Reads the input from the console
	char* line = NULL;
	size_t bufferSize = 0;
	getline(&line, &bufferSize, stdin);
	return line;
}
char** parseInput(char* input)
{
	//Parses the input to be able to execute commands

	int bufferSize = TOKEN_BUFFER_SIZE;
	int position = 0;
	char** tokens = malloc(bufferSize * sizeof(char*));
	char* token;

	if(!tokens)
	{
		perror("malloc error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, DELIMETER);
	while(token != NULL)
	{
		tokens[position] = token;
		position++;

		if(position >= bufferSize)
		{
			bufferSize += TOKEN_BUFFER_SIZE;
			tokens = realloc(tokens, bufferSize * sizeof(char*));
			if(!tokens)
			{
				perror("realloc error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, DELIMETER);
	}
	tokens[position] = NULL;
	return tokens;
}
