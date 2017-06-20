//
//  QBasicVariableJsonTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/16.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"
#import "picojson.h"

/// JSON変換テスト
@interface QBasicVariableJsonTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}

@end

@implementation QBasicVariableJsonTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"variable_json" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// JSON文字列変換　int
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	auto object = interpreter->variables["a"].toJsonObject();
	auto jsonString = picojson::value(object).serialize();
	XCTAssertEqual(jsonString, "{\"b\":1}");
	auto valueEntity = QBasicVariableEntity::buildForJsonObject(object);
	XCTAssertEqual(valueEntity.dictValue.size(), interpreter->variables["a"].dictValue.size());
	XCTAssertEqual(valueEntity.dictValue.begin()->first, interpreter->variables["a"].dictValue.begin()->first);
	XCTAssertEqual(valueEntity.dictValue.begin()->second.intValue, interpreter->variables["a"].dictValue.begin()->second.intValue);
}

/// JSON文字列変換 float
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	auto object = interpreter->variables["a"].toJsonObject();
	auto jsonString = picojson::value(object).serialize();
	XCTAssertEqual(jsonString, "{\"b\":1.1}");
	auto valueEntity = QBasicVariableEntity::buildForJsonObject(object);
	XCTAssertEqual(valueEntity.dictValue.size(), interpreter->variables["a"].dictValue.size());
	XCTAssertEqual(valueEntity.dictValue.begin()->first, interpreter->variables["a"].dictValue.begin()->first);
	XCTAssertEqual(valueEntity.dictValue.begin()->second.floatValue, interpreter->variables["a"].dictValue.begin()->second.floatValue);
}

/// JSON文字列変換 str
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	auto object = interpreter->variables["a"].toJsonObject();
	auto jsonString = picojson::value(object).serialize();
	XCTAssertEqual(jsonString, "{\"b\":\"abc\"}");
	auto valueEntity = QBasicVariableEntity::buildForJsonObject(object);
	XCTAssertEqual(valueEntity.dictValue.size(), interpreter->variables["a"].dictValue.size());
	XCTAssertEqual(valueEntity.dictValue.begin()->first, interpreter->variables["a"].dictValue.begin()->first);
	XCTAssertEqual(valueEntity.dictValue.begin()->second.strValue, interpreter->variables["a"].dictValue.begin()->second.strValue);
}

/// JSON文字列変換 bool
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	auto object = interpreter->variables["a"].toJsonObject();
	auto jsonString = picojson::value(object).serialize();
	XCTAssertEqual(jsonString, "{\"b\":false}");
	auto valueEntity = QBasicVariableEntity::buildForJsonObject(object);
	XCTAssertEqual(valueEntity.dictValue.size(), interpreter->variables["a"].dictValue.size());
	XCTAssertEqual(valueEntity.dictValue.begin()->first, interpreter->variables["a"].dictValue.begin()->first);
	XCTAssertEqual(valueEntity.dictValue.begin()->second.boolValue, interpreter->variables["a"].dictValue.begin()->second.boolValue);
}

/// JSON文字列変換 list
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	auto object = interpreter->variables["a"].toJsonObject();
	auto jsonString = picojson::value(object).serialize();
	XCTAssertEqual(jsonString, "{\"b\":[2,2.2,\"def\",true,[1],{\"h\":1}]}");
	auto valueEntity = QBasicVariableEntity::buildForJsonObject(object);
	XCTAssertEqual(valueEntity.dictValue.size(), interpreter->variables["a"].dictValue.size());
	XCTAssertEqual(valueEntity.dictValue.begin()->first, interpreter->variables["a"].dictValue.begin()->first);
	XCTAssertEqual(valueEntity.dictValue.begin()->second.listValue.size(), interpreter->variables["a"].dictValue.begin()->second.listValue.size());
	for (int i = 0;i < valueEntity.dictValue.begin()->second.listValue.size();i++) {
		switch(i) {
			case 0:
				XCTAssertEqual(valueEntity.dictValue.begin()->second.listValue[i].intValue,
							   interpreter->variables["a"].dictValue.begin()->second.listValue[i].intValue);
				break;
			case 1:
				XCTAssertEqual(valueEntity.dictValue.begin()->second.listValue[i].floatValue,
							   interpreter->variables["a"].dictValue.begin()->second.listValue[i].floatValue);
				break;
			case 2:
				XCTAssertEqual(valueEntity.dictValue.begin()->second.listValue[i].strValue,
							   interpreter->variables["a"].dictValue.begin()->second.listValue[i].strValue);
				break;
			case 3:
				XCTAssertEqual(valueEntity.dictValue.begin()->second.listValue[i].boolValue,
							   interpreter->variables["a"].dictValue.begin()->second.listValue[i].boolValue);
				break;
			case 4:
				XCTAssertEqual(valueEntity.dictValue.begin()->second.listValue[i].listValue.size(),
							   interpreter->variables["a"].dictValue.begin()->second.listValue[i].listValue.size());
				XCTAssertEqual(valueEntity.dictValue.begin()->second.listValue[i].listValue[0].intValue,
							   interpreter->variables["a"].dictValue.begin()->second.listValue[i].listValue[0].intValue);
				break;
			default:
				XCTAssertEqual(valueEntity.dictValue.begin()->second.listValue[i].dictValue.size(),
							   interpreter->variables["a"].dictValue.begin()->second.listValue[i].dictValue.size());
				XCTAssertEqual(valueEntity.dictValue.begin()->second.listValue[i].dictValue.begin()->first,
							   interpreter->variables["a"].dictValue.begin()->second.listValue[i].dictValue.begin()->first);
				XCTAssertEqual(valueEntity.dictValue.begin()->second.listValue[i].dictValue.begin()->second.intValue,
							   interpreter->variables["a"].dictValue.begin()->second.listValue[i].dictValue.begin()->second.intValue);
				break;
		}
	}
}

/// JSON文字列変換 dist 順番が不確定になる得るが一応チェック
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	auto object = interpreter->variables["a"].toJsonObject();
	auto jsonString = picojson::value(object).serialize();
	XCTAssertEqual(jsonString, "{\"b\":{\"c\":1,\"d\":2,\"e\":\"abc\",\"f\":[1],\"g\":{\"h\":1}}}");
	auto valueEntity = QBasicVariableEntity::buildForJsonObject(object);
	XCTAssertEqual(valueEntity.dictValue.size(), interpreter->variables["a"].dictValue.size());
	XCTAssertEqual(valueEntity.dictValue.begin()->first, interpreter->variables["a"].dictValue.begin()->first);
	XCTAssertEqual(valueEntity.dictValue.begin()->second.dictValue.size(), interpreter->variables["a"].dictValue.begin()->second.dictValue.size());
}

/// JSON文字列変換 JSON文字列変換 配列
- (void)test6 {
	interpreter = new QBasic(nullptr, [scripts[6] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	auto object = interpreter->variables["a"].toJsonArray();
	auto jsonString = picojson::value(object).serialize();
	XCTAssertEqual(jsonString, "[2,2.2,\"def\",true,[1],{\"h\":1}]");
	auto valueEntity = QBasicVariableEntity::buildForJsonArray(object);
	XCTAssertEqual(valueEntity.listValue.size(), interpreter->variables["a"].listValue.size());
}

@end
