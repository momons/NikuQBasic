//
//  QBasicTouchFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/21.
//
//

#include "QBasicTouchFunctions.h"

#include "QBasic.h"
#include "StringUtil.h"
#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"
#include "QBasicSubFunction.h"
#include "QBasicScene.h"
#include "QBasicVariableEntity.h"

/** 範囲外の場合の座標 **/
#define INVALID_TOUCH_LOCATION		"-9999"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicTouchFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;

	entity = QBasicStatementEntity("touchBegin", {}, { VariableType::List, VariableType::List, VariableType::Float }, touchBegin_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("touchMove", {}, { VariableType::List, VariableType::List, VariableType::Float }, touchMove_qb, nullptr);
	statementList[entity.alias] = entity;
	entity = QBasicStatementEntity("touchEnd", {}, { VariableType::List, VariableType::List, VariableType::Float }, touchEnd_qb, nullptr);
	statementList[entity.alias] = entity;
	
	return statementList;
}

/// タッチ開始
QBasicVariableEntity QBasicTouchFunctions::touchBegin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto value = QBasicVariableEntity("", { VariableType::List, VariableType::List, VariableType::Float }, nullptr);
	if (interpreter->subFunc->scene != nullptr) {
		for (auto it = interpreter->subFunc->scene->touchBegin.begin();it != interpreter->subFunc->scene->touchBegin.end();it++) {
			auto locationValue = QBasicVariableEntity("", { VariableType::List, VariableType::Float }, nullptr);
			double x = it->x;
			double y = it->y;
			auto xValue = QBasicVariableEntity("", { VariableType::Float }, &x);
			auto yValue = QBasicVariableEntity("", { VariableType::Float }, &y);
			locationValue.listValue.push_back(xValue);
			locationValue.listValue.push_back(yValue);
			value.listValue.push_back(locationValue);
		}
		value.isNil = value.listValue.size() <= 0;
	}
	return value;
}
/// タッチ移動
QBasicVariableEntity QBasicTouchFunctions::touchMove_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto value = QBasicVariableEntity("", { VariableType::List, VariableType::List, VariableType::Float }, nullptr);
	if (interpreter->subFunc->scene != nullptr) {
		for (auto it = interpreter->subFunc->scene->touchMove.begin();it != interpreter->subFunc->scene->touchMove.end();it++) {
			auto locationValue = QBasicVariableEntity("", { VariableType::List, VariableType::Float }, nullptr);
			double x = it->x;
			double y = it->y;
			auto xValue = QBasicVariableEntity("", { VariableType::Float }, &x);
			auto yValue = QBasicVariableEntity("", { VariableType::Float }, &y);
			locationValue.listValue.push_back(xValue);
			locationValue.listValue.push_back(yValue);
			value.listValue.push_back(locationValue);
		}
		value.isNil = value.listValue.size() <= 0;
	}
	return value;
}
/// タッチ終了
QBasicVariableEntity QBasicTouchFunctions::touchEnd_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
	auto value = QBasicVariableEntity("", { VariableType::List, VariableType::List, VariableType::Float }, nullptr);
	if (interpreter->subFunc->scene != nullptr) {
		for (auto it = interpreter->subFunc->scene->touchEnd.begin();it != interpreter->subFunc->scene->touchEnd.end();it++) {
			auto locationValue = QBasicVariableEntity("", { VariableType::List, VariableType::Float }, nullptr);
			double x = it->x;
			double y = it->y;
			auto xValue = QBasicVariableEntity("", { VariableType::Float }, &x);
			auto yValue = QBasicVariableEntity("", { VariableType::Float }, &y);
			locationValue.listValue.push_back(xValue);
			locationValue.listValue.push_back(yValue);
			value.listValue.push_back(locationValue);
		}
		value.isNil = value.listValue.size() <= 0;
	}
	return value;
}
