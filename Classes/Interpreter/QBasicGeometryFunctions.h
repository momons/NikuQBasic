//
//  QBasicGeometryFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#ifndef QBasicGeometryFunctions_h
#define QBasicGeometryFunctions_h

#include <stdio.h>

using namespace std;

class QBasic;
class QBasicStatementEntity;
class QBasicVariableEntity;

/// スクリプト 図形描画サブ関数群
class QBasicGeometryFunctions final {
public:
	
	/**
	 *  ステートメントを作成
	 *
	 *  @return 文字操作ステートメント
	 */
	static unordered_map<string, QBasicStatementEntity> buildStatements();
	
	/**
	 *  スクリプト用ステートメント
	 *  @param interpreter 親クラス
	 *  @param arg         引数
	 *  @return 戻り値
	 */
	/// 線描画
	static QBasicVariableEntity *line_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 四角描画
	static QBasicVariableEntity *rect_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 円描画
	static QBasicVariableEntity *circle_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 三角描画
	static QBasicVariableEntity *triangle_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
};

#endif /* QBasicGeometryFunctions_h */
