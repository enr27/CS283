#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dshlib.h"

/*
 *  build_cmd_list
 *    cmd_line:     the command line from the user
 *    clist *:      pointer to clist structure to be populated
 *
 *  This function builds the command_list_t structure passed by the caller
 *  It does this by first splitting the cmd_line into commands by spltting
 *  the string based on any pipe characters '|'.  It then traverses each
 *  command.  For each command (a substring of cmd_line), it then parses
 *  that command by taking the first token as the executable name, and
 *  then the remaining tokens as the arguments.
 *
 *  NOTE your implementation should be able to handle properly removing
 *  leading and trailing spaces!
 *
 *  errors returned:
 *
 *    OK:                      No Error
 *    ERR_TOO_MANY_COMMANDS:   There is a limit of CMD_MAX (see dshlib.h)
 *                             commands.
 *    ERR_CMD_OR_ARGS_TOO_BIG: One of the commands provided by the user
 *                             was larger than allowed, either the
 *                             executable name, or the arg string.
 *
 *  Standard Library Functions You Might Want To Consider Using
 *      memset(), strcmp(), strcpy(), strtok(), strlen(), strchr()
 */
void trim(char *str) {
    char *start = str;
    while (isspace((unsigned char) *start)) {
        start++;
    }

    if (*start == '\0') {
        *str = '\0';
        return;
    }

    char *end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char) *end)) {
        end--;
    }

    *(end + 1) = '\0';

    if (start != str) {
        memmove(str, start, end - start + 2);
    }
}

int build_cmd_list(char *cmd_line, command_list_t *clist)
{
    if (cmd_line == NULL || clist == NULL) {
        return WARN_NO_CMDS;
    }

    trim(cmd_line);
    if (*cmd_line == '\0') {
        return WARN_NO_CMDS;
    }

    clist->num = 0;
    char*saveptr1;
    char*cmd_str = strtok_r(cmd_line, PIPE_STRING, &saveptr1);
    while (cmd_str != NULL) {
        trim(cmd_str);
        if (*cmd_str == '\0') {
            cmd_str = strtok_r(NULL, PIPE_STRING, &saveptr1);
            continue;
        }

        if (clist->num >= CMD_MAX) {
            return ERR_TOO_MANY_COMMANDS;
        }

        char *saveptr2;
        char *cmd_name = strtok_r(cmd_str, " ", &saveptr2);
        if (cmd_name == NULL) {
            cmd_str = strtok_r(NULL, PIPE_STRING, &saveptr1);
            continue;
        }

        if (strlen(cmd_name) >= EXE_MAX) {
            return ERR_CMD_OR_ARGS_TOO_BIG;
        }

        strcpy(clist->commands[clist->num].exe, cmd_name);

        clist->commands[clist->num].args[0] = '\0';
        char args_buffer[ARG_MAX] = {0};
        int first_arg = 1;

        char *cmd_arg;
        while ((cmd_arg = strtok_r(NULL, " ", &saveptr2)) != NULL) {
            if (!first_arg) {
                strcat(args_buffer, " ");
            }
            first_arg = 0;
            strcat(args_buffer, cmd_arg);

            if (strlen(args_buffer) >= ARG_MAX) {
                return ERR_CMD_OR_ARGS_TOO_BIG;
            }
        }

        strcpy(clist->commands[clist->num].args, args_buffer);
        clist->num++;
        cmd_str = strtok_r(NULL, PIPE_STRING, &saveptr1);
    }

    if (clist->num == 0) {
        return WARN_NO_CMDS;
    } else {
        return OK;
    }
}