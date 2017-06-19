//
//  QBasicStorageFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/21.
//
//

#ifndef QBasicStorageFunctions_h
#define QBasicStorageFunctions_h

#include <stdio.h>

using namespace std;

class QBasic;
class QBasicStatementEntity;
class QBasicVariableEntity;

/// スクリプト ストレージサブ関数群
class QBasicStorageFunctions final {
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
	/// 読込
	static inline vector<QBasicVariableEntity> loadFile_params();
	static inline QBasicVariableEntity loadFile_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 保存
	static inline vector<QBasicVariableEntity> saveFile_params();
	static inline QBasicVariableEntity saveFile_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	/// キーが存在するかチェック
	static inline vector<QBasicVariableEntity> hasFileKey_params();
	static inline QBasicVariableEntity hasFileKey_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 削除
	static inline vector<QBasicVariableEntity> removeFile_params();
	static inline QBasicVariableEntity removeFile_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	

};

#endif /* QBasicStorageFunctions_h */
