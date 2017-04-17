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
enum class VariableType;

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
	/// 引数変数タイプ
	vector<VariableType> argTypes;
    
    /// 戻り値
    bool isReturnValue;
	/// 戻り値タイプ
	VariableType returnType;
	
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
						  const statmentFunction &func);
	/**
	 * コンストラクタ
	 * @param name          ステートメント名
	 * @param argTypes      引数変数タイプ
	 * @param returnType    戻り値タイプ
	 * @param func			実行ファンクション
	 */
	QBasicStatementEntity(
						  const string &name,
						  const vector<VariableType> &argTypes,
						  const VariableType returnType,
						  const statmentFunction &func);
    /**
     * デストラクタ
     */
    ~QBasicStatementEntity();
};

#endif /* defined(__ToolQTheWorld__QBasicStatementEntity__) */
