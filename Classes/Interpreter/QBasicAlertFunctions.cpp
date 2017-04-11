//
//  QBasicAlertFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#include "QBasicAlertFunctions.h"

#include "QBasic.h"
#include "QBasicStatementEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicAlertFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
	entity = QBasicStatementEntity("alert", 3, false, alert_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("confirm", 4, true, confirm_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("input", 3, true, input_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

/// アラート
string QBasicAlertFunctions::alert_qb(QBasic *interpreter, const vector<string> arg) {
	// Alert起動
	//	QBAlertViewLauncher::show(arg[0].c_str(), arg[1].c_str(), arg[2].c_str());
	//	while (QBAlertViewLauncher::isShow) {
	//		// 帰ってくるまで無限ループ
	//	}
	return "";
}
/// 確認アラート
string QBasicAlertFunctions::confirm_qb(QBasic *interpreter, const vector<string> arg) {
	// Alert起動
	//	QBAlertViewLauncher::showConfirm(arg[0].c_str(), arg[1].c_str(), arg[2].c_str(), arg[3].c_str());
	//	while (QBAlertViewLauncher::isShow) {
	//		// 帰ってくるまで無限ループ
	//	}
	//	return QBAlertViewLauncher::retValue;
	return "";
}
/// 入力アラート
string QBasicAlertFunctions::input_qb(QBasic *interpreter, const vector<string> arg) {
	// Alert起動
	//	QBAlertViewLauncher::showInput(arg[0].c_str(), arg[1].c_str(), arg[2].c_str());
	//	while (QBAlertViewLauncher::isShow) {
	//		// 帰ってくるまで無限ループ
	//	}
	//	return QBAlertViewLauncher::retValue;
	return "";
}

