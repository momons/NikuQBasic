//
//  QBasicPushBackEntity.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/01.
//
//

#ifndef QBasicPushBackEntity_h
#define QBasicPushBackEntity_h

using namespace std;

class QBasicVariableEntity;

/**
 * 退避用Entity
 */
class QBasicPushBackEntity final {
public:

	/// 関数名
	string name;
	/// 文字退避
	string symbol;
	/// 文字退避
	long execOffset;
	/// ローカル変数
	unordered_map<string, QBasicVariableEntity> localVariables;
	
	/**
	 * コンストラクタ
	 * @param name           関数名
	 * @param symbol         退避文字
	 * @param execOffset     実行オフセット
	 * @param localVariables ローカル変数
	 */
	QBasicPushBackEntity(
						 const string &name,
						 const string &symbol,
						 const long execOffset,
						 const unordered_map<string, QBasicVariableEntity> &localVariables);
	
	/**
	 * デストラクタ
	 */
	~QBasicPushBackEntity();
};

#endif /* QBasicPushBackEntity_h */
