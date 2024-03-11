/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboissen <bboissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:31:06 by bboissen          #+#    #+#             */
/*   Updated: 2024/03/11 13:48:21 by bboissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

// cc -o chdir src/chdir.c

int main(void)
{
	char *pwd;
	
	pwd = getcwd(NULL, 0);
	printf("pwd before chdir: %s\n", pwd);
	chdir("..");
	pwd = getcwd(NULL, 0);
	printf("pwd after chdir: %s\n", pwd);
	return (0);
}