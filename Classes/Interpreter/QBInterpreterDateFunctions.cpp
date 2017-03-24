//
//  QBInterpreterDateFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/20.
//
//

#include "QBInterpreterDateFunctions.h"

#include <time.h>

#include "QBInterpreter.h"
#include "StringUtil.h"
#include "QBInterpreterStatementEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBInterpreterStatementEntity> QBInterpreterDateFunctions::buildStatements() {
	
	unordered_map<string, QBInterpreterStatementEntity> statementList;
	QBInterpreterStatementEntity entity;
	
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("year", 0, true, year_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("month", 0, true, month_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("day", 0, true, day_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("hour", 0, true, hour_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("minute", 0, true, minute_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("second", 0, true, second_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("week", 0, true, week_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

/// 年取得
string QBInterpreterDateFunctions::year_qb(QBInterpreter *interpreter, const vector<string> arg) {
	struct tm *date = getNowDate();
	return StringUtil::toString(date->tm_year + 1900);
}
/// 月取得
string QBInterpreterDateFunctions::month_qb(QBInterpreter *interpreter, const vector<string> arg) {
	struct tm *date = getNowDate();
	return StringUtil::toString(date->tm_mon + 1);
}
/// 日付取得
string QBInterpreterDateFunctions::day_qb(QBInterpreter *interpreter, const vector<string> arg) {
	struct tm *date = getNowDate();
	return StringUtil::toString(date->tm_mday);
}
/// 時間取得
string QBInterpreterDateFunctions::hour_qb(QBInterpreter *interpreter, const vector<string> arg) {
	struct tm *date = getNowDate();
	return StringUtil::toString(date->tm_hour);
}
/// 分取得
string QBInterpreterDateFunctions::minute_qb(QBInterpreter *interpreter, const vector<string> arg) {
	struct tm *date = getNowDate();
	return StringUtil::toString(date->tm_min);
}
/// 秒取得
string QBInterpreterDateFunctions::second_qb(QBInterpreter *interpreter, const vector<string> arg) {
	struct tm *date = getNowDate();
	return StringUtil::toString(date->tm_sec);
}
/// 曜日取得
string QBInterpreterDateFunctions::week_qb(QBInterpreter *interpreter, const vector<string> arg) {
	struct tm *date = getNowDate();
	return StringUtil::toString(date->tm_wday);
}

#pragma mark - サブルーチン

/**
 * 現在日付取得
 * @return 現在日付
 */
struct tm *QBInterpreterDateFunctions::getNowDate() {
	time_t now = NULL;
	struct tm *date;
	time(&now);
	date = localtime(&now);
	return date;
}
