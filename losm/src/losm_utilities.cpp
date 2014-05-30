/**
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2014 Kyle Wray
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of
 *  this software and associated documentation files (the "Software"), to deal in
 *  the Software without restriction, including without limitation the rights to
 *  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 *  the Software, and to permit persons to whom the Software is furnished to do so,
 *  subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 *  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 *  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 *  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#include "../include/losm_utilities.h"

void trim_whitespace(std::string &item)
{
	// Trim from the left side.
	int left = 0;
	for (left = 0; left < item.length(); left++) {
		if (item[left] != ' ') {
			break;
		}
	}

	// Trim from the right side.
	int right = item.length();
	for (right = item.length(); right > 0; right--) {
		if (item[right - 1] != ' ') {
			break;
		}
	}

	item = item.substr(left, right - left);
}

std::vector<std::string> split_string_by_comma(std::string item)
{
	// Split the key and value of the line, and trim the white spaces.
	std::istringstream ssLine(item);
	std::vector<std::string> items;
	std::string temp;

	while (std::getline(ssLine, temp, ',')) {
		trim_whitespace(temp);
		if (temp.length() == 0) {
			continue;
		}
		items.push_back(temp);
	}

	return items;
}
