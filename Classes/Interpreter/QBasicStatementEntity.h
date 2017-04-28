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
typedef function <QBasicVariableEntity (QBasic *, const vector<QBasicVariableEntity>&)> statmentFunction;

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
	vector<VariableType> argTypes;
    
	/// 戻り値タイプ
	VariableType returnType;
	/// 戻り値サブタイプ
	vector<VariableType> returnSubTypes;
	
	/// 実行ファンクション
	statmentFunction func;
    
    /**
     * コンストラクタ
     */
    QBasicStatementEntity();

	/**
	 * コンストラクタ
	 * @param name           ステートメント名
	 * @param argTypes       引数変数タイプ
	 * @param returnType     戻り値タイプ
	 * @param func			 実行ファンクション
	 */
	QBasicStatementEntity(
						  const string &name,
						  const vector<VariableType> &argTypes,
						  const VariableType returnType,
						  const statmentFunction &func);
	
	/**
	 * コンストラクタ
	 * @param name           ステートメント名
	 * @param argTypes       引数変数タイプ
	 * @param returnType     戻り値タイプ
	 * @param returnSubTypes 戻り値サブタイプ
	 * @param func			 実行ファンクション
	 */
	QBasicStatementEntity(
						  const string &name,
						  const vector<VariableType> &argTypes,
						  const VariableType returnType,
						  const vector<VariableType> &returnSubTypes,
						  const statmentFunction &func);
	
    /**
     * デストラクタ
     */
    ~QBasicStatementEntity();
	
	/**
	 * 関数名変換
	 * @param name       元の名前
	 * @param argTypes   引数変数タイプ
	 * @return 変換名
	 */
	static string exchangeAlias(const string &name, const vector<VariableType> &argTypes);
	
	/**
	 * 関数名変換
	 * @param name       元の名前
	 * @param argNames   引数名
	 * @return 変換別名
	 */
	static string exchangeAlias(const string &name, const vector<string> &argNames);
	
	/**
	 * 別名設定
	 */
	void configureAlias();
};

#endif /* defined(__ToolQTheWorld__QBasicStatementEntity__) */
