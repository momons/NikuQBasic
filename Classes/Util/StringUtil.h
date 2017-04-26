//
//  StringUtil.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/18.
//
//

#ifndef StringUtil_h
#define StringUtil_h

#include <string>
#include <vector>

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
	
	/**
	 *  文字分割
	 *
	 *  @param result    分割文字
	 *  @param inStr     入力文字列
	 *  @param delimiter デリミタ
	 */
	static void split(vector<string> &result, const string &inStr, const string &delim);
};

#endif /* StringUtil_h */
