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
	/// int読込
	static inline vector<QBasicVariableEntity> loadInt_params();
	static inline QBasicVariableEntity loadInt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// float読込
	static inline vector<QBasicVariableEntity> loadFloat_params();
	static inline QBasicVariableEntity loadFloat_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// str読込
	static inline vector<QBasicVariableEntity> loadStr_params();
	static inline QBasicVariableEntity loadStr_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// bool読込
	static inline vector<QBasicVariableEntity> loadBool_params();
	static inline QBasicVariableEntity loadBool_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// list読込
	static inline vector<QBasicVariableEntity> loadList_params();
	static inline QBasicVariableEntity loadList_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// dict読込
	static inline vector<QBasicVariableEntity> loadDict_params();
	static inline QBasicVariableEntity loadDict_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// int保存
	static inline vector<QBasicVariableEntity> saveInt_params();
	static inline QBasicVariableEntity saveInt_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	/// float保存
	static inline vector<QBasicVariableEntity> saveFloat_params();
	static inline QBasicVariableEntity saveFloat_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	/// str保存
	static inline vector<QBasicVariableEntity> saveStr_params();
	static inline QBasicVariableEntity saveStr_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	/// bool保存
	static inline vector<QBasicVariableEntity> saveBool_params();
	static inline QBasicVariableEntity saveBool_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	/// list保存
	static inline vector<QBasicVariableEntity> saveList_params();
	static inline QBasicVariableEntity saveList_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	/// dict保存
	static inline vector<QBasicVariableEntity> saveDict_params();
	static inline QBasicVariableEntity saveDict_qb(QBasic *interpreter, vector<QBasicVariableEntity> &arg);
	/// キーが存在するかチェック
	static inline vector<QBasicVariableEntity> hasFileKey_params();
	static inline QBasicVariableEntity hasFileKey_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 削除
	static inline vector<QBasicVariableEntity> removeStorage_params();
	static inline QBasicVariableEntity removeStorage_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	

};

#endif /* QBasicStorageFunctions_h */
