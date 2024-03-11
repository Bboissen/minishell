/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:26:06 by bboissen          #+#    #+#             */
/*   Updated: 2024/03/11 16:28:48 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <term.h>
#include <stdlib.h>

//cc -o clear src/clear.c -lreadline -ltermcap

int main(void)
{
    char *rl;
    char *pwd;
    char term_buffer[2048];
    char *clear_seq;
    char *term_type = getenv("TERM");

    if (tgetent(term_buffer, term_type) < 1) {
        fprintf(stderr, "Could not get terminal entry\n");
        return 1;
    }

    while (1)
    {
        rl = readline("Prompt > ");
        if (rl == NULL) {
            continue;
        }
        add_history(rl);
        if (rl[0] == 'c') {
            clear_seq = tgetstr("cl", NULL);
            if (clear_seq != NULL) {
                tputs(clear_seq, 1, putchar);
            } else {
                fprintf(stderr, "Could not get clear sequence\n");
            }
        }
        if (rl[0] == 'p') {
            pwd = getcwd(NULL, 0);
            printf("%s\n", pwd);
            free(pwd);
        }
        if (rl[0] == 'b') {
            break;
        }
        rl_on_new_line();
        free(rl);
    }
    return (0);
}