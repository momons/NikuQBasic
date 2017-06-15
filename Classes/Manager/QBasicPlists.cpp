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
	read(filePath);
}

/**
 *  デストラクタ
 */
QBasicPlists::~QBasicPlists() {
}

/**
 *  読込
 *  @param filePath ファイルパス
 */
void QBasicPlists::read(const string &filePath) {
	// ファイル読込
	data = FileUtils::getInstance()->getValueMapFromFile(filePath);
}

/**
 *  書込
 *  @param filePath ファイルパス
 */
void QBasicPlists::write(const string &filePath) {
	FileUtils::getInstance()->writeToFile(data, filePath);
}

/**
 *  値を取得
 *  @param key キー
 *  @return 値
 */
string QBasicPlists::getValue(const string &key) {
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
