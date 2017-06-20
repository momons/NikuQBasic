//
//  QBasicPlists.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/07/07.
//
//

#include "QBasicPlists.h"

/**
 *  コンストラクタ
 *  @param filePath ファイルパス
 */
QBasicPlists::QBasicPlists(const string &filePath) {

	// ファイルパス退避
	this->filePath = filePath;
	
	// 読み込み
	read();
}

/**
 *  デストラクタ
 */
QBasicPlists::~QBasicPlists() {
}

/**
 *  読込
 */
void QBasicPlists::read() {
	// ファイル読込
	data = FileUtils::getInstance()->getValueMapFromFile(filePath);
}

/**
 *  書込
 */
void QBasicPlists::write() {
	FileUtils::getInstance()->writeToFile(data, filePath);
}

/**
 *  値を取得
 *  @param key キー
 *  @return 値
 */
string QBasicPlists::getValue(const string &key) {
	if (data.find(key) == data.end()) {
		return "";
	}
	return data[key].asString();
}

/**
 *  値を設定
 *  @param key   キー
 *  @param value 値
 */
void QBasicPlists::setValue(const string &key, const string &value) {
	data[key] = value;
}

/**
 *  値を削除
 *  @param key   キー
 */
void QBasicPlists::clearValue(const string &key) {
	auto it = data.find(key);
	if (it == data.end()) {
		return;
	}
	data.erase(it);
}

/**
 *  全て削除
 */
void QBasicPlists::clearAll() {
	data.clear();
}

