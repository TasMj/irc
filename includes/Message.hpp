/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:30:54 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/14 19:31:50 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/******************************************************************************/
/*                                 Includes                                   */
/******************************************************************************/
#include <string>
#include <deque>
#include <stdexcept>
#include <iostream>
#include "Color.hpp"
#include "Utils.hpp"

/******************************************************************************/
/*                               Structures                                   */
/******************************************************************************/
typedef struct s_prefix {
    std::string nickname;
    bool        has_user;
    std::string user;
    bool        has_host;
    std::string host;
}   t_prefix;

typedef struct s_message {
	std::string				raw;
    bool                    has_prefix;
    t_prefix                prefix;;
    std::string             command;
    std::deque<std::string> params;
    bool                    has_last_params;
    std::string             last_params;
}   t_message;

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/
t_message*      parse_message(std::string& input);
std::ostream&   operator<<(std::ostream& os, t_message& msg);
