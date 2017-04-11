//
//  QBasicDateFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/20.
//
//

#include "QBasicDateFunctions.h"

#include <time.h>

#include "QBasic.h"
#include "StringUtil.h"
#include "QBasicStatementEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicDateFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("year", 0, true, year_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("month", 0, true, month_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("day", 0, true, day_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("hour", 0, true, hour_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("minute", 0, true, minute_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("second", 0, true, second_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("week", 0, true, week_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

/// 年取得
string QBasicDateFunctions::year_qb(QBasic *interpreter, const vector<string> arg) {
	struct tm *date = getNowDate();
	return StringUtil::toString(date->tm_year + 1900);
}
/// 月取得
string QBasicDateFunctions::month_qb(QBasic *interpreter, const vector<string> arg) {
	struct tm *date = getNowDate();
	return StringUtil::toString(date->tm_mon + 1);
}
/// 日付取得
string QBasicDateFunctions::day_qb(QBasic *interpreter, const vector<string> arg) {
	struct tm *date = getNowDate();
	return StringUtil::toString(date->tm_mday);
}
/// 時間取得
string QBasicDateFunctions::hour_qb(QBasic *interpreter, const vector<string> arg) {
	struct tm *date = getNowDate();
	return StringUtil::toString(date->tm_hour);
}
/// 分取得
string QBasicDateFunctions::minute_qb(QBasic *interpreter, const vector<string> arg) {
	struct tm *date = getNowDate();
	return StringUtil::toString(date->tm_min);
}
/// 秒取得
string QBasicDateFunctions::second_qb(QBasic *interpreter, const vector<string> arg) {
	struct tm *date = getNowDate();
	return StringUtil::toString(date->tm_sec);
}
/// 曜日取得
string QBasicDateFunctions::week_qb(QBasic *interpreter, const vector<string> arg) {
	struct tm *date = getNowDate();
	return StringUtil::toString(date->tm_wday);
}

#pragma mark - サブルーチン

/**
 * 現在日付取得
 * @return 現在日付
 */
struct tm *QBasicDateFunctions::getNowDate() {
	time_t now = NULL;
	struct tm *date;
	time(&now);
	date = localtime(&now);
	return date;
}
