//
//  QBUserDefaultsManager.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/05/30.
//
//

#include "QBUserDefaultsManager.h"

#include "QBPlistManager.h"

/**
 *  コンストラクタ
 *  @param projectId プロジェクトId
 */
QBUserDefaultsManager::QBUserDefaultsManager(string projectId) {
	
	// ファイルパス作成
	filePath = FileUtils::getInstance()->getWritablePath() + "Script/" + projectId + "/" + "Save.plist";
	
	// 読み込み
	plistManager = new QBPlistManager(filePath);
}

/**
 *  デストラクタ
 */
QBUserDefaultsManager::~QBUserDefaultsManager() {
	// 解放
	delete plistManager;
	filePath.clear();
	filePath.shrink_to_fit();
	data.clear();
}

/**
 *  読込
 *  @param key キー
 *  @return 文字列
 */
string QBUserDefaultsManager::read(string key) {
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
void QBUserDefaultsManager::write(string key, string value) {
	data[key] = value;
	// 書込
	plistManager->setValue(key, value);
	plistManager->write(filePath);
}
