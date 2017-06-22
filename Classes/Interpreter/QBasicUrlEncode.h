//
//  QBasicUrlEncode.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/22.
//
//

#ifndef QBasicUrlEncode_h
#define QBasicUrlEncode_h

#include <string>

using namespace std;

class QBasicVariableEntity;

/**
 *  クエリを扱うクラス
 */
class QBasicUrlEncode final {
public:
	
	/**
	 *  URLエンコード
	 *  @param value  変換前文字列
	 *  @return 変換後文字列
	 */
	static string encode(const string &value);
	
	/**
	 *  URLデコード
	 *  @param value  変換前文字列
	 *  @return 変換後文字列
	 */
	static string decode(const string &value);
	
private:
	
	/**
	 *  コンストラクタ
	 */
	QBasicUrlEncode() {}
	
	/**
	 *  デストラクタ
	 */
	~QBasicUrlEncode() {}
};

#endif /* QBasicUrlEncode_h */
