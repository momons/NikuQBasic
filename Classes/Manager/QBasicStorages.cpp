//
//  QBasicStorages.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/05/30.
//
//

#include "QBasicStorages.h"

#include "picojson.h"
#include "QBasicPlists.h"
#include "QBasicVariableEntity.h"
#include "QBasicJsons.h"

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
 *  キーの存在チェック
 *  @param key キー
 *  @return キーあり/キーなし
 */
QBasicVariableEntity QBasicStorages::hasKey(const string &key) {
	bool answer = !plistManager->getValue(key).empty();
	return QBasicVariableEntity("", { VariableType::Bool }, &answer);
}

/**
 *  読込
 *  @param key キー
 *  @return 変数Entity
 */
QBasicVariableEntity QBasicStorages::read(const string &key) {
	
	QBasicVariableEntity returnValue;
	
	auto value = plistManager->getValue(key);
	if (value.empty()) {
		// 読み込み
		return returnValue;
	}
	
	// 文字列変換
	picojson::value jsonValue;
	string error;
	QBasicJsons::toObject(jsonValue, &error, value);
	
	if (!error.empty()) {
		// JSONコンバートエラー
		return returnValue;
	}
	
	auto valueEntity = QBasicVariableEntity::buildForStorageJsonObject(jsonValue.get<picojson::object>());
	return valueEntity;
}

/**
 *  書込
 *  @param key   キー
 *  @param value 値
 */
void QBasicStorages::write(const string &key, QBasicVariableEntity &value) {
	
	auto jsonObject = value.toStorageJsonObject();
	auto jsonString = picojson::value(jsonObject).serialize();
	
	// 書込
	plistManager->setValue(key, jsonString);
	plistManager->write();
}

/**
 *  削除
 *  @param key   キー
 */
void QBasicStorages::remove(const string &key) {
	plistManager->clearValue(key);
	plistManager->write();
}

/**
 *  全て削除
 */
void QBasicStorages::removeAll() {
	plistManager->clearAll();
	plistManager->write();
}

