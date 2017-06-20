//
//  QBasicFunctionStorageTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/20.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "StringUtil.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"

/// データアクセス関数テスト
@interface QBasicFunctionStorageTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicFunctionStorageTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"function_storage" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// intを保存し読込
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["b"].intValue, 10);
	XCTAssertEqual(interpreter->variables["c"].floatValue, 10.0);
	XCTAssertEqual(interpreter->variables["d"].strValue, "10");
	XCTAssertEqual(interpreter->variables["e"].boolValue, true);
	XCTAssertEqual(interpreter->variables["f"].isNil, true);
	XCTAssertEqual(interpreter->variables["g"].isNil, true);
}

/// floatを保存し読込
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["b"].intValue, 10);
	XCTAssertEqual(interpreter->variables["c"].floatValue, 10.5);
	XCTAssertEqual(interpreter->variables["d"].strValue, "10.5");
	XCTAssertEqual(interpreter->variables["e"].boolValue, true);
	XCTAssertEqual(interpreter->variables["f"].isNil, true);
	XCTAssertEqual(interpreter->variables["g"].isNil, true);
}

/// strを保存し読込
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["b"].intValue, 123);
	XCTAssertEqual(interpreter->variables["c"].floatValue, 123.5);
	XCTAssertEqual(interpreter->variables["d"].strValue, "123.5");
	XCTAssertEqual(interpreter->variables["e"].boolValue, false);
	XCTAssertEqual(interpreter->variables["f"].isNil, true);
	XCTAssertEqual(interpreter->variables["g"].isNil, true);
}

/// boolを保存し読込
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["b"].intValue, 1);
	XCTAssertEqual(interpreter->variables["c"].floatValue, 1.0);
	XCTAssertEqual(interpreter->variables["d"].strValue, "true");
	XCTAssertEqual(interpreter->variables["e"].boolValue, true);
	XCTAssertEqual(interpreter->variables["f"].isNil, true);
	XCTAssertEqual(interpreter->variables["g"].isNil, true);
}

/// listを保存し読込
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["b"].isNil, true);
	XCTAssertEqual(interpreter->variables["c"].isNil, true);
	XCTAssertEqual(interpreter->variables["d"].isNil, true);
	XCTAssertEqual(interpreter->variables["e"].isNil, true);
	XCTAssertEqual(interpreter->variables["f"].isNil, false);
	XCTAssertEqual(interpreter->variables["f"].listValue.size(), 3);
	XCTAssertEqual(interpreter->variables["f"].listValue[0].intValue, 1);
	XCTAssertEqual(interpreter->variables["f"].listValue[1].intValue, 2);
	XCTAssertEqual(interpreter->variables["f"].listValue[2].intValue, 3);
	XCTAssertEqual(interpreter->variables["g"].isNil, true);
}

/// dictを保存し読込
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["b"].isNil, true);
	XCTAssertEqual(interpreter->variables["c"].isNil, true);
	XCTAssertEqual(interpreter->variables["d"].isNil, true);
	XCTAssertEqual(interpreter->variables["e"].isNil, true);
	XCTAssertEqual(interpreter->variables["f"].isNil, true);
	XCTAssertEqual(interpreter->variables["g"].isNil, false);
	XCTAssertEqual(interpreter->variables["g"].dictValue.size(), 3);
	XCTAssertEqual(interpreter->variables["g"].dictValue["a"].intValue, 1);
	XCTAssertEqual(interpreter->variables["g"].dictValue["b"].intValue, 2);
	XCTAssertEqual(interpreter->variables["g"].dictValue["c"].intValue, 3);
}

@end
