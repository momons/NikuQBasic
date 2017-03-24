//
//  QBInterpreterParticleFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#include "QBInterpreterParticleFunctions.h"

#include "QBInterpreter.h"
#include "QBInterpreterStatementEntity.h"
#include "QBInterpreterSubFunction.h"
#include "QBUserDefaultsManager.h"
#include "QBInterpreterScene.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBInterpreterStatementEntity> QBInterpreterParticleFunctions::buildStatements() {
	
	unordered_map<string, QBInterpreterStatementEntity> statementList;
	QBInterpreterStatementEntity entity;
	
	entity = QBInterpreterStatementEntity("loadparticle", 2, true, loadparticle_qb);
	statementList[entity.name] = entity;
	entity = QBInterpreterStatementEntity("drawparticle", 4, false, drawparticle_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

/// パーティクル読み込み
string QBInterpreterParticleFunctions::loadparticle_qb(QBInterpreter *interpreter, const vector<string> arg) {
	interpreter->subFunc->scene->particles[stoi(arg[0])] = arg[1];
	return "1";
}
/// パーティクル描画
string QBInterpreterParticleFunctions::drawparticle_qb(QBInterpreter *interpreter, const vector<string> arg) {
	interpreter->subFunc->drawParticle(
									   stoi(arg[0]),
									   stoi(arg[1]),
									   stod(arg[2]),
									   stod(arg[3])
									   );
	return "";
}
