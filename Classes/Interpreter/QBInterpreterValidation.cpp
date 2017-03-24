//
//  QBInterpreterValidation.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/25.
//
//

#include "QBInterpreterValidation.h"

#include "QBInterpreterStatements.h"
#include "QBInterpreterStatementEntity.h"

/// 基本ステートメント名
const vector<string> QBInterpreterValidation::basicStatementNames = {
	"var",
	"if",
	"then",
	"endif",
	"elseif",
	"else",
	"label",
	"goto",
	"gosub",
	"return",
	"for",
	"to",
	"step",
	"next",
	"rem",
	"exit",
	"and",
	"or",
	"xor",
};

/**
 *  変数名チェック
 *  @param variableName 変数名
 *  @return 変数名として使用可能か
 */
bool QBInterpreterValidation::isValidVariableName(const string variableName) {

	// 他の命令と被っていないか
	if (find(basicStatementNames.begin(), basicStatementNames.end(), variableName) != basicStatementNames.end()) {
		// TODO: [ERROR]変数名が予約語と被っています
		return false;
	}
	auto statements = QBInterpreterStatements::sharedInstance();
	if (statements.getStatement(variableName) != nullptr) {
		// TODO: [ERROR]変数名が予約語と被っています
		return false;
	}
	
	int i = 0;
	for (i = 0;i < variableName.length();i++) {
		char c = variableName.c_str()[i];
		// アルファベットOK
		if (isalpha(c)) {
			continue;
		}
		// 最初の文字に数字はダメ
		if (isdigit(c)) {
			if (i == 0) {
				// TODO: [ERROR]変数名の頭に数字を使用しています
				return false;
			}
			continue;
		}
		// TODO: [ERROR]変数名に英数字以外を使用しています
		return false;
	}
	return true;
}


