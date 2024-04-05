/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:05:45 by tmejri            #+#    #+#             */
/*   Updated: 2024/03/25 15:05:56 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

size_t FindInString(const std::string& chaine, const std::string& sousChaine)
{
    size_t position = chaine.find(sousChaine);
    return (position);
}
