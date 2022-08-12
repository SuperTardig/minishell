/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 09:09:52 by bperron           #+#    #+#             */
/*   Updated: 2022/08/12 10:41:54 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//sert a quitter le shell avec un exit code donner par le user ou celui de la dernier commande utiliser
//va falloir mettre les bons parametre
void	exit(void)
{
	int	status;

	//if () regarder si un argument a ete donner
	//	status = arg;
	//else 
	//	status = last_status;
	//free_all(); va falloir la creer
	//exit (status);
}

//sert a imprimer quelque chose
//va falloir mettre les bons parametre
void	echo(void)
{
	int	i;
	int	flags;

	i = 0;
	flags = 0;
	//while (i <= 4)
	//	i++;
	//if (str[i] == '-') check for flags
/* 	{
		flags = 1;
		i += 3;
	} on pourrait probablement mettre cette partie la dans le parsing en meme temps de toute checker*/
	/*if (flags == 0)
		printf ("%s\n", argument);
	else
		printf("%s", argument);
	soit on fait ca de meme ou dans le parsing on rajoute un \n mais je */
}

//sert a print le working directory
//va falloir mettre les parametre
void	pwd(void)
{
	//if (argument == 1)
		//printf("%s\n", arg);
	//else
	//	printf("pwd: too many arguments");
}
