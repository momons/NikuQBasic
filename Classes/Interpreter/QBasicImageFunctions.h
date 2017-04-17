//
//  QBasicImageFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#ifndef QBasicImageFunctions_h
#define QBasicImageFunctions_h

#include <stdio.h>

using namespace std;

class QBasic;
class QBasicStatementEntity;
class QBasicVariableEntity;

/// スクリプト 画像操作サブ関数群
class QBasicImageFunctions final {
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
	/// 画像読み込み
	static QBasicVariableEntity *loadimg_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 画像描画
	static QBasicVariableEntity *drawimg_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 画像拡大縮小
	static QBasicVariableEntity *imgscale_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 画像透過
	static QBasicVariableEntity *imgalpha_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
};

#endif /* QBasicImageFunctions_h */
