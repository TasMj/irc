/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Transmission.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:32:42 by tas               #+#    #+#             */
/*   Updated: 2024/04/07 12:34:09 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/******************************************************************************/
/*                                 Includes                                   */
/******************************************************************************/

# include "Server.hpp"

/******************************************************************************/
/*                                  Class                                     */
/******************************************************************************/

class Transmission
{
    private:
        /* data */
        int                  _fdEmitter;
        std::vector<int>     _fdDest;
        std::string          _nameEmitter;

        std::string          _msg;
    
    public:
        Transmission(/* args */);
        ~Transmission();

        void            setMsg(std::string msg);
        void            setFdEmitter(int fd);
        void            addNewFdDest(int newFd);
        int             getFdEmitter();
        void            setFdDest(std::vector<int> fdDest);
std::vector<int>        getFdDest();
		

        std::string     getMsg();
};
    

