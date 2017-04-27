//
//  QBasicFunctionEntity.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/10.
//
//

#ifndef QBasicFunctionEntity_h
#define QBasicFunctionEntity_h

using namespace std;

class QBasicVariableEntity;
enum class VariableType;

/**
 * 関数Entity
 */
class QBasicFunctionEntity final {
	
public:
	
	/// 名前
	string name;
	
	/// 名前 (引数+戻り値)
	string alias;

	/// 引数名
	vector<QBasicVariableEntity> argNames;
	
	/// 戻り値タイプ
	VariableType returnVariableType;
	
	/// 開始オフセット
	long startOffset;
	/// 終了オフセット
	long endOffset;
	
	/**
	 * コンストラクタ
	 */
	QBasicFunctionEntity();

	/**
	 * コンストラクタ
	 * @param name               関数名
	 * @param argNames           引数変数タイプ
	 * @param returnVariableType 戻り値タイプ
	 * @param startOffset        開始オフセット
	 * @param endOffset          終了オフセット
	 */
	QBasicFunctionEntity(
						 const string &name,
						 const vector<QBasicVariableEntity> &argNames,
						 VariableType returnVariableType,
						 long startOffset,
						 long endOffset);

	/**
	 * デストラクタ
	 */
	~QBasicFunctionEntity();
	
	/**
	 * 関数名変換
	 * @param name       元の名前
	 * @param argTypes   引数変数タイプ
	 * @param returnType 戻り値タイプ
	 * @return 変換名
	 */
	static string exchangeAlias(const string &name, const vector<QBasicVariableEntity> &argNames);
	
	/**
	 * 別名設定
     */
	void configureAlias();
};

#endif /* QBasicFunctionEntity_h */
