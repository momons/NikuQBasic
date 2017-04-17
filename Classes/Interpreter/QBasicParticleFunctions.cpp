//
//  QBasicParticleFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/22.
//
//

#include "QBasicParticleFunctions.h"

#include "QBasic.h"
#include "QBasicStatementEntity.h"
#include "QBasicVariableEntity.h"
#include "QBasicSubFunction.h"
#include "QBUserDefaultsManager.h"
#include "QBasicScene.h"

#pragma mark - スクリプトステートメント

/**
 *  ステートメントを作成
 *
 *  @return 文字操作ステートメント
 */
unordered_map<string, QBasicStatementEntity> QBasicParticleFunctions::buildStatements() {
	
	unordered_map<string, QBasicStatementEntity> statementList;
	QBasicStatementEntity entity;
	
	entity = QBasicStatementEntity("loadparticle", 2, true, loadparticle_qb);
	statementList[entity.name] = entity;
	entity = QBasicStatementEntity("drawparticle", 4, false, drawparticle_qb);
	statementList[entity.name] = entity;
	
	return statementList;
}

/// パーティクル読み込み
QBasicVariableEntity *QBasicParticleFunctions::loadparticle_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	interpreter->subFunc->scene->particles[stoi(arg[0])] = arg[1];
//	return "1";
	return nullptr;
}
/// パーティクル描画
QBasicVariableEntity *QBasicParticleFunctions::drawparticle_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg) {
//	interpreter->subFunc->drawParticle(
//									   stoi(arg[0]),
//									   stoi(arg[1]),
//									   stod(arg[2]),
//									   stod(arg[3])
//									   );
	return nullptr;
}
