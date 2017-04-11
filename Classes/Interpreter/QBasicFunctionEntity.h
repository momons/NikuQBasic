//
//  QBasicFunctionEntity.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/10.
//
//

#ifndef QBasicFunctionEntity_h
#define QBasicFunctionEntity_h

#include <stdio.h>

using namespace std;

/**
 * ステートメントEntity
 */
class QBasicFunctionEntity final {
	
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
	QBasicFunctionEntity();
	
	/**
	 * デストラクタ
	 */
	~QBasicFunctionEntity();
};

#endif /* QBasicFunctionEntity_h */
