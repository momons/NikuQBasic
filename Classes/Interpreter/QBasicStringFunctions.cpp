//
//  QBasicStringFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/18.
//
//

#include "QBasicStringFunctions.h"

#include "QBasic.h"
#include "StringUtil.h"
#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicStringFunctions::buildStatements() {

	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;

	entity = QBasicStatementEntity("length", 1, true, length_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("mid", 3, true, mid_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("left", 2, true, left_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("right", 2, true, right_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("split", 2, true, split_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("splitget", 1, true, splitget_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("replase", 3, true, replase_qb);
	statementList[entity.name] = entity;

	return statementList;
}

/// 文字列長取得
QBasicVariableEntity *QBasicStringFunctions::length_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString(arg[0].length());
	return nullptr;
}
/// 真ん中切り取り
QBasicVariableEntity *QBasicStringFunctions::mid_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return arg[0].substr(stoi(arg[1]), stoi(arg[2]));
	return nullptr;
}
/// 左切り取り
QBasicVariableEntity *QBasicStringFunctions::left_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return arg[0].substr(0, stoi(arg[1]));
	return nullptr;
}
/// 右切り取り
QBasicVariableEntity *QBasicStringFunctions::right_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	int length = stoi(arg[1]);
//	return arg[0].substr(arg[0].length() - length, length);
	return nullptr;
}
/// 分割
QBasicVariableEntity *QBasicStringFunctions::split_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return StringUtil::toString((double)interpreter->stringFunc->splitString(arg[0], arg[1]));
	return nullptr;
}
/// 分割結果取得
QBasicVariableEntity *QBasicStringFunctions::splitget_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	return interpreter->stringFunc->splitStringGet(stoi(arg[0]));
	return nullptr;
}
/// 置換
QBasicVariableEntity *QBasicStringFunctions::replase_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	string::size_type pos(arg[0].find(arg[1]));
//	string retStr = arg[0];
//	while (pos != string::npos) {
//		retStr.replace(pos, arg[1].length(), arg[2]);
//		pos = retStr.find(arg[1], pos + arg[2].length());
//	}
//	return retStr;
	return nullptr;
}

#pragma mark - サブルーチン

/**
 *  文字列を分割する
 *  @param inStr 文字列
 *  @param split 分割文字列
 *  @return カウント
 */
int QBasicStringFunctions::splitString(const string &inStr, const string &split) {
	splitList = vector<string>();
	string::size_type posBack = 0;
	string::size_type pos = inStr.find(split);
	while (pos != string::npos) {
		splitList.push_back(inStr.substr(posBack, pos - posBack));
		posBack = pos + split.length();
		pos = inStr.find(split, posBack);
	}
	splitList.push_back(inStr.substr(posBack, inStr.length() - posBack));
	return (int)splitList.size();
}

/**
 *  分割した文字取得
 *  @param index インデックス
 *  @return 文字列
 */
string QBasicStringFunctions::splitStringGet(const int index) {
	if (index < 0 || index >= splitList.size()) {
		return "";
	}
	return splitList[index];
}

/**
 *  コンストラクタ
 */
QBasicStringFunctions::QBasicStringFunctions() {
	// 初期化
	splitList.clear();
}
