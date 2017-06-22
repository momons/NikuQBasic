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
string QBasicUrlEncode::encode(const string &value) {
	ostringstream encode;
	encode.fill('0');
	encode << hex;
	
	for (auto it = value.begin();it != value.end();it++) {
		
		string::value_type chr = *it;
		
		if (isalnum(chr) || chr == '-' || chr == '_' || chr == '.' || chr == '~') {
			encode << chr;
			continue;
		}
		
		encode << uppercase;
		encode << '%' << setw(2) << int((unsigned char) chr);
		encode << nouppercase;
	}
	
	return encode.str();
}

/**
 *  URLデコード
 *  @param value  変換前文字列
 *  @return 変換後文字列
 */
string QBasicUrlEncode::decode(const string &value) {
	ostringstream decode;
	
	for (int i = 0;i < value.length();i++) {
		
		char chr = value[i];
		
		if (chr == '%' && i < value.length() - 2) {
			int decodeChr = 0;
			sscanf(value.substr(i + 1,2).c_str(), "%x", &decodeChr);
			chr = static_cast<char>(decodeChr);
			i += 2;
		}
		decode << chr;
	}
	return decode.str();
}
