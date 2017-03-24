//
//  QBPlistManager.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/07/07.
//
//

#include "QBPlistManager.h"

/**
 *  コンストラクタ
 *  @param filePath ファイルパス
 */
QBPlistManager::QBPlistManager(string filePath) {

	// ファイルパス退避
	this->filePath = filePath;
	
	// 読み込み
	read(filePath);
}

/**
 *  デストラクタ
 */
QBPlistManager::~QBPlistManager() {
	filePath.clear();
	filePath.shrink_to_fit();
	data.clear();
}

/**
 *  読込
 *  @param filePath ファイルパス
 */
void QBPlistManager::read(string filePath) {
	
	// ファイル読込
	data = FileUtils::getInstance()->getValueMapFromFile(filePath);
}

/**
 *  書込
 *  @param filePath ファイルパス
 */
void QBPlistManager::write(string filePath) {
	FileUtils::getInstance()->writeToFile(data, filePath);
}

/**
 *  値を取得
 *  @param key キー
 *  @return 値
 */
string QBPlistManager::getValue(string key) {
	return data[key].asString();
}

/**
 *  値を設定
 *  @param key   キー
 *  @param value 値
 */
void QBPlistManager::setValue(string key, string value) {
	data[key] = value;
	
}
