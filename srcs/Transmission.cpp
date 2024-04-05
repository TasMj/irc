/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Transmission.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:31:30 by tas               #+#    #+#             */
/*   Updated: 2024/04/05 11:39:56 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Transmission.hpp"

Transmission::Transmission()
{
    
}
Transmission::~Transmission()
{
    
}

int Transmission::getFlagPoll()
{
    return (this->flagPoll);
}

void Transmission::setPollStatus()
{
    if (Transmission::getFlagPoll() == 0)
        pollStatus = POLLIN;
    else if (Transmission::getFlagPoll() == 1)
        pollStatus = POLLOUT;
    else
        pollStatus = POLLERR;
}

unsigned int Transmission::getPollStatus()
{
    return (this->pollStatus);
}

void    Transmission::setMsg(std::string msg)
{
    this->msg = msg;
}

void    Transmission::setFdHost(int fd)
{
    this->fd_host = fd;
}

int     Transmission::getFdHost()
{
    return (this->fd_host);
}

std::string     Transmission::getMsg()
{
    return (this->msg);
}
