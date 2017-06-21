//
//  QBasicUrlEncode.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/22.
//
//

#include "QBasicUrlEncode.h"

#include <iomanip>

/**
 *  URLエンコード
 *  @param value  変換前文字列
 *  @return 変換後文字列
 */
string QBasicUrlEncode::urlEncode(const string &value) {
	ostringstream escaped;
	escaped.fill('0');
	escaped << hex;
	
	for (auto it = value.begin();it != value.end();it++) {
		
		string::value_type chr = *it;
		
		if (isalnum(chr) || chr == '-' || chr == '_' || chr == '.' || chr == '~') {
			escaped << chr;
			continue;
		}
		
		escaped << uppercase;
		escaped << '%' << setw(2) << int((unsigned char) chr);
		escaped << nouppercase;
	}
	
	return escaped.str();
	
	
	
}
