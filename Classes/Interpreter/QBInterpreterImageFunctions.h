//
//  QBInterpreterImageFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#ifndef QBInterpreterImageFunctions_h
#define QBInterpreterImageFunctions_h

#include <stdio.h>

using namespace std;

class QBInterpreter;
class QBInterpreterStatementEntity;

/// スクリプト 画像操作サブ関数群
class QBInterpreterImageFunctions final {
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
	/// 画像読み込み
	static string loadimg_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 画像描画
	static string drawimg_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 画像拡大縮小
	static string imgscale_qb(QBInterpreter *interpreter, const vector<string> arg);
	/// 画像透過
	static string imgalpha_qb(QBInterpreter *interpreter, const vector<string> arg);
};

#endif /* QBInterpreterImageFunctions_h */
