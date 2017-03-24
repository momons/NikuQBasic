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

