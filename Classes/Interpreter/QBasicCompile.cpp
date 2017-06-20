//
//  QBasicCompile.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/07.
//
//

#include "QBasicCompile.h"

#include "QBasic.h"
#include "QBasicSymbols.h"
#include "QBasicVariableEntity.h"
#include "QBasicValidation.h"
#include "QBasicErrors.h"
#include "QBasicErrorEntity.h"
#include "QBasicStatements.h"
#include "QBasicStatementEntity.h"
#include "QBasicFunctions.h"
#include "QBasicFunctionEntity.h"
#include "QBasicFors.h"
#include "QBasicForEntity.h"
#include "QBasicIfs.h"
#include "QBasicIfEntity.h"

/**
 * コンストラクタ
 * @param interpreter　メイン
 */
QBasicCompile::QBasicCompile(QBasic *interpreter): QBasicBase(interpreter) {
}

/**
 * デストラクタ
 */
QBasicCompile::~QBasicCompile() {
}

/**
 * 単語が一致しているかをチェック
 * @param str 比較文字列
 */
void QBasicCompile::match(const string &str) {
	string sym = getSymbol();
	if (sym != str) {
		interpreter->errors->addError(ErrorType::MissingFound, QBasicErrors::buildMissingFound(str, sym));
	}
}

/**
 * and、or、xor判定
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasicCompile::expression(const bool run) {
	
	// 式の値取得
	auto value = relop(run);
	
	auto sym = getSymbol();
	while(true) {
		if (sym == "&&" ||
			sym == "||" ) {
			
			int offset = interpreter->symbols->offset();
			
			auto valueDist = relop(run);
			if (!QBasicValidation::isValidExpression(value, valueDist)) {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value.types, valueDist.types));
			}
			value = QBasicVariableEntity("", "true");
			
		} else {
			break;
		}
		sym = getSymbol();
	}
	pushBack(sym);
	
	return value;
}

/**
 * =、<、<=、>、>=、<>判定
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasicCompile::relop(const bool run) {
	
	// 足し算、引き算の値取得
	auto value = addsub(run);
	
	auto sym = getSymbol();
	while(true) {
		if (sym == "==" ||
			sym == "<" ||
			sym == "<=" ||
			sym == ">" ||
			sym == ">=" ||
			sym == "!=" ) {
			
			int offset = interpreter->symbols->offset();
			
			auto valueDist = addsub(run);
			if (!QBasicValidation::isValidVariableType(value, valueDist)) {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value.types, valueDist.types));
			}
			value.set(true);
		} else {
			break;
		}
		sym = getSymbol();
	}
	pushBack(sym);
	
	return value;
}

/**
 * 足し算、引き算、NOTの計算
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasicCompile::addsub(const bool run) {
	
	QBasicVariableEntity value;
	
	// 値取得
	auto sym = getSymbol();
	if (sym == "+") {
		value = muldiv(run);
	} else if(sym == "-") {
		int offset = interpreter->symbols->offset();
		value = muldiv(run);
		if (QBasicValidation::isValidSub(value)) {
			value = value.mul(value.types, -1);
		} else {
			interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int, VariableType::Float}, value));
		}
	} else if(sym == "!") {
		int offset = interpreter->symbols->offset();
		value = muldiv(run);
		if (QBasicValidation::isValidNot(value)) {
			value = !value;
		} else {
			interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Bool}, value));
		}
	} else {
		pushBack(sym);
		value = muldiv(run);
	}
	
	// 式実行
	sym = getSymbol();
	while (true) {
		if (sym == "+") {
			int offset = interpreter->symbols->offset();
			auto valueDist = muldiv(run);
			if (QBasicValidation::isValidAdd(value, valueDist)) {
				value = value + valueDist;
			} else {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value.types, valueDist.types));
			}
		} else if(sym == "-") {
			int offset = interpreter->symbols->offset();
			auto valueDist = muldiv(run);
			if (QBasicValidation::isValidSub(value, valueDist)) {
				value = value - valueDist;
			} else {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value.types, valueDist.types));
			}
		} else {
			break;
		}
		sym = getSymbol();
	}
	pushBack(sym);
	
	return value;
}

/**
 * 掛け算、割り算、あまりの計算
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasicCompile::muldiv(const bool run) {
	
	// 戻り値取得
	auto value = factor(run);
	
	string sym = getSymbol();
	while (true) {
		if (sym == "*") {
			int offset = interpreter->symbols->offset();
			auto valueDist = factor(run);
			if (QBasicValidation::isValidMul(value, valueDist)) {
				value = value * valueDist;
			} else {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value.types, valueDist.types));
			}
		} else if (sym == "/") {
			int offset = interpreter->symbols->offset();
			auto valueDist = factor(run);
			if (QBasicValidation::isValidDiv(value, valueDist)) {
				value = value / valueDist;
			} else {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value.types, valueDist.types));
			}
		} else if (sym == "%") {
			int offset = interpreter->symbols->offset();
			auto valueDist = factor(run);
			if (QBasicValidation::isValidMod(value, valueDist)) {
				value = value % valueDist;
			} else {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(value.types, valueDist.types));
			}
		} else {
			break;
		}
		sym = getSymbol();
	}
	pushBack(sym);
	
	return value;
}

/**
 * 戻り値の取得
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasicCompile::factor(const bool run) {
	
	string sym = getSymbol();
	
	if (interpreter->localVariables.find(sym) != interpreter->localVariables.end() ||
		interpreter->variables.find(sym) != interpreter->variables.end()) {
		auto operate = getSymbol();
		if (operate != "(") {
			pushBack(operate);
			auto variable = getVariable(run, sym);
			return *variable;
		}
		pushBack(operate);
	}
 
	if (sym.length() == 1) {
		switch (sym.c_str()[0]) {
			case '(': {
				auto value = expression(run);
				match(")");
				return value;
			}
			case '[': {
				auto value = listValue(run);
				return value;
			}
			case '{': {
				auto value = dictValue(run);
				return value;
			}
		}
	}
	
	// 数値ならば
	if (QBasicValidation::isFloat(sym)) {
		return QBasicVariableEntity("", sym);
	}
	
	// 文字ならば
	if (sym.find("\"") == 0) {
		return QBasicVariableEntity("", sym);
	}
	
	// bool値ならば
	if (sym == "true" || sym == "false") {
		return QBasicVariableEntity("", sym);
	}
	
	// nil値ならば
	if (sym == "nil") {
		return QBasicVariableEntity("", { VariableType::Unknown }, nullptr);
	}
	
	// ステートメント
	if (interpreter->statements->hasName(sym)) {
		auto value = executeStatement(run, sym, true);
		return value;
	}
	
	// ファンクション
	if (interpreter->functions->hasName(sym)) {
		return executeFunction(run, sym);
	}
	
	// 不明な文字が見つかりました。
	interpreter->errors->addError(ErrorType::UnknownSymbol, sym);
	
	return QBasicVariableEntity("", sym);
}

/**
 * 戻り値なし実行
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicCompile::statement(const bool run) {
	
	auto sym = getSymbol();
	
	// 終了
	if (sym.empty()) {
		return false;
	}
	
	if (interpreter->localVariables.find(sym) != interpreter->localVariables.end() ||
		interpreter->variables.find(sym) != interpreter->variables.end()) {
		auto operate = getSymbol();
		if (operate != "(") {
			pushBack(operate);
			return analysisValueAssigned(run, sym);
		}
		pushBack(operate);
	}
	if (sym == "var") {
		return analysisVar(run);
	}
	if (sym == "if") {
		return analysisIf(run);
	}
	if (sym == "for") {
		return analysisFor(run);
	}
	if (sym == "break") {
		return true;
	}
	if (sym == "continue") {
		return true;
	}
	if (sym == "func") {
		return analysisFunc(run);
	}
	if (sym == "return") {
		return analysisReturn(run);
	}
	if (sym == "endfunc") {
		return analysisEndfunc(run);
	}
	if (sym == "exit") {
		return true;
	}
	if (sym == "pass") {
		return true;
	}
	if (interpreter->statements->hasName(sym)) {
		// ステートメント
		executeStatement(run, sym, false);
		return true;
	}
	if (interpreter->functions->hasName(sym)) {
		// ファンクション
		executeFunction(run, sym);
		return true;
	}
	if (sym.c_str()[0] == '#') {
		// コメント
		return true;
	}
 
	pushBack(sym);
	expression(run);
	
	return true;
}

/**
 * dict型の取得
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasicCompile::dictValue(const bool run) {
	QBasicVariableEntity returnValue;
	returnValue.types = { VariableType::Dict };
	// 上位で"{"のチェックがされる
	int count = 0;
	while (true) {
		auto sym = getSymbol();
		if (sym == "}" || sym.empty()) {
			break;
		}
		interpreter->symbols->popBack();
		if (count > 0) {
			match(",");
		}
		int offset = interpreter->symbols->offset();
		auto keyValue = expression(run);
		if (keyValue.types[0] != VariableType::Str) {
			interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Str}, keyValue));
		}
		match(":");
		QBasicVariableEntity value;
		sym = getSymbol();
		if (sym == "[") {
			value = listValue(run);
		} else if(sym == "{") {
			value = dictValue(run);
		} else {
			interpreter->symbols->popBack();
			value = expression(run);
		}
		returnValue.dictValue[keyValue.strValue] = value;
		count += 1;
	}
	returnValue.isNil = false;
	returnValue.types = QBasicVariableEntity::getVariableTypes(returnValue);
	return returnValue;
}

/**
 * 変数取得
 * @param name 変数名
 * @param run  実行中フラグ
 * @return 変数取得
 */
