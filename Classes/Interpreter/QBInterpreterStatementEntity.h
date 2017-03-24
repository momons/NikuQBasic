//
//  QBInterpreterStatementEntity.h
//  ToolQTheWorld
//
//  Created by HaraKazunari on 2015/02/18.
//  Copyright (c) 2015年 NikuQ. All rights reserved.
//

#ifndef __ToolQTheWorld__QBInterpreterStatementEntity__
#define __ToolQTheWorld__QBInterpreterStatementEntity__

#include <stdio.h>

using namespace std;

class QBInterpreter;

/** ステートメント */
typedef function <string (QBInterpreter *, const vector<string>)> statmentFunction;

/**
 * ステートメントEntity
 */
class QBInterpreterStatementEntity final {

public:
	
    /// ステートメント名
    string name;
    
    /// 引数数
    int argCount;
    
    /// 戻り値
    bool isReturnValue;
	
	/// 実行ファンクション
	statmentFunction func;
    
    /**
     * コンストラクタ
     */
    QBInterpreterStatementEntity();
    
    /**
     * コンストラクタ
     * @param name          ステートメント名
     * @param argCount      引数数
     * @param isReturnValue 戻り値
	 * @param func			実行ファンクション
     */
    QBInterpreterStatementEntity(
								 const string name,
								 const int argCount,
								 const bool isReturnValue,
								 const statmentFunction func
								 );

    /**
     * デストラクタ
     */
    ~QBInterpreterStatementEntity();
};

#endif /* defined(__ToolQTheWorld__QBInterpreterStatementEntity__) */
