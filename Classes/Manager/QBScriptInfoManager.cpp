//
//  QBScriptInfoManager.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2015/07/06.
//
//

#include "QBScriptInfoManager.h"

#include "QBasicPlists.h"

/**
 *  コンストラクタ
 *  @param projectId プロジェクトId
 */
QBScriptInfoManager::QBScriptInfoManager(string projectId) {

	// 初期化
	_plistManager = nullptr;
	
	// ファイルパス作成
	_filePath = FileUtils::getInstance()->getWritablePath() + "Script/" + projectId + "/" + "Info.plist";
	
	// 読み込み
	read();
}

/**
 *  デストラクタ
 */
QBScriptInfoManager::~QBScriptInfoManager() {
	
	// 解放
	delete _plistManager;
	_filePath.clear();
	_filePath.shrink_to_fit();
	this->projectId.clear();
	this->projectId.shrink_to_fit();
	this->projectName.clear();
	this->projectName.shrink_to_fit();
	this->copyright.clear();
	this->copyright.shrink_to_fit();
	this->comment.clear();
	this->comment.shrink_to_fit();
	
}

/**
 *  読み込み
 */
void QBScriptInfoManager::read() {
	
	// 解放
	if (_plistManager != nullptr) {
		delete _plistManager;
	}
	
	// 読み込み
	_plistManager = new QBasicPlists(_filePath);
	
	// 情報取得
	this->projectId = _plistManager->getValue("projectId");
	this->projectName = _plistManager->getValue("projectName");
	this->orientation = atoi(_plistManager->getValue("orientation").c_str());
	this->screenWidth = atoi(_plistManager->getValue("screenWidth").c_str());
	this->screenHeight = atoi(_plistManager->getValue("screenHeight").c_str());
	this->copyright = _plistManager->getValue("copyright");
	this->comment = _plistManager->getValue("comment");
	
}

/**
 *  書き込み
 */
void QBScriptInfoManager::write() {
	
	// 情報保存
	_plistManager->setValue("projectId", this->projectId);
	_plistManager->setValue("projectName", this->projectName);
	_plistManager->setValue("orientation", to_string(this->orientation));
	_plistManager->setValue("screenWidth", to_string(this->screenWidth));
	_plistManager->setValue("screenHeight", to_string(this->screenHeight));
	_plistManager->setValue("copyright", this->copyright);
	_plistManager->setValue("comment", this->comment);
	
	_plistManager->write();

}
