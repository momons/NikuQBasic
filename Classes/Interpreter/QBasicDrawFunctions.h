//
//  QBasicDrawFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#ifndef QBasicDrawFunctions_h
#define QBasicDrawFunctions_h

#include <stdio.h>

using namespace std;

class QBasic;
class QBasicStatementEntity;
class QBasicVariableEntity;

/// スクリプト 描画サブ関数群
class QBasicDrawFunctions final {
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
	/// 色指定
	static QBasicVariableEntity *color_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 色変更
	static QBasicVariableEntity *colorchg_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 線のサイズ指定
	static QBasicVariableEntity *linewidth_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 描画ロック
	static QBasicVariableEntity *drawlock_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 非表示
	static QBasicVariableEntity *hidden_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 指定位置に移動
	static QBasicVariableEntity *move_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 現在地から移動
	static QBasicVariableEntity *moveadd_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 拡大縮小
	static QBasicVariableEntity *scale_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 現在の状態から拡大縮小
	static QBasicVariableEntity *scaleadd_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 回転
	static QBasicVariableEntity *rotation_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 現在の状態から回転
	static QBasicVariableEntity *rotationadd_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 反転
	static QBasicVariableEntity *mirror_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
};

#endif /* QBasicDrawFunctions_h */
