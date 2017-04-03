//
//  QBInterpreterMessages.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/28.
//
//

#include "QBInterpreterMessages.h"

#include "StringUtil.h"

/** インスタンス */
QBInterpreterMessages *QBInterpreterMessages::interpreterMessagesInstance;

/**
 * インスタンスシェア
 * @return インスタンス
 */
QBInterpreterMessages *QBInterpreterMessages::sharedInstance()
{
	static once_flag flag;
	
	// 一度だけコール
	call_once(flag,initialize);
	
	return QBInterpreterMessages::interpreterMessagesInstance;
}

/**
 * 初期化
 */
void QBInterpreterMessages::initialize() {
	QBInterpreterMessages::interpreterMessagesInstance = new QBInterpreterMessages();
	QBInterpreterMessages::interpreterMessagesInstance->build();
}

/**
 * デストラクタ
 */
QBInterpreterMessages::~QBInterpreterMessages() {
	delete QBInterpreterMessages::interpreterMessagesInstance;
}

/**
 *  メッセージ取得
 *  @param key    キー
 *  @param params パラメータ
 *  @return メッセージ
 */
string QBInterpreterMessages::getMessage(const string key, const char *params) {
	if (localizable.find(key) == localizable.end()) {
		return key;
	}
	if (params == nullptr) {
		return localizable[key];
	}
	ostringstream os;
	os << localizable[key] << *params;
	return os.str();
}

/**
 * メッセージ一覧作成
 */
void QBInterpreterMessages::build() {
	
	FileUtils *fileUtil = FileUtils::getInstance();
	
	// カレント言語取得
	LanguageType language = Application::getInstance()->getCurrentLanguage();
	if (language == LanguageType::JAPANESE) {
		fileUtil->addSearchPath("ja.lproj");
	} else {
		fileUtil->addSearchPath("en.lproj");
	}
	
	// ファイル名を読み込み
	string fullpath = fileUtil->fullPathForFilename("Localize.strings");
	string strings = fileUtil->getStringFromFile(fullpath);
	if (strings.empty()) {
		return;
	}
	
	vector<string> stringLines;
	StringUtil::split(stringLines, strings, "\";\n");
	for(auto it = stringLines.begin();it != stringLines.end();it++) {
		vector<string> stringKeyValue;
		StringUtil::split(stringKeyValue, *it, "=\"");
		if(stringKeyValue.size() == 2){
			localizable[stringKeyValue[0]] = stringKeyValue[1];
		}
	}
}
