//
//  QBasicQueries.cpp
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/21.
//
//

#include "QBasicQueries.h"

#include "QBasicVariableEntity.h"
#include "QBasicUrlEncode.h"

/**
 *  クエリ文字列変換
 *  @param value 値
 */
string QBasicQueries::toQueryString(QBasicVariableEntity &value) {
	if (value.types[0] != VariableType::Dict || value.isNil) {
		return "";
	}
	ostringstream ostr;
	int count = 0;
	for (auto it = value.dictValue.begin();it != value.dictValue.end();it++) {
		if (count > 0) {
			ostr << "&";
		}
		ostr << it->first << "=";
		switch (it->second.types[0]) {
			case VariableType::Int:
			case VariableType::Float:
			case VariableType::Str:
			case VariableType::Bool:
				ostr << QBasicUrlEncode::encode(it->second.toStr().strValue);
				break;
			case VariableType::List: {
				int count2 = 0;
				for (auto it2 = it->second.listValue.begin();it2 != it->second.listValue.end();it2++) {
					if (count2 > 0) {
						ostr << "&" << it->first << "=";
					}
					ostr << QBasicUrlEncode::encode(it2->toStr().strValue);
					count2 += 1;
				}
				break;
			}
			default:
				// Dictとそれ以外は無視
				break;
		}
		count += 1;
	}
	return ostr.str();
}
