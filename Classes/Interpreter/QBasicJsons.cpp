//
//  QBasicJsons.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/14.
//
//

#include "QBasicJsons.h"

/**
 *  オブジェクト変換
 *
 *  @param jsonValue  出力オブジェクト
 *  @param error      エラー
 *  @param jsonString JSON文字列
 */
void QBasicJsons::toObject(picojson::value &jsonValue, string *error, const string &jsonString) {
	
	// データ取得
	string::size_type jsonSize = jsonString.length();
	char *jsonBuff = (char*)malloc(jsonSize + 1);
	memset(jsonBuff, 0x00, jsonSize + 1);
	memcpy(jsonBuff, jsonString.c_str(), jsonSize);
	
	// JSON
	picojson::parse(jsonValue, jsonBuff, jsonBuff + jsonSize, error);
	
	// 解放
	free(jsonBuff);
	
}

/**
 *  JSON文字列変換
 *
 *  @param jsonString 出力JSON文字列
 *  @param error      エラー
 *  @param jsonValue  オブジェクト
 */
void QBasicJsons::toJSONString(string *jsonString, string *error, picojson::value *jsonValue) {
	if (jsonValue->is<picojson::object>()) {
		
	}
	
}
