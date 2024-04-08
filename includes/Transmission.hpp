/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Transmission.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:32:42 by tas               #+#    #+#             */
/*   Updated: 2024/04/08 13:06:56 by tas              ###   ########.fr       */
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
    
        int                  _fdEmitter;
        std::vector<int>     _fdDest;
        std::string          _nameEmitter;

        std::string          _msg;
    
    public:
        Transmission();
        ~Transmission();

        void            setMsg(std::string msg);
        void            setFdEmitter(int fd);
        void            addNewFdDest(int newFd);
        int             getFdEmitter();
        void            setFdDest(std::vector<int> fdDest);
std::vector<int>        getFdDest();
		

        std::string     getMsg();
};
    

