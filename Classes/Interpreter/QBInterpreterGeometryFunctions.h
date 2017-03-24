//
//  QBInterpreterGeometryFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#ifndef QBInterpreterGeometryFunctions_h
#define QBInterpreterGeometryFunctions_h

#include <stdio.h>

using namespace std;

class QBInterpreter;
class QBInterpreterStatementEntity;

/// スクリプト 図形描画サブ関数群
class QBInterpreterGeometryFunctions final {
public:
	
	/**
	 *  ステートメントを作成
	 *
	 *  @return 文字操作ステートメント
	 */
	static unordered_map<string, QBInterpreterStatementEntity> buildStatements();
	
	/**
	 *  スクリプト用ステートメント
	 *  @param interpreter 親クラス
	 *  @param arg         引数
	 *  @return 戻り値
	 */
	/// 線描画
	static string line_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 四角描画
	static string rect_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 円描画
	static string circle_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 三角描画
	static string triangle_qb(QBInterpreter *interpreter, const vector<string> arg);
};

#endif /* QBInterpreterGeometryFunctions_h */
