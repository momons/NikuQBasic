//
//  QBasicFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/28.
//
//

#ifndef QBasicFunctions_h
#define QBasicFunctions_h

using namespace std;

class QBasic;
class QBasicFunctionEntity;
class QBasicVariableEntity;
enum class VariableType;

/**
 * イベントスクリプト 関数制御用クラス定数
 */
class QBasicFunctions final {
	
public:

	/**
	 * 関数追加更新
	 * @param name          関数名
	 * @param variableTypes 引数タイプ
	 * @param returnVariableType 戻り値タイプ
	 * @param startOffset   開始オフセット
	 * @param endOffset     終了オフセット
	 * @return 関数情報
	 */
	QBasicFunctionEntity *addUpdate(
									const string &name,
									const vector<QBasicVariableEntity> variableTypes,
									VariableType returnVariableType,
									long startOffset,
									long endOffset);
	
	/**
	 * 名前で存在判定
	 * @param name 関数名
	 * @return 存在可否
	 */
	bool hasName(const string &name);
	
	/**
	 * 名前で存在判定
	 * @param name          関数名
	 * @param variableTypes 引数タイプ
	 * @return 存在可否
	 */
	bool hasFunction(const string &name, const vector<QBasicVariableEntity> &variableTypes);
	
	/**
	 * 名前と引数で取得
	 * @param name          関数名
	 * @param variableTypes 引数タイプ
	 * @return 関数情報
	 */
	QBasicFunctionEntity *getFunction(const string &name, const vector<QBasicVariableEntity> &variableTypes);
	
	/**
	 * 別名で取得
	 * @param name          関数名
	 * @param variableTypes 引数タイプ
	 * @return 関数情報
	 */
	QBasicFunctionEntity *getFunction(const string &alias);
	
	/**
	 *  クリア
	 */
	void clear();
	
	/**
	 * コンストラクタ
	 */
	QBasicFunctions();
	
	/**
	 * デストラクタ
	 */
	~QBasicFunctions();
	
private:
	
	/// 関数一覧 関数名,引数,戻り値
	unordered_map<string, QBasicFunctionEntity> functions;
	/// 関数を名前でさまった一覧
	vector<string> summaryNames;
	
};

#endif /* QBasicFunctions_h */
