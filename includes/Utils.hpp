#pragma once

#include <string>
#include <deque>

size_t                  FindInString(const std::string& chaine, const std::string& sousChaine);
std::deque<std::string> split(std::string& input, std::string del);
