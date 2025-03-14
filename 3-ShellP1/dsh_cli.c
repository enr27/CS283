#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dshlib.h"

/*
 * Implement your main function by building a loop that prompts the
 * user for input.  Use the SH_PROMPT constant from dshlib.h and then
 * use fgets to accept user input.  Since we want fgets to also handle
 * end of file so we can run this headless for testing we need to check
 * the return code of fgets.  I have provided an example below of how
 * to do this assuming you are storing user input inside of the cmd_buff
 * variable.
 *
 *      while(1){
 *        printf("%s", SH_PROMPT);
 *        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
 *           printf("\n");
 *           break;
 *        }
 *        //remove the trailing \n from cmd_buff
 *        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
 *
 *        //IMPLEMENT THE REST OF THE REQUIREMENTS
 *      }
 *
 *   Also, use the constants in the dshlib.h in this code.
 *      SH_CMD_MAX              maximum buffer size for user input
 *      EXIT_CMD                constant that terminates the dsh program
 *      SH_PROMPT               the shell prompt
 *      OK                      the command was parsed properly
 *      WARN_NO_CMDS            the user command was empty
 *      ERR_TOO_MANY_COMMANDS   too many pipes used
 *
 *   Expected output:
 *
 *      CMD_OK_HEADER      if the command parses properly. You will
 *                         follow this by the command details
 *
 *      CMD_WARN_NO_CMD    if the user entered a blank command
 *      CMD_ERR_PIPE_LIMIT if the user entered too many commands using
 *                         the pipe feature, e.g., cmd1 | cmd2 | ... |
 *
 *  See the provided test cases for output expectations.
 */
int main()
{
    char cmd_buffer[SH_CMD_MAX];
    command_list_t cmd_list;

    while (1) {
        printf("%s", SH_PROMPT);

        if (fgets(cmd_buffer, SH_CMD_MAX, stdin) == NULL) {
            printf("\n");
            break;
        }

        cmd_buffer[strcspn(cmd_buffer, "\n")] = '\0';

        if (strlen(cmd_buffer) == 0) {
            printf("%s", CMD_WARN_NO_CMD);
            continue;
        }

        if (strcmp(cmd_buffer, EXIT_CMD) == 0) {
            exit(0);
        }

        int parse_result = build_cmd_list(cmd_buffer, &cmd_list);

        if (parse_result == OK) {
            printf(CMD_OK_HEADER, cmd_list.num);
            for (int i = 0; i < cmd_list.num; i++) {
                if (strlen(cmd_list.commands[i].args) > 0) {
                    printf("<%d> %s [%s]\n", i + 1, cmd_list.commands[i].exe, cmd_list.commands[i].args);
                } else {
                    printf("<%d> %s\n", i + 1, cmd_list.commands[i].exe);
                }
            }
        }

        else if (parse_result == WARN_NO_CMDS) {
            printf("%s", CMD_WARN_NO_CMD);
        }

        else if (parse_result == ERR_TOO_MANY_COMMANDS) {
            printf(CMD_ERR_PIPE_LIMIT, CMD_MAX);
        }
    }

    return 0;
}