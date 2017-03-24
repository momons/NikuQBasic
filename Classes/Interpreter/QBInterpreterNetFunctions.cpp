//
//  QBInterpreterNetFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/18.
//
//

#include "QBInterpreterNetFunctions.h"

#include "QBInterpreter.h"
#include "QBInterpreterStatementEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBInterpreterStatementEntity> QBInterpreterNetFunctions::buildStatements() {
	
	unordered_map<string, QBInterpreterStatementEntity> statementList;
	QBInterpreterStatementEntity entity;

	// ネット通信
	entity = QBInterpreterStatementEntity("net", 1, true, net_qb);
	statementList[entity.name] = entity;
	// ブラウザ
	entity = QBInterpreterStatementEntity("browser", 1, false, browser_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

/// ネット通信
string QBInterpreterNetFunctions::net_qb(QBInterpreter *interpreter, const vector<string> arg) {
	
	string retNetValue;
	
	// 通信開始
	interpreter->netFunc->startNetFetcher(arg[0], &retNetValue);
	while (interpreter->netFunc->isConnect) {
		// 通信が帰ってくるまで無限ループ
	}
	
	return retNetValue;
}

/// ブラウザ
string QBInterpreterNetFunctions::browser_qb(QBInterpreter *interpreter, const vector<string> arg) {
	Application::getInstance()->openURL(arg[0]);
	return "";
}

#pragma mark - サブルーチン

/**
 *  HTTPスタート
 *  @param url         URL
 *  @param retNetValue 返却変数ポインタ
 */
void QBInterpreterNetFunctions::startNetFetcher(const string url, string *retNetValue) {
	
	// フラグON
	isConnect = true;
	
	// 退避
	this->retNetValue = retNetValue;
	
	// 解放
	if (netFetcher != nullptr) {
		delete netFetcher;
	}
	
	// フェッチャスタート
	netFetcher = new QBNetFetcher();
	netFetcher->startRequest(url, this);
}

/**
 *  通信成功
 *  @param responseData レスポンスデータ
 */
void QBInterpreterNetFunctions::successNetFetcher(const string responseData) {
	
	// 変数設定
	*retNetValue = responseData;
	
	// フラグOFF
	isConnect = false;
	
	// 解放
	delete netFetcher;
	netFetcher = nullptr;
}

/**
 *  通信失敗
 */
void QBInterpreterNetFunctions::failureNetFetcher() {
	
	// 変数設定
	*retNetValue = "ERROR";
	
	// フラグOFF
	isConnect = false;
	
	// 解放
	delete netFetcher;
	netFetcher = nullptr;
}
