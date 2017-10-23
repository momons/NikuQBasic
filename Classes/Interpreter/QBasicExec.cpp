//
//  QBasicExec.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/07.
//
//

#include "QBasicExec.h"

#include "QBasic.h"
#include "QBasicSymbols.h"
#include "QBasicVariableEntity.h"
#include "QBasicErrors.h"
#include "QBasicErrorEntity.h"
#include "QBasicStatements.h"
#include "QBasicStatementEntity.h"
#include "QBasicFunctions.h"
#include "QBasicFunctionEntity.h"
#include "QBasicPushBackEntity.h"
#include "QBasicValidation.h"
#include "QBasicFors.h"
#include "QBasicForEntity.h"
#include "QBasicIfs.h"
#include "QBasicIfEntity.h"

/** 関数返却変数名 */
#define FUNCTION_RETURN_VARIABLE_NAME  "__return_variable__"

/**
 * コンストラクタ
 * @param interpreter　メイン
 */
QBasicExec::QBasicExec(QBasic *interpreter): QBasicBase(interpreter) {
	isExit = false;
	isBreak = false;
	isContinue = false;
	functionPushBacks.clear();
}

/**
 * デストラクタ
 */
QBasicExec::~QBasicExec() {
	
}

/**
 * 単語が一致しているかをチェック
 * @param str 比較文字列
 */
void QBasicExec::match(const string &str) {
	getSymbol();
}

/**
 * and、or、xor判定
 * @param run 実行中フラグ
 * @return 値
 */
QBasicVariableEntity QBasicExec::expression(const bool run) {
	
	// 式の値取得
	auto value = relop(run);
	
	auto sym = getSymbol();
	while(true) {
		if (sym == "&&" ||
			sym == "||" ) {
			
			auto valueDist = relop(run);
			if (sym == "&&") {
				value = value && valueDist;
			} else {
				value = value || valueDist;
			}
			
		} else if (sym == "?") {
			
			auto value1 = expression(run);
			match(":");
			auto value2 = expression(run);
			
			value = value.boolValue ? value1 : value2;
			
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
QBasicVariableEntity QBasicExec::relop(const bool run) {
	
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
			
			auto valueDist = addsub(run);
			bool boolValue = ((sym == "==" && value == valueDist) ||
							  (sym == "<" && value < valueDist) ||
							  (sym == "<=" && value <= valueDist) ||
							  (sym == ">" && value > valueDist) ||
							  (sym == ">=" && value >= valueDist) ||
							  (sym == "!=" && value != valueDist));
			value.set(boolValue);
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
QBasicVariableEntity QBasicExec::addsub(const bool run) {
	
	QBasicVariableEntity value;
	
	// 値取得
	auto sym = getSymbol();
	if (sym == "+") {
		value = muldiv(run);
	} else if(sym == "-") {
		value = muldiv(run);
		value = value.mul(value.types, -1);
	} else if(sym == "!") {
		value = muldiv(run);
		value = !value;
	} else {
		pushBack(sym);
		value = muldiv(run);
	}
	
	// 式実行
	sym = getSymbol();
	while (true) {
		if (sym == "+") {
			auto valueDist = muldiv(run);
			value = value + valueDist;
		} else if(sym == "-") {
			auto valueDist = muldiv(run);
			value = value - valueDist;
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
QBasicVariableEntity QBasicExec::muldiv(const bool run) {
	
	// 戻り値取得
	auto value = factor(run);
	
	string sym = getSymbol();
	while (true) {
		if (sym == "*") {
			auto valueDist = factor(run);
			value = value * valueDist;
		} else if (sym == "/") {
			auto valueDist = factor(run);
			value = value / valueDist;
		} else if (sym == "%") {
			auto valueDist = factor(run);
			value = value % valueDist;
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
QBasicVariableEntity QBasicExec::factor(const bool run) {
	
	string sym = getSymbol();
	
	if (interpreter->localVariables.find(sym) != interpreter->localVariables.end() ||
		interpreter->variables.find(sym) != interpreter->variables.end()) {
		auto operate = getSymbol();
		pushBack(operate);
		if (operate != "(") {
			auto variable = getVariable(run, sym);
			return *variable;
		}
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
	
	return QBasicVariableEntity("", sym);
}

/**
 * 戻り値なし実行
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicExec::statement(const bool run) {
	
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
	if (sym == "var" || sym == "let") {
		return analysisVar(run, sym == "let");
	}
	if (sym == "if") {
		return analysisIf(run);
	}
	if (sym == "for") {
		return analysisFor(run);
	}
	if (sym == "break") {
		// TODO: ループ内ではないときの対応を入れる
		isBreak = true;
		return false;
	}
	if (sym == "continue") {
		// TODO: ループ内ではないときの対応を入れる
		isContinue = true;
		return false;
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
		isExit = true;
		return false;
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
QBasicVariableEntity QBasicExec::dictValue(const bool run) {
	QBasicVariableEntity returnValue;
	returnValue.types = { VariableType::Dict };
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
		auto keyValue = expression(run);
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
QBasicVariableEntity *QBasicExec::getVariable(const bool run, const string &name) {
	
	// 変数があるかどうかは上位でチェックしている
	QBasicVariableEntity *parentVariable;
	if (interpreter->localVariables.find(name) != interpreter->localVariables.end()) {
		// ローカル
		parentVariable = &interpreter->localVariables[name];
	} else {
		// グローバル
		parentVariable = &interpreter->variables[name];
	}
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
			if (keyValue.intValue < 0 || keyValue.intValue >= variable->listValue.size()) {
				interpreter->errors->setThrow(offset, ErrorType::ListIndexOutOfBounds, QBasicErrors::buildListIndexOutOfBounds(0, (int)variable->listValue.size() - 1, keyValue.intValue));
				return nullptr;
			}
			variable = &variable->listValue[keyValue.intValue];
		} else {
			if (variable->dictValue.find(keyValue.strValue) == variable->dictValue.end()) {
				interpreter->errors->setThrow(offset, ErrorType::DictUnknownKey, keyValue.strValue);
				return nullptr;
			}
			variable = &variable->dictValue[keyValue.strValue];
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
QBasicVariableEntity QBasicExec::executeStatement(const bool run, const string &functionName, const bool needsReturnValue) {
	// 引数取得
	auto argList = getArguments(run);
	// 省略引数とマージ
	argList = interpreter->statements->mergeArguments(functionName, argList);
	
	auto entity = interpreter->statements->getStatement(functionName, argList);
	
	return entity->execFunc(interpreter, argList);
}

/**
 * func実行
 * @param run            実行中フラグ
 * @param functionName   関数名
 * @return 戻り値
 */
QBasicVariableEntity QBasicExec::executeFunction(const bool run, const string &functionName) {
	
	// 引数取得
	auto argList = getArguments(run);
	// 省略引数とマージ
	argList = interpreter->functions->mergeArguments(functionName, argList);
	
	// 関数エリアス取得
	auto entity = interpreter->functions->getFunction(functionName, argList);
	
	// ローカル変数に行数とプッシュバック変数を退避
	auto pushBackEntity = QBasicPushBackEntity(lastFunctionName, pushBacked, interpreter->symbols->offset(), interpreter->localVariables);
	functionPushBacks.push_back(pushBackEntity);
	
	// 実行オフセットを設定
	lastFunctionName = entity->alias;
	interpreter->symbols->jumpOffset(entity->startOffset);
	
	// 情報クリア
	pushBacked.clear();
	interpreter->localVariables.clear();
	
	// ローカル変数に引数を設定する
	for (auto it = argList.begin();it != argList.end();it++) {
		interpreter->localVariables[it->name] = *it;
	}
	
	// 実行
	while(true) {
		bool isExecute = statement(run);
		if (!isExecute || isExit) {
			break;
		}
	}
	
	// 戻り値が設定されているので返却
	if (interpreter->variables.find(FUNCTION_RETURN_VARIABLE_NAME) != interpreter->variables.end()) {
		return interpreter->variables[FUNCTION_RETURN_VARIABLE_NAME];
	} else {
		return QBasicVariableEntity("", { VariableType::Unknown }, nullptr);
	}
}

/**
 * func終了実行
 * @param run          実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicExec::executeFunctionEnd(const bool run) {
	// 関数内ではない
	if (functionPushBacks.size() <= 0) {
		return false;
	}
	// 退避していたものを戻す
	QBasicPushBackEntity entity = *(functionPushBacks.end() - 1);
	lastFunctionName = entity.name;
	pushBacked = entity.symbol;
	interpreter->symbols->jumpOffset(entity.execOffset);
	interpreter->localVariables.clear();
	interpreter->localVariables = entity.localVariables;
	// 削除
	functionPushBacks.pop_back();
	return true;
}

/**
 * 変数に代入
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicExec::analysisValueAssigned(const bool run, const string &variableName) {
	
	// 変数取得
	auto variable = getVariable(run, variableName);
	if (variable == nullptr) {
		return false;
	}
	// 記号
	auto operate = getSymbol();
	// 変数
	auto value = expression(run);
	value.types = QBasicVariableEntity::getVariableTypes(value);
	if (operate == "+=") {
		value = *variable + value;
	} else if (operate == "-=") {
		value = *variable - value;
	} else if (operate == "*=") {
		value = *variable * value;
	} else if (operate == "/=") {
		value = *variable / value;
	} else if (operate == "%=") {
		value = *variable % value;
	}
	variable->set(value);
	
	return true;
}

/**
 * 変数を解析
 * @param run     実行中フラグ
 * @param isConst 定数フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicExec::analysisVar(const bool run, const bool isConst) {
	
	// 変数宣言
	auto variableName = getSymbol();
	
	auto sym = getSymbol();
	
	vector<VariableType> variableTypes = { VariableType::Unknown };
	if (sym == ":") {
		// 型をチェック
		sym = getSymbol();
		variableTypes[0] = QBasicVariableEntity::getVariableType(sym);
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
	auto value = expression(run);
	value.name = variableName;
	if (isConst) {
		value.setConst(true);
	}
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
bool QBasicExec::analysisVarListDict(const bool run, const string &variableName, vector<VariableType> &valueVariableTypes) {
	// リストの場合は型の宣言が必要
	while(true) {
		match("<");
		auto sym = getSymbol();
		auto valueVariableType = QBasicVariableEntity::getVariableType(sym);
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
bool QBasicExec::analysisIf(const bool run) {
	
	int ifKey = interpreter->symbols->offset();
	int ifIndex = 0;
	bool isElse = false;
	bool isSuccess = false;
	
	// if文
	auto value = expression(run);
	if (!value.boolValue) {
		ifIndex += 1;
		if (!jumpIf(ifKey, ifIndex)) {
			return true;
		}
	} else {
		isSuccess = true;
	}
	while (true) {
		if (isBreak || isContinue) {
			// ループを抜ける
			jumpIf(ifKey, -1);
			break;
		}
		auto sym = getSymbol();
		if (sym == "endif") {
			// ループを抜ける
			jumpIf(ifKey, -1);
			break;
		} else if(sym == "elseif") {
			if (isSuccess) {
				jumpIf(ifKey, -1);
				break;
			}
			auto value = expression(run);
			if (!value.boolValue) {
				ifIndex += 1;
				if (!jumpIf(ifKey, ifIndex)) {
					break;
				}
			} else {
				isSuccess = true;
				if (!statement(run)) {
					break;
				}
				jumpIf(ifKey, -1);
				break;
			}
		} else if(sym == "else") {
			if (isSuccess) {
				jumpIf(ifKey, -1);
				break;
			}
			isSuccess = true;
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
	return !isExit;
}



/**
 * 次のif分へ
 * @param key   キー
 * @param index インデックス
 * @return 終了フラグ false:もうなし true:次へ
 */
bool QBasicExec::jumpIf(const int key, const int index) {
	pushBacked = "";
	auto ifEntities = (*interpreter->ifs)[key];
	if (ifEntities == nullptr) {
		return false;
	}
	if (index < 0 || index >= ifEntities->size()) {
		// もう次がない
		interpreter->symbols->jumpOffset((ifEntities->end() - 1)->endOffset);
		return false;
	}
	interpreter->symbols->jumpOffset(ifEntities->at(index).startOffset);
	return true;
}

/**
 * for文を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicExec::analysisFor(const bool run) {
	
	string variableName = getSymbol();
	QBasicVariableEntity *valueEntity = getVariable(run, variableName);
	
	match("=");
	
	auto value = expression(run);
	
	valueEntity->set(value.intValue);
	
	int from = valueEntity->intValue;
	
	match("to");
	
	value = expression(run);
	
	int to = value.intValue;
	
	bool isUpLoop = true;
	int step = 0;
	auto sym = getSymbol();
	if (sym == "step") {
		value = expression(run);
		step = value.intValue;
		isUpLoop = step >= 0 ? true : false;
	} else {
		interpreter->symbols->popBack();
		if (from <= to) {
			step = 1;
		} else {
			step = -1;
			isUpLoop = false;
		}
	}
	
	int startOffset = interpreter->symbols->offset();
	
	int count = 0;
	int pcfor = interpreter->symbols->offset();
	string pushbackfor = pushBacked;
	isBreak = false;
	isContinue = false;
	while ((isUpLoop && valueEntity->intValue <= to) ||
		   (!isUpLoop && valueEntity->intValue >= to)) {
		
		interpreter->symbols->jumpOffset(pcfor);
		pushBacked = pushbackfor;
		
		while (true) {
			sym = getSymbol();
			if (sym == "next") {
				break;
			}
			pushBack(sym);
			if (!statement(!isContinue)) {
				if (isExit) {
					return false;
				}
				break;
			}
			if (isBreak || isContinue) {
				break;
			}
		}
		
		// カウント加算
		count++;
		
		isContinue = false;
		
		if (isBreak) {
			isBreak = false;
			break;
		}
		
		valueEntity->intValue += step;
	}
	
	// 次の処理まで飛ばす
	auto forEntity = (*interpreter->fors)[startOffset];
	interpreter->symbols->jumpOffset(forEntity->endOffset + 1);
	
	return true;
}

/**
 * 関数を解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicExec::analysisFunc(const bool run) {
	
	// 関数名取得
	auto functionName = getSymbol();
	
	// 引数を解析
	vector<QBasicVariableEntity> argNames;
	bool isSuccess = analysisArguments(run, argNames);
	if (!isSuccess) {
		return false;
	}
	
	// function取得
	auto entity = interpreter->functions->getFunction(functionName, argNames);
	
	// 実行中ならば、endまで処理を飛ばす
	interpreter->symbols->jumpOffset(entity->endOffset);
	
	return true;
}

/**
 * 引数を解析
 * @param argNames 出力引数
 * @param run      実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicExec::analysisArguments(const bool run, vector<QBasicVariableEntity> &argNames) {
	
	// 引数を解析
	match("(");
	while(true) {
		auto variableName = getSymbol();
		if (variableName == ")" || variableName.empty()) {
			// 終了
			break;
		}
		if (argNames.size() > 0) {
			interpreter->symbols->popBack();
			match(",");
			variableName = getSymbol();
		}
		
		vector<VariableType> variableTypes = { VariableType::Unknown };
		auto sym = getSymbol();
		if (sym == ":") {
			// 型指定へ
			sym = getSymbol();
			variableTypes[0] = QBasicVariableEntity::getVariableType(sym);
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
			if (!sym.empty()) {
				interpreter->symbols->popBack();
			}
			variableEntity.name = variableName;
			variableEntity.types = variableTypes;
		} else {
			// デフォルト値指定へ
			QBasicVariableEntity value = expression(run);
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
bool QBasicExec::analysisReturn(const bool run) {
	auto entity = (*(interpreter->functions))[lastFunctionName];
	// 終了オフセットを退避
	if (entity->returnTypes[0] == VariableType::Void) {
		executeFunctionEnd(run);
		return false;
	}
	// 戻り値取得
	auto value = expression(run);

	executeFunctionEnd(run);
	// 値をグローバル変数に設定
	interpreter->variables[FUNCTION_RETURN_VARIABLE_NAME] = value;
	
	return false;
}

/**
 * endfuncを解析
 * @param run 実行中フラグ
 * @return 終了フラグ false:終了 true:進行
 */
bool QBasicExec::analysisEndfunc(const bool run) {
	auto entity = (*(interpreter->functions))[lastFunctionName];

	// 戻り値あるはずがない
	if (entity->returnTypes[0] != VariableType::Void) {
		interpreter->errors->setThrow(interpreter->symbols->offset() - 1, ErrorType::NothingReturnValue, "");
		return false;
	}
	executeFunctionEnd(run);
	
	// 終了
	return false;
}
