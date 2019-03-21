
//Global_Functions.h

#pragma once

#include <string>
#include <vector>
#include <tuple>

using namespace std;

vector<string> parse(const string& input, char delimiter = ' ');
tuple<string, string> clipOne(const string& input, char delimiter = ' ');
string fullConcat(const vector<string>& input, string pad = "");
string removeCase(const string& input);
