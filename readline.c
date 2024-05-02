#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t sigint_received = 0;

int sigint_handler(int count, int key)
{
	sigint_received = 1;
	rl_free_line_state();
	rl_cleanup_after_signal();
	return (0);
}

int main()
{
	char *line;
	char *prompt = "heredoc > ";

	rl_catch_signals = 1;
	rl_set_signals();
	rl_bind_keyseq("\\C-c", sigint_handler);

	while (1)
	{
		line = readline(prompt);
		if (sigint_received)
		{
			printf("\nExiting heredoc due to SIGINT\n");
			sigint_received = 0;
			break;
		}
		if (line && *line)
			add_history(line);
		free(line);
	}

	return (0);
}