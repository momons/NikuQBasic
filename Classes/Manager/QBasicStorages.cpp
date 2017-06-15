//
//  QBasicStorages.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/05/30.
//
//

#include "QBasicStorages.h"

#include "QBasicPlists.h"
#include "QBasicVariableEntity.h"

/**
 *  コンストラクタ
 *  @param projectId プロジェクトId
 */
QBasicStorages::QBasicStorages(const string &projectId) {
	
	// ファイルパス作成
	filePath = FileUtils::getInstance()->getWritablePath() + "Script/" + projectId + "/" + "Save.plist";
	
	// 読み込み
	plistManager = new QBasicPlists(filePath);
}

/**
 *  デストラクタ
 */
QBasicStorages::~QBasicStorages() {
	delete plistManager;
}

/**
 *  読込
 *  @param key キー
 *  @return 文字列
 */
string QBasicStorages::read(const string &key) {
	// キーに当てはまる情報があるかを検索
	if (data.count(key) > 0) {
		return data[key];
	}
	// 退避
	data[key] = plistManager->getValue(key);
	return data[key];
}

/**
 *  書込
 *  @param key   キー
 *  @param value 値
 */
void QBasicStorages::write(const string &key, const string &value) {
	data[key] = value;
	// 書込
	plistManager->setValue(key, value);
	plistManager->write(filePath);
}

/**
 *  書込
 *  @param key   キー
 *  @param value 値
 */
void QBasicStorages::write(const string &key, const QBasicVariableEntity &value) {
	
	
	
	
	
}
