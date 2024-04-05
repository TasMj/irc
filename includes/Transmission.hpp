/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Transmission.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:32:42 by tas               #+#    #+#             */
/*   Updated: 2024/04/05 17:13:59 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSMISSION_HPP
# define TRANSMISSION_HPP

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
        int             fd_host;
        // int             fd_dest;
        std::string     msg;
        int             flagPoll;
        unsigned int    pollStatus;
    
    public:
        Transmission(/* args */);
        ~Transmission();

        int             getFlagPoll();
        void            setPollStatus();
        unsigned int    getPollStatus();
        void            setMsg(std::string msg);
        void            setFdHost(int fd);
        int             getFdHost();
        std::string     getMsg();
};
    

#endif
