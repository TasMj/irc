/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Transmission.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:31:30 by tas               #+#    #+#             */
/*   Updated: 2024/04/07 15:00:15 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Transmission.hpp"

Transmission::Transmission()
{
    
}

Transmission::~Transmission()
{
    
}

void    Transmission::setMsg(std::string msg)
{
    this->_msg = msg;
}

void    Transmission::setFdEmitter(int fd)
{
    this->_fdEmitter = fd;
}

std::string     Transmission::getMsg()
{
    return (this->_msg);
}

void    Transmission::addNewFdDest(int newFd)
{   
	std::cout << "newFD : " << newFd << std::endl;
    _fdDest.push_back(newFd);
}

void    Transmission::setFdDest(std::vector<int> fdDest)
{
    this->_fdDest = fdDest;
}

std::vector<int> Transmission::getFdDest()
{
    return (this->_fdDest);
}

int    Transmission::getFdEmitter()
{
    return (this->_fdEmitter);
}