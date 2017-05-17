//
//  QBasicErrors.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/17.
//
//

#include "QBasicErrors.h"

#include "QBasicSymbols.h"
#include "QBasicErrorEntity.h"
#include "QBasicVariableEntity.h"

/**
 *  コンストラクタ
 *  @param source プログラムソース
 */
QBasicErrors::QBasicErrors(QBasicSymbols *symbols) {
	this->symbols = symbols;
}

/**
 *  デストラクタ
 */
QBasicErrors::~QBasicErrors() {
	
}

/**
 *  エラー追加
 *  @param errorType エラータイプ
 *  @param message   メッセージ
 */
void QBasicErrors::addError(const ErrorType errorType, const string &message) {
	auto entity = QBasicErrorEntity(symbols->offset() - 1, errorType, message);
	errors.push_back(entity);
}

/**
 *  エラー追加
 *  @param symbolIndex シンボルインデックス
 *  @param errorType   エラータイプ
 *  @param message     メッセージ
 */
void QBasicErrors::addError(const int symbolIndex, const ErrorType errorType, const string &message) {
	auto entity = QBasicErrorEntity(symbolIndex, errorType, message);
	errors.push_back(entity);
}

/**
 *  エラークリア
 */
void QBasicErrors::clear() {
	errors.clear();
}

/**
 *  カウント
 */
int QBasicErrors::count() {
	return (int)errors.size();
}

/**
 *  エラー有無
 *  @return true: エラーあり、false: エラーなし
 */
bool QBasicErrors::hasError() {
	return errors.size() > 0;
}

/**
 *  エラータイプMissingFoundのメッセージ作成
 *  @param trueSymbol  正しいシンボル
 *  @param falseSymbol 間違ったシンボル
 *  @return メッセージ
 */
string QBasicErrors::buildMissingFound(const string &trueSymbol, const string &falseSymbol) {
	ostringstream stream;
	stream << "o:'" << trueSymbol << "' x:'" << falseSymbol << "'";
	return stream.str();
}

/**
 *  エラータイプBadVariableTypeのメッセージ作成
 *  @param trueVariable  正しいタイプ
 *  @param falseVariable 間違ったタイプ
 *  @return メッセージ
 */
string QBasicErrors::buildBadVariableType(const QBasicVariableEntity &trueVariable, const QBasicVariableEntity &falseVariable) {
	ostringstream stream;
	stream << "o:'" << QBasicVariableEntity::toString(trueVariable.type, trueVariable.valueTypes) << "' ";
	stream << "x:'" << QBasicVariableEntity::toString(falseVariable.type, falseVariable.valueTypes) << "'";
	return stream.str();
}

/**
 *  エラータイプBadVariableTypeのメッセージ作成
 *  @param trueTypes     正しいタイプ
 *  @param falseVariable 間違ったタイプ
 *  @return メッセージ
 */
string QBasicErrors::buildBadVariableType(const vector<VariableType> &trueTypes, const QBasicVariableEntity &falseVariable) {
	ostringstream stream;
	stream << "o:";
	for (auto it = trueTypes.begin();it != trueTypes.end();it++) {
		stream << "'" << QBasicVariableEntity::toString(*it) << "'";
		if (it == trueTypes.end() - 1) {
			stream << " ";
		} else {
			stream << ",";
		}
	}
	stream << "x:'" << QBasicVariableEntity::toString(falseVariable.type, falseVariable.valueTypes) << "'";
	return stream.str();
}

