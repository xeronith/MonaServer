/*
Copyright 2014 Mona
mathieu.poux[a]gmail.com
jammetthomas[a]gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License received along this program for more
details (or else see http://www.gnu.org/licenses/).

This file is a part of Mona.
*/

#include "Mona/MapParameters.h"

using namespace std;


namespace Mona {

void MapParameters::iteration(const char* prefix, ForEach& function) const {
	auto it = _map.begin();
	UInt32 prefixSize(0);
	if (prefix) {
		prefixSize = strlen(prefix);
		it = _map.lower_bound(prefix);
	}
	while (it != _map.end() && (prefixSize==0 || memcmp(prefix, it->first.c_str(), prefixSize) == 0)) {
		if (prefixSize>0) {
			const std::string key(&it->first[prefixSize]);
			function(key, it->second);
		} else
			function(it->first, it->second);
		++it;
	}
}

bool MapParameters::setRaw(const string& key, const char* value) {
	if (!value)
		return _map.erase(key)>0;
	_map[key].assign(value);
	return true;
}


} // namespace Mona
