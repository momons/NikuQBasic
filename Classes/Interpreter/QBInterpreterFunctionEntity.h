//
//  QBInterpreterFunctionEntity.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/10.
//
//

#ifndef QBInterpreterFunctionEntity_h
#define QBInterpreterFunctionEntity_h

#include <stdio.h>

using namespace std;

/**
 * ステートメントEntity
 */
class QBInterpreterFunctionEntity final {
	
public:
	
	/// 引数名
	vector<string> argNames;
	
	/// 開始オフセット
	long startOffset;
	/// 終了オフセット
	long endOffset;
	
	/**
	 * コンストラクタ
	 */
	QBInterpreterFunctionEntity();
	
	/**
	 * デストラクタ
	 */
	~QBInterpreterFunctionEntity();
};

#endif /* QBInterpreterFunctionEntity_h */
