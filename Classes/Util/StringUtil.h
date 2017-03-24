//
//  StringUtil.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/18.
//
//

#ifndef StringUtil_h
#define StringUtil_h

#include <stdio.h>

using namespace std;

/// 文字列操作ユーティル
class StringUtil final {
public:

	/**
	 *  数値を文字列に変換
	 *  @param num 数値
	 *  @return 文字列
	 */
	static string toString(const double num);
	
};

#endif /* StringUtil_h */
