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

/// 実行ステートメント
typedef function <QBasicVariableEntity (QBasic *, vector<QBasicVariableEntity>&)> statmentFunction;

/// コンパイルステートメント
typedef function <void (QBasic *, vector<QBasicVariableEntity>&, int)> compileFunction;

/**
 * ステートメントEntity
 */
class QBasicStatementEntity final {

public:
	
    /// ステートメント名
    string name;
	
	/// ステートメント名 (引数+戻り値)
	string alias;
	
	/// 引数変数タイプ
	vector<QBasicVariableEntity> argNames;
    
	/// 戻り値タイプ
	VariableType returnType;
	/// 戻り値サブタイプ
	vector<VariableType> returnSubTypes;
	
	/// 実行ファンクション
	statmentFunction execFunc;
	/// コンパイルファンクション
	compileFunction compileFunc;
	
    /**
     * コンストラクタ
     */
    QBasicStatementEntity();

	/**
	 * コンストラクタ
	 * @param name           ステートメント名
	 * @param argNames       引数変数タイプ
	 * @param returnType     戻り値タイプ
	 * @param execFunc		 実行ファンクション
	 * @param compileFunc    コンパイルファンクション
	 */
	QBasicStatementEntity(
						  const string &name,
						  const vector<QBasicVariableEntity> &argNames,
						  const VariableType returnType,
						  const statmentFunction &exeFunc,
						  const compileFunction &compileFunc);
	
	/**
	 * コンストラクタ
	 * @param name           ステートメント名
	 * @param argTypes       引数変数タイプ
	 * @param returnType     戻り値タイプ
	 * @param returnSubTypes 戻り値サブタイプ
	 * @param execFunc		 実行ファンクション
	 * @param compileFunc    コンパイルファンクション
	 */
	QBasicStatementEntity(
						  const string &name,
						  const vector<QBasicVariableEntity> &argNames,
						  const VariableType returnType,
						  const vector<VariableType> &returnSubTypes,
						  const statmentFunction &exeFunc,
						  const compileFunction &compileFunc);
	
    /**
     * デストラクタ
     */
    ~QBasicStatementEntity();
	
	/**
	 * 別名設定
	 */
	void configureAlias();
};

#endif /* defined(__ToolQTheWorld__QBasicStatementEntity__) */