QBasicVariableEntity *QBasicCompile::getVariable(const bool run, const string &name) {
	
	// 変数があるかどうかは上位でチェックしている
	QBasicVariableEntity *parentVariable;
	if (interpreter->localVariables.find(name) != interpreter->localVariables.end()) {
		// ローカル
		parentVariable = &interpreter->localVariables[name];
	} else {
		// グローバル
		parentVariable = &interpreter->variables[name];
	}
	int count = 1;
	QBasicVariableEntity *variable = parentVariable;
	while (true) {
		if (variable->types[0] != VariableType::List &&
			variable->types[0] != VariableType::Dict) {
			break;
		}
		
		auto sym = getSymbol();
		if (sym != "[") {
			interpreter->symbols->popBack();
			break;
		}
		if (sym.empty()) {
			break;
		}
		
		int offset = interpreter->symbols->offset();
		
		auto keyValue = expression(run);
		match("]");
		
		if (variable->types[0] == VariableType::List) {
			if (keyValue.types[0] != VariableType::Int) {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int}, keyValue));
				return nullptr;
			}
			if (variable->listValue.size() <= 0) {
				variable->listValue.push_back(QBasicVariableEntity("", { parentVariable->types[count] }, nullptr));
			}
			variable = &variable->listValue[0];
			count += 1;
		} else {
			if (keyValue.types[0] != VariableType::Str) {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Str}, keyValue));
				return nullptr;
			}
			if (variable->dictValue.size() <= 0) {
				variable->dictValue[""] = QBasicVariableEntity("", { parentVariable->types[count] }, nullptr);
			}
			variable = &variable->dictValue.begin()->second;
			count += 1;
		}
	}
	
	return variable;
}

/**
 * ステートメント実行
 * @param run              実行中フラグ
 * @param functionName     関数名
 * @param needsReturnValue 戻り値
 * @return 戻り値
 */
QBasicVariableEntity QBasicCompile::executeStatement(const bool run, const string &functionName, const bool needsReturnValue) {
	int offset = interpreter->symbols->offset() - 1;
	
	// 引数取得
	auto argList = getArguments(run);
	// 省略引数とマージ
	argList = interpreter->statements->mergeArguments(functionName, argList);
	
	auto entity = interpreter->statements->getStatement(functionName, argList);
	
	// 該当のステートメントなし
	if (entity == nullptr) {
		interpreter->errors->addError(offset, ErrorType::UnknownFunction, functionName);
		return QBasicVariableEntity();
	}
	// 戻り値がvoid
	if (needsReturnValue && entity->returnTypes[0] == VariableType::Void) {
		interpreter->errors->addError(offset, ErrorType::ReturnTypeVoid, entity->alias);
		return QBasicVariableEntity();
	}
	
	// コンパイルファンクションが定義されていたらそちらを実行。
	if (entity->compileFunc != nullptr) {
		entity->compileFunc(interpreter, argList, offset);
	}
	
	return QBasicVariableEntity("", entity->returnTypes, nullptr);
}

