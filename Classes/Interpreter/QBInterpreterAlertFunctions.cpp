//
//  QBInterpreterAlertFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#include "QBInterpreterAlertFunctions.h"

#include "QBInterpreter.h"
#include "QBInterpreterStatementEntity.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBInterpreterStatementEntity> QBInterpreterAlertFunctions::buildStatements() {
	
	unordered_map<string, QBInterpreterStatementEntity> statementList;
	QBInterpreterStatementEntity entity;
	
	entity = QBInterpreterStatementEntity("alert", 3, false, alert_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("confirm", 4, true, confirm_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("input", 3, true, input_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

/// アラート
string QBInterpreterAlertFunctions::alert_qb(QBInterpreter *interpreter, const vector<string> arg) {
	// Alert起動
	//	QBAlertViewLauncher::show(arg[0].c_str(), arg[1].c_str(), arg[2].c_str());
	//	while (QBAlertViewLauncher::isShow) {
	//		// 帰ってくるまで無限ループ
	//	}
	return "";
}
/// 確認アラート
string QBInterpreterAlertFunctions::confirm_qb(QBInterpreter *interpreter, const vector<string> arg) {
	// Alert起動
	//	QBAlertViewLauncher::showConfirm(arg[0].c_str(), arg[1].c_str(), arg[2].c_str(), arg[3].c_str());
	//	while (QBAlertViewLauncher::isShow) {
	//		// 帰ってくるまで無限ループ
	//	}
	//	return QBAlertViewLauncher::retValue;
	return "";
}
/// 入力アラート
string QBInterpreterAlertFunctions::input_qb(QBInterpreter *interpreter, const vector<string> arg) {
	// Alert起動
	//	QBAlertViewLauncher::showInput(arg[0].c_str(), arg[1].c_str(), arg[2].c_str());
	//	while (QBAlertViewLauncher::isShow) {
	//		// 帰ってくるまで無限ループ
	//	}
	//	return QBAlertViewLauncher::retValue;
	return "";
}

