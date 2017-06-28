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
#include "QBasicQueries.h"
#include "QBasicErrors.h"
#include "QBasicErrorEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicNetFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;

	entity = QBasicStatementEntity("net", net_params(), { VariableType::Void }, net_qb, net_compile);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("toQuaryParams", toQuaryParams_params(), { VariableType::Str }, toQuaryParams_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("browser", browser_params(), { VariableType::Void }, browser_qb, nullptr);
	statementList[entity.alias] = entity;
	
	return statementList;
}

/// ネット通信
vector<QBasicVariableEntity> QBasicNetFunctions::net_params() {
	vector<QBasicVariableEntity> argNames;
	QBasicVariableEntity value;
	// 返却 変数名
	value = QBasicVariableEntity("ret", { VariableType::Str }, nullptr);
	argNames.push_back(value);
	// URL 必須
	value = QBasicVariableEntity("url", { VariableType::Str }, nullptr);
	argNames.push_back(value);
	// METHOD デフォルト GET
	value = QBasicVariableEntity("method", { VariableType::Str }, nullptr);
	value.set(string("GET"));
	argNames.push_back(value);
	// BODY デフォルト なし
	value = QBasicVariableEntity("body", { VariableType::Str }, nullptr);
	value.set("");
	argNames.push_back(value);
	// HEADER デフォルト指定なし
	value = QBasicVariableEntity("headers", { VariableType::Dict }, nullptr);
	value.set(map<string, QBasicVariableEntity>());
	argNames.push_back(value);
	return argNames;
}
QBasicVariableEntity QBasicNetFunctions::net_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	
//	string retNetValue;
//	
//	// 通信開始
//	interpreter->netFunc->startNetFetcher(arg[0], &retNetValue);
//	while (interpreter->netFunc->isConnect) {
//		// 通信が帰ってくるまで無限ループ
//	}
//	
//	return retNetValue;
	return QBasicVariableEntity("", { VariableType::Void }, nullptr);
}
void QBasicNetFunctions::net_compile(QBasic *interpreter, const vector<QBasicVariableEntity> &arg, const int symbolOffset) {
	auto it = interpreter->variables.find(arg[0].strValue);
	// 変数名チェック
	if (it == interpreter->variables.end()) {
		interpreter->errors->addError(symbolOffset, ErrorType::UnknownVariable, arg[0].strValue);
		return;
	}
	// 型チェック
	if (it->second.types.size() != 2 || it->second.types[0] != VariableType::Dict || it->second.types[1] != VariableType::Void) {
		interpreter->errors->addError(symbolOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({ VariableType::Dict, VariableType::Void }, it->second));
	}
}
/// クエリパラメータ変換
vector<QBasicVariableEntity> QBasicNetFunctions::toQuaryParams_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("v", { VariableType::Dict }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicNetFunctions::toQuaryParams_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg) {
	auto answer = QBasicQueries::toQueryString(arg[0]);
	return QBasicVariableEntity("", { VariableType::Str }, &answer);
}
/// ブラウザ
vector<QBasicVariableEntity> QBasicNetFunctions::browser_params() {
	vector<QBasicVariableEntity> argNames;
	argNames.push_back(QBasicVariableEntity("url", { VariableType::Str }, nullptr));
	return argNames;
}
QBasicVariableEntity QBasicNetFunctions::browser_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	Application::getInstance()->openURL(arg[0].strValue);
	return QBasicVariableEntity("", { VariableType::Void }, nullptr);
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
 *  @param fetcher    対象フェッチャー
 *  @param statusCode HTTPステータス
 *  @param response   レスポンスデータ
 */
void QBasicNetFunctions::success(const QBasicFetchers *fetcher, const long statusCode, const QBasicVariableEntity &response) {

	// フラグOFF
	isConnect = false;
}

/**
 *  通信失敗
 *  @param fetcher     対象フェッチャー
 *  @param statusCode  HTTPステータス
 *  @param errorType   エラータイプ
 */
void QBasicNetFunctions::failure(const QBasicFetchers *fetcher, const long statusCode, const QBasicFetchersErrorType errorType) {

	// 変数設定
	*retNetValue = "ERROR";
	
	// フラグOFF
	isConnect = false;
	
	// 解放
//	delete netFetcher;
//	netFetcher = nullptr;
}
