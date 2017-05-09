//
//  QBasicFunctions.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/28.
//
//

#include "QBasicFunctions.h"

#include "QBasicFunctionEntity.h"
#include "QBasicVariableEntity.h"

/**
 * コンストラクタ
 */
QBasicFunctions::QBasicFunctions() {
	functions.clear();
}

/**
 * デストラクタ
 */
QBasicFunctions::~QBasicFunctions() {
	
}

/**
 * 関数追加
 * @param name           関数名
 * @param variableTypes  引数タイプ
 * @param returnType     戻り値タイプ
 * @param returnSubTypes 戻り値サブタイプ
 * @param startOffset    開始オフセット
 * @param endOffset      終了オフセット
 * @return 関数情報
 */
QBasicFunctionEntity *QBasicFunctions::addUpdate(
												 const string &name,
												 const vector<QBasicVariableEntity> &variableTypes,
												 const VariableType returnType,
												 const vector<VariableType> returnSubTypes,
												 const int startOffset,
												 const int endOffset) {

	auto func = getFunction(name, variableTypes);
	if (func != nullptr) {
		// 更新
		func->returnType = returnType;
		func->returnSubTypes = returnSubTypes;
		func->startOffset = startOffset;
		func->endOffset = endOffset;
		return func;
	}
	// 追加
	QBasicFunctionEntity entity = QBasicFunctionEntity(name, variableTypes, returnType, returnSubTypes, startOffset, endOffset);
	functions[entity.alias] = entity;
	// 名前サマリ更新
	buildSummaryNames();
	return &functions[entity.alias];
}

/**
 * 名前で存在判定
 * @param name 関数名
 * @return 存在可否
 */
bool QBasicFunctions::hasName(const string &name) {
	return find(summaryNames.begin(), summaryNames.end(), name) != summaryNames.end();
}

/**
 * 名前で存在判定
 * @param name          関数名
 * @param variableTypes 引数タイプ
 * @return 存在可否
 */
bool QBasicFunctions::hasFunction(const string &name, const vector<QBasicVariableEntity> &arguments) {
	return getFunction(name, arguments) != nullptr;
}

/**
 * 名前と引数で取得
 * @param name          関数名
 * @param variableTypes 引数タイプ
 * @return 関数情報
 */
QBasicFunctionEntity *QBasicFunctions::getFunction(const string &name, const vector<QBasicVariableEntity> &arguments) {
	// エリアス取得
	auto alias = QBasicFunctionEntity::exchangeAlias(name, arguments);
	return functions.find(alias) != functions.end() ? &functions[alias] : nullptr;
}

/**
 * 別名で取得
 * @param alias 別名
 * @return 関数情報
 */
QBasicFunctionEntity *QBasicFunctions::getFunction(const string &alias) {
	return functions.find(alias) != functions.end() ? &functions[alias] : nullptr;
}


/**
 * 省略引数をマージする
 * @param name      関数名
 * @param arguments 引数
 * @return 引数群
 */
vector<QBasicVariableEntity> QBasicFunctions::mergeArguments(const string &name, const vector<QBasicVariableEntity> &arguments) {
	
	bool isSuccess = false;
	vector<QBasicVariableEntity> argList;
	vector<string> functionNames;
	
	// 対象のファンクションを取得する
	for (auto funcIt = functions.begin();funcIt != functions.end();funcIt++) {
		if (funcIt->second.name != name) {
			continue;
		}
		
		argList.clear();

		// 引数チェック
		int index = 0;
		for (auto argIt = funcIt->second.argNames.begin();argIt != funcIt->second.argNames.end();argIt++) {
			auto value = *argIt;
			if (argIt->isEmpty) {
				// 省略不可
				if (index < arguments.size() && argIt->name != arguments[index].name) {
					// 名前が一致してないので終了
					break;
				}
				value.set(arguments[index]);
				argList.push_back(value);
				index++;
				continue;
			}
			
			// 省略可
			if (index < arguments.size() && argIt->name == arguments[index].name) {
				// 名前一致
				value.set(arguments[index]);
				argList.push_back(value);
				index++;
				continue;
			}
			
			// そのまま設定
			argList.push_back(value);
		}
		isSuccess = (index == arguments.size());
		
		// TODO: 複数該当のファンクションがあった場合はエラーにする。
		
		if (isSuccess) {
			break;
		}
	}
	
	if (!isSuccess) {
		return arguments;
	}
	
	return argList;
}

/**
 *  クリア
 */
void QBasicFunctions::clear() {
	functions.clear();
}

/**
 * 名前でさまった一覧作成
 */
void QBasicFunctions::buildSummaryNames() {
	summaryNames.clear();
	for (auto it = functions.begin();it != functions.end();it++) {
		if (functions.find(it->second.name) == functions.end()) {
			summaryNames.push_back(it->second.name);
		}
	}
}
