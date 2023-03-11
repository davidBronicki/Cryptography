#pragma once

#include <string>
#include <vector>
#include <tuple>

std::vector<std::string> parse(const std::string& input, char delimiter = ' ');
std::tuple<std::string, std::string> clipOne(const std::string& input, char delimiter = ' ');
std::string fullConcat(const std::vector<std::string>& input, std::string pad = "");
std::string removeCase(const std::string& input);
