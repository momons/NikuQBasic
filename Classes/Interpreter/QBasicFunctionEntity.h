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
	 * デストラクタ
	 */
	~QBasicFunctionEntity();
};

#endif /* QBasicFunctionEntity_h */
