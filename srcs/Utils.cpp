/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utiils.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:05:45 by tmejri            #+#    #+#             */
/*   Updated: 2024/04/12 12:43:45 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

size_t FindInString(const std::string& chaine, const std::string& sousChaine)
{
    size_t position = chaine.find(sousChaine);
    return (position);
}

std::deque<std::string> split(std::string& input, std::string del) {
    std::deque<std::string> output;
    std::string word;

    int start, end = -1 * del.size();
    do 
    {
        start = end + del.size();
        end = input.find(del, start);
        word = input.substr(start, end - start);
        if (!word.empty())
            output.push_back(word);
    } while (end != -1);
    return (output);
}
