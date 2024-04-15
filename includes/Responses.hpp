/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responses.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:53:37 by tmalless          #+#    #+#             */
/*   Updated: 2024/04/16 00:00:24 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <sstream>
# include "./Server.hpp"
# include "./Client.hpp"

# define WELCOME "                                                                     \n\
                                                                     \n\
                   Téma la taille du welcome !                       \n\
                                                                     \n\
██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗    ██╗\n\
██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝    ██║\n\
██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗      ██║\n\
██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝      ╚═╝\n\
╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗    ██╗\n\
 ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝    ╚═╝\n\
                                                                     \n\
                                par tmejri, aclement et tmalless     \n\
                                                                     \n\
																	 \r\n"

# define PREFIXE "localhost"
# define SERVER "HYPER MEGA GIGA SERVER 3000"
# define VERSION "Version 0.0000001"
# define CREATION "March 12 1989"

class Client;

/* ************************************************************************** */
// WELCOME
/* ************************************************************************** */

std::string	RPL_WELCOME(Client *cli); //001
std::string	RPL_YOURHOST(); //002
std::string	RPL_CREATED();//003
std::string	RPL_MYINFO();//004

/* ************************************************************************** */
// NICK
/* ************************************************************************** */

std::string	ERR_NICKNAMEINUSE(std::string oldNick, std::string newNick, std::string reason);

/* ************************************************************************** */
// JOIN
/* ************************************************************************** */

std::string	RPL_JOIN(Client *cli, std::string chan);
std::string	ERR_CHANWRONGPASS(std::string nick, std::string chan, std::string reason);
std::string	ERR_CHANNELISFULL(std::string nick, std::string chan, std::string reason);
std::string	ERR_CHANNELUSERNOTINVIT(std::string nick, std::string chan, std::string reason);

/* ************************************************************************** */
// INVITE
/* ************************************************************************** */

std::string	ERR_NEEDMOREPARAMS(std::string nick, std::string cmd, std::string reason);
std::string	RPL_INVITE(std::string sender, std::string receiver, std::string chan, std::string reason);

/* ************************************************************************** */
// MODE
/* ************************************************************************** */

std::string	ERR_NEEDMOREPARAMS(std::string nick, std::string cmd, std::string reason);
std::string	RPL_MODE(std::string nick, std::string chan, std::string sign, std::string flag, std::string reason);
std::string	ERR_CHANPRIVSNEEDED(std::string nick, std::string chan);

/* ************************************************************************** */
// NICK
/* ************************************************************************** */

std::string	RPL_NICK(Client *cli, std::string newNick);