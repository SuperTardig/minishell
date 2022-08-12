/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:40:39 by bperron           #+#    #+#             */
/*   Updated: 2022/08/12 10:52:52 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h> //de readline (a verifier)
# include <readline/history.h> //de readline (a verifier)
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "../libft/libft.h"

//signal.c

void	signal_handling(void);
void	sighandler(int signum, siginfo_t *s_info, void *content);
void	sighandlerc(int signum, siginfo_t *s_info, void *content);

//utils.c

void	cmd_prompt(void);

#endif
