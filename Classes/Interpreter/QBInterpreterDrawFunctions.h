//
//  QBInterpreterDrawFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#ifndef QBInterpreterDrawFunctions_h
#define QBInterpreterDrawFunctions_h

#include <stdio.h>

using namespace std;

class QBInterpreter;
class QBInterpreterStatementEntity;

/// スクリプト 描画サブ関数群
class QBInterpreterDrawFunctions final {
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
	/// 色指定
	static string color_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 色変更
	static string colorchg_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 線のサイズ指定
	static string linewidth_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 描画ロック
	static string drawlock_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 非表示
	static string hidden_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 指定位置に移動
	static string move_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 現在地から移動
	static string moveadd_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 拡大縮小
	static string scale_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 現在の状態から拡大縮小
	static string scaleadd_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 回転
	static string rotation_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 現在の状態から回転
	static string rotationadd_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 反転
	static string mirror_qb(QBInterpreter *interpreter, const vector<string> arg);
};

#endif /* QBInterpreterDrawFunctions_h */