/**
 * func実行
 * @param run            実行中フラグ
 * @param functionName   関数名
 * @return 戻り値
 */
QBasicVariableEntity QBasicCompile::executeFunction(const bool run, const string &functionName) {
	
	int offset = interpreter->symbols->offset() - 1;
	
	// 引数取得
	auto argList = getArguments(run);
	// 省略引数とマージ
	argList = interpreter->functions->mergeArguments(functionName, argList);
	
	// 関数エリアス取得
	auto entity = interpreter->functions->getFunction(functionName, argList);
	
	if (entity == nullptr) {
		interpreter->errors->addError(offset, ErrorType::UnknownFunction, functionName);
		return QBasicVariableEntity("", { VariableType::Void }, nullptr);
	}
	return QBasicVariableEntity("", entity->returnTypes, nullptr);
}

/**
 * 変数に代入
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicCompile::analysisValueAssigned(const bool run, const string &variableName) {
	
	// 変数取得
	auto variable = getVariable(run, variableName);
	if (variable == nullptr) {
		return false;
	}
	// 記号
	int operateOffset = interpreter->symbols->offset();
	auto operate = getSymbol();
	// 変数
	int valueOffset = interpreter->symbols->offset();
	auto value = expression(run);
	value.types = QBasicVariableEntity::getVariableTypes(value);
	if (!QBasicValidation::isValidVariableType(value, variable->types)) {
		interpreter->errors->addError(valueOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({variable->types[0]}, value));
	}
	if (operate == "+=") {
		if (!QBasicValidation::isValidAdd(*variable, value)) {
			interpreter->errors->addError(operateOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int, VariableType::Float, VariableType::Str}, value));
		}
	} else if (operate == "-=") {
		if (!QBasicValidation::isValidSub(*variable, value)) {
			interpreter->errors->addError(operateOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int, VariableType::Float}, value));
		}
	} else if (operate == "*=") {
		if (!QBasicValidation::isValidMul(*variable, value)) {
			interpreter->errors->addError(operateOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int, VariableType::Float}, value));
		}
	} else if (operate == "/=") {
		if (!QBasicValidation::isValidDiv(*variable, value)) {
			interpreter->errors->addError(operateOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int, VariableType::Float}, value));
		}
	} else if (operate == "%=") {
		if (!QBasicValidation::isValidMod(*variable, value)) {
			interpreter->errors->addError(operateOffset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int}, value));
		}
	} else if (operate != "=") {
		interpreter->errors->addError(operateOffset, ErrorType::UnknownSymbol, operate);
	}
	return true;
}

/**
 * 変数を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicCompile::analysisVar(const bool run) {
	// 変数宣言
	int variableOffset = interpreter->symbols->offset();
	auto variableName = getSymbol();
	
	// 名前が不適切
	if (!QBasicValidation::isValidVariableName(variableName)) {
		interpreter->errors->addError(variableOffset, ErrorType::BadVariableName, variableName);
	}
	if (!lastFunctionName.empty()) {
		// func内の宣言ならばローカル変数
		if (interpreter->localVariables.find(variableName) != interpreter->localVariables.end()) {
			interpreter->errors->addError(variableOffset, ErrorType::OverlapVariableName, variableName);
		}
	} else {
		// すでに宣言済み
		if (interpreter->variables.find(variableName) != interpreter->variables.end()) {
			interpreter->errors->addError(variableOffset, ErrorType::OverlapVariableName, variableName);
		}
	}

	auto sym = getSymbol();
	
	vector<VariableType> variableTypes = { VariableType::Unknown };
	if (sym == ":") {
		// 型をチェック
		int offset = interpreter->symbols->offset();
		sym = getSymbol();
		variableTypes[0] = QBasicVariableEntity::getVariableType(sym);
		if (variableTypes[0] == VariableType::Void ||
			variableTypes[0] == VariableType::Unknown) {
			interpreter->errors->addError(offset, ErrorType::UnknownSymbol, sym);
		}
		if (variableTypes[0] == VariableType::List ||
			variableTypes[0] == VariableType::Dict ) {
			// 配列の場合は型の宣言が必要
			analysisVarListDict(run, variableName, variableTypes);
		}
		
		// 次を取得
		sym = getSymbol();
	}
	
	// 初期値設定されているか
	if (sym != "=") {
		if (!run && variableTypes[0] == VariableType::Unknown) {
			interpreter->errors->addError(variableOffset, ErrorType::BadVariableType, variableName);
		}
		if (!sym.empty()) {
			interpreter->symbols->popBack();
		}
		QBasicVariableEntity variableEntity;
		switch (variableTypes[0]) {
			case VariableType::List:
				variableEntity = QBasicVariableEntity(variableName, variableTypes, vector<QBasicVariableEntity>());
				break;
			case VariableType::Dict:
				variableEntity = QBasicVariableEntity(variableName, variableTypes, map<string, QBasicVariableEntity>());
				break;
			default:
				variableEntity = QBasicVariableEntity(variableName, variableTypes, nullptr);
				break;
		}
		if (!lastFunctionName.empty()) {
			interpreter->localVariables[variableName] = variableEntity;
		} else {
			interpreter->variables[variableName] = variableEntity;
		}
		return true;
	}
	
	// 初期値取得
	int offset = interpreter->symbols->offset();
	auto value = expression(run);
	if (variableTypes[0] != VariableType::Unknown) {
		if (!QBasicValidation::isValidVariableType(value, variableTypes)) {
			interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(variableTypes, value));
		}
	} else {
		value.types = QBasicVariableEntity::getVariableTypes(value);
	}
	
	value.name = variableName;
	if (!lastFunctionName.empty()) {
		interpreter->localVariables[variableName] = value;
	} else {
		interpreter->variables[variableName] = value;
	}
	
	return true;
}

/**
 * 変数を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicCompile::analysisVarListDict(const bool run, const string &variableName, vector<VariableType> &valueVariableTypes) {
	// リストの場合は型の宣言が必要
	while(true) {
		match("<");
		int offset = interpreter->symbols->offset();
		auto sym = getSymbol();
		auto valueVariableType = QBasicVariableEntity::getVariableType(sym);
		if (valueVariableType == VariableType::Void ||
			valueVariableType == VariableType::Unknown) {
			interpreter->errors->addError(offset, ErrorType::UnknownSymbol, sym);
		}
		valueVariableTypes.push_back(valueVariableType);
		if (valueVariableType != VariableType::List && valueVariableType != VariableType::Dict) {
			break;
		}
	}
	for (auto i = 0;i < valueVariableTypes.size() - 1;i++) {
		match(">");
	}
	return true;
}

/**
 * if文を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicCompile::analysisIf(const bool run) {
	
	int ifKey = interpreter->symbols->offset();
	int startOffset = ifKey;
	bool isElse = false;
	
	// if文
	auto value = expression(run);
	if (!QBasicValidation::isValidIf(value)) {
		interpreter->errors->addError(ifKey, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Bool}, value));
	}
	if (!statement(run)) {
		return false;
	}
	while (true) {
		int offset = interpreter->symbols->offset();
		auto sym = getSymbol();
		if (sym.empty()) {
			interpreter->errors->addError(ErrorType::NothingEndif, "");
			break;
		}
		if (sym == "endif") {
			interpreter->ifs->add(ifKey, startOffset, interpreter->symbols->offset());
			break;
		} else if(sym == "elseif") {
			if (isElse) {
				interpreter->errors->addError(offset, ErrorType::BadElseif, "");
			}
			interpreter->ifs->add(ifKey, startOffset, interpreter->symbols->offset() - 2);
			startOffset = interpreter->symbols->offset() - 1;
			int offset = interpreter->symbols->offset();
			auto value = expression(run);
			if (!QBasicValidation::isValidIf(value)) {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Bool}, value));
			}
			if (!statement(run)) {
				break;
			}
		} else if(sym == "else") {
			if (isElse) {
				interpreter->errors->addError(offset, ErrorType::BadElse, "");
			}
			interpreter->ifs->add(ifKey, startOffset, interpreter->symbols->offset() - 2);
			startOffset = interpreter->symbols->offset() - 1;
			if (!statement(run)) {
				break;
			}
			// フラグON
			isElse = true;
		} else {
			pushBack(sym);
			if (!statement(run)) {
				break;
			}
		}
	}
	return true;
}

/**
 * for文を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicCompile::analysisFor(const bool run) {
	
	int offset = interpreter->symbols->offset();
	string variableName = getSymbol();
	QBasicVariableEntity *valueEntity = getVariable(run, variableName);
	
	if (valueEntity == nullptr) {
		interpreter->errors->addError(offset, ErrorType::UnknownVariable, variableName);
	} else {
		if (!QBasicValidation::isValidFor(interpreter->variables[variableName])) {
			interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int}, *valueEntity));
		}
	}

	match("=");
	
	offset = interpreter->symbols->offset();
	auto value = expression(run);
	if (!QBasicValidation::isValidFor(value)) {
		interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int}, value));
	}
	
	match("to");
	
	offset = interpreter->symbols->offset();
	value = expression(run);
	if (!QBasicValidation::isValidFor(value)) {
		interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int}, value));
	}
	
	auto sym = getSymbol();
	if (sym == "step") {
		value = expression(run);
		if (!QBasicValidation::isValidFor(value)) {
			interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType({VariableType::Int}, value));
		}
	} else {
		interpreter->symbols->popBack();
	}
	
	int startOffset = interpreter->symbols->offset();
	
	int pcfor = interpreter->symbols->offset();
	string pushbackfor = pushBacked;
	
	for (int i = 0;i < 1;i++) {
		interpreter->symbols->jumpOffset(pcfor);
		pushBacked = pushbackfor;
		
		while (true) {
			sym = getSymbol();
			if (sym.empty()) {
				interpreter->errors->addError(ErrorType::NothingNext, "");
				break;
			}
			if (sym == "next") {
				// forに追加
				interpreter->fors->addUpdate(startOffset, interpreter->symbols->offset() - 1);
				break;
			}
			pushBack(sym);
			if (!statement(false)) {
				break;
			}
		}
	}
	
	return true;
}

/**
 * 関数を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicCompile::analysisFunc(const bool run) {
	
	int offset = interpreter->symbols->offset();
	
	// func内にfuncを定義
	if (!lastFunctionName.empty()) {
		interpreter->errors->addError(offset, ErrorType::FunctionOverFunction, lastFunctionName);
	}
	
	// 関数名取得
	auto functionName = getSymbol();
	
	// 名前が不適切
	if (!QBasicValidation::isValidFunctionName(functionName)) {
		interpreter->errors->addError(offset, ErrorType::BadVariableName, functionName);
	}

	// 引数を解析
	vector<QBasicVariableEntity> argNames;
	bool isSuccess = analysisArguments(run, argNames);
	if (!isSuccess) {
		return false;
	}
	
	// function取得
	auto entity = interpreter->functions->getFunction(functionName, argNames);
	
	// すでに宣言済み
	if (entity != nullptr) {
		interpreter->errors->addError(offset, ErrorType::OverlapFunctionName, lastFunctionName);
	}
	
	// 戻り値タイプを解析
	auto sym = getSymbol();
	vector<VariableType> returnTypes = { VariableType::Unknown };
	if (sym != ":") {
		// 引数省略
		returnTypes[0] = VariableType::Void;
		// オフセットを戻す
		if (!sym.empty()) {
			interpreter->symbols->popBack();
		}
	} else {
		string returnVariableName = getSymbol();
		returnTypes[0] = QBasicVariableEntity::getVariableType(returnVariableName);
		if (returnTypes[0] == VariableType::Unknown) {
			interpreter->errors->addError(offset, ErrorType::BadVariableType, returnVariableName);
		}
		if (returnTypes[0] == VariableType::List ||
			returnTypes[0] == VariableType::Dict ) {
			// 配列の場合は型の宣言が必要
			analysisVarListDict(run, "", returnTypes);
		}
	}
	
	// ファンクション追加
	entity = interpreter->functions->addUpdate(functionName, argNames, returnTypes, interpreter->symbols->offset(), 0);
	
	// 最後の関数名を退避
	lastFunctionName = entity->alias;
	// ローカル変数に引数を設定する
	interpreter->localVariables.clear();
	for (auto it = argNames.begin();it != argNames.end();it++) {
		interpreter->localVariables[it->name] = *it;
	}
	
	// 初期化
	hasReturnSymbol = false;
	
	return true;
}

/**
 * 引数を解析
 * @param argNames 出力引数
 * @param run      実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicCompile::analysisArguments(const bool run, vector<QBasicVariableEntity> &argNames) {
	
	// 引数を解析
	match("(");
	while(true) {
		int offset = interpreter->symbols->offset();
		auto variableName = getSymbol();
		if (variableName.empty()) {
			break;
		}
		if (variableName == ")") {
			// 終了
			break;
		}
		if (argNames.size() > 0) {
			interpreter->symbols->popBack();
			match(",");
			variableName = getSymbol();
		}
		
		// 変数名が不正
		if (!QBasicValidation::isValidVariableName(variableName)) {
			interpreter->errors->addError(offset, ErrorType::BadVariableName, variableName);
		}
		for (auto it = argNames.begin();it != argNames.end();it++) {
			if (it->name == variableName) {
				interpreter->errors->addError(offset, ErrorType::OverlapVariableName, variableName);
			}
		}
	
		vector<VariableType> variableTypes = { VariableType::Unknown };
		auto sym = getSymbol();
		if (sym == ":") {
			// 型指定へ
			int offset = interpreter->symbols->offset();
			sym = getSymbol();
			variableTypes[0] = QBasicVariableEntity::getVariableType(sym);
			if (variableTypes[0] == VariableType::Void ||
				variableTypes[0] == VariableType::Unknown) {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, sym);
			}
			if (variableTypes[0] == VariableType::List ||
				variableTypes[0] == VariableType::Dict ) {
				// 配列の場合は型の宣言が必要
				analysisVarListDict(run, variableName, variableTypes);
			}
			
			// 次を取得
			sym = getSymbol();
		}
		
		QBasicVariableEntity variableEntity;
		if (sym != "=") {
			if (variableTypes[0] == VariableType::Unknown) {
				interpreter->errors->addError(offset, ErrorType::BadVariableType, variableName);
			}
			if (!sym.empty()) {
				interpreter->symbols->popBack();
			}
			variableEntity.name = variableName;
			variableEntity.types = variableTypes;
		} else {
			// デフォルト値指定へ
			int offset = interpreter->symbols->offset();
			QBasicVariableEntity value = expression(run);
			if (variableTypes[0] != VariableType::Unknown) {
				// 型が一致するかをチェック
				if (!QBasicValidation::isValidVariableType(value, variableTypes)) {
					interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(variableTypes, value));
				}
			}
			variableEntity = value;
			variableEntity.name = variableName;
		}
		
		argNames.push_back(variableEntity);
	}
	
	return true;
}

/**
 * returnを解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicCompile::analysisReturn(const bool run) {
	auto entity = (*(interpreter->functions))[lastFunctionName];
	if (entity == nullptr) {
		return true;
	}
	// 終了オフセットを退避
	if (entity->returnTypes[0] == VariableType::Void) {
		return true;
	}
	// 戻り値取得
	int offset = interpreter->symbols->offset();
	auto value = expression(run);
	if (!QBasicValidation::isValidVariableType(value, entity->returnTypes)) {
		interpreter->errors->addError(offset, ErrorType::BadVariableType, QBasicErrors::buildBadVariableType(entity->returnTypes, value));
	}
	hasReturnSymbol = true;
	return true;
}

/**
 * endfuncを解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicCompile::analysisEndfunc(const bool run) {
	auto entity = (*(interpreter->functions))[lastFunctionName];
	if (entity == nullptr) {
		return true;
	}
	if (entity->returnTypes[0] != VariableType::Void && !hasReturnSymbol) {
		interpreter->errors->addError(ErrorType::NothingReturnValue, "");
	}
	// 終了オフセットを退避
	entity->endOffset = interpreter->symbols->offset();
	// 最後の関数名をクリア
	lastFunctionName = "";
	interpreter->localVariables.clear();
	return true;
}
