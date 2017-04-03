//
//  StringUtil.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/18.
//
//

#include "StringUtil.h"

/**
 *  数値を文字列に変換
 *  @param num 数値
 *  @return 文字列
 */
string StringUtil::toString(const double num) {
	ostringstream os;
	os << num;
	return os.str();
}

/**
 *  文字分割
 *
 *  @param result    分割文字
 *  @param inStr     入力文字列
 *  @param delimiter デリミタ
 */
void StringUtil::split(vector<string> &result, const string &inStr, const string &delim) {
	
	result.clear();
	
	using string = string;
	string::size_type pos = 0;
	
	while (pos != string::npos) {
		string::size_type p = inStr.find(delim, pos);
		
		if (p == string::npos) {
			result.push_back(inStr.substr(pos));
			break;
		} else {
			result.push_back(inStr.substr(pos, p - pos));
		}
		pos = p + delim.size();
	}
}
