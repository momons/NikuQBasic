//
//  QBasicJsons.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/14.
//
//

#ifndef QBasicJsons_h
#define QBasicJsons_h

#include "picojson.h"

using namespace std;

/**
 *  JSONを扱うクラス
 */
class QBasicJsons final {
public:
	
	/**
	 *  オブジェクト変換
	 *
	 *  @param jsonValue  出力オブジェクト
	 *  @param error      エラー
	 *  @param jsonString JSON文字列
	 */
	static void toObject(picojson::value &jsonValue, string *error, const string &jsonString);

	/**
	 *  JSON文字列変換
	 *
	 *  @param jsonString 出力JSON文字列
	 *  @param error      エラー
	 *  @param jsonValue  オブジェクト
	 */
	static void toJSONString(string *jsonString, string *error, picojson::value *jsonValue);

private:
	
	/**
	 *  コンストラクタ
	 */
	QBasicJsons() {}
	
	/**
	 *  デストラクタ
	 */
	~QBasicJsons() {}
};

#endif /* QBasicJsons_h */
