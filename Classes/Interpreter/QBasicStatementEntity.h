//
//  QBasicStatementEntity.h
//  ToolQTheWorld
//
//  Created by HaraKazunari on 2015/02/18.
//  Copyright (c) 2015年 NikuQ. All rights reserved.
//

#ifndef __ToolQTheWorld__QBasicStatementEntity__
#define __ToolQTheWorld__QBasicStatementEntity__

using namespace std;

class QBasic;
class QBasicVariableEntity;

/** ステートメント */
typedef function <QBasicVariableEntity *(QBasic *, const vector<QBasicVariableEntity>&)> statmentFunction;

/**
 * ステートメントEntity
 */
class QBasicStatementEntity final {

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
    QBasicStatementEntity();
    
    /**
     * コンストラクタ
     * @param name          ステートメント名
     * @param argCount      引数数
     * @param isReturnValue 戻り値
	 * @param func			実行ファンクション
     */
    QBasicStatementEntity(
								 const string &name,
								 const int argCount,
								 const bool isReturnValue,
								 const statmentFunction &func
								 );

    /**
     * デストラクタ
     */
    ~QBasicStatementEntity();
};

#endif /* defined(__ToolQTheWorld__QBasicStatementEntity__) */
