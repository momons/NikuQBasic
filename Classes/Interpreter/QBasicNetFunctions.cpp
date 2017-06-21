//
//  QBasicNetFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/18.
//
//

#include "QBasicNetFunctions.h"

#include "QBasic.h"
#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicNetFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;

//	// ネット通信
//	entity = QBasicStatementEntity("net", 1, true, net_qb);
//	statementList[entity.name] = entity;
//	// ブラウザ
//	entity = QBasicStatementEntity("browser", 1, false, browser_qb);
//	statementList[entity.name] = entity;
	
	return statementList;
}

/// ネット通信
QBasicVariableEntity *QBasicNetFunctions::net_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	
//	string retNetValue;
//	
//	// 通信開始
//	interpreter->netFunc->startNetFetcher(arg[0], &retNetValue);
//	while (interpreter->netFunc->isConnect) {
//		// 通信が帰ってくるまで無限ループ
//	}
//	
//	return retNetValue;
	return nullptr;
}

/// ブラウザ
QBasicVariableEntity *QBasicNetFunctions::browser_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	Application::getInstance()->openURL(arg[0]);
	return nullptr;
}

#pragma mark - サブルーチン

/**
 *  HTTPスタート
 *  @param url         URL
 *  @param retNetValue 返却変数ポインタ
 */
void QBasicNetFunctions::startNetFetcher(const string &url, string *retNetValue) {
	
	// フラグON
	isConnect = true;
	
	// 退避
	this->retNetValue = retNetValue;
	
	// 解放
//	if (netFetcher != nullptr) {
//		delete netFetcher;
//	}
	
	// フェッチャスタート
//	netFetcher = new QBNetFetcher();
//	netFetcher->startRequest(url, this);
}

/**
 *  通信成功
 *  @param responseData レスポンスデータ
 */
void QBasicNetFunctions::successNetFetcher(const string responseData) {
	
	// 変数設定
	*retNetValue = responseData;
	
	// フラグOFF
	isConnect = false;
	
	// 解放
//	delete netFetcher;
//	netFetcher = nullptr;
}

/**
 *  通信失敗
 *  @param fetcher 対象フェッチャー
 *  @param status  HTTPステータス
 *  @param message メッセージ
 */
void QBasicNetFunctions::failure(const QBasicFetchers *fetcher, const long status, const string &message) {

	// 変数設定
	*retNetValue = "ERROR";
	
	// フラグOFF
	isConnect = false;
	
	// 解放
//	delete netFetcher;
//	netFetcher = nullptr;
}
