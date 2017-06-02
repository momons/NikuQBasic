//
//  QBasicFunctionStringTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/01.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "StringUtil.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"

/// 文字関数テスト
@interface QBasicFunctionStringTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicFunctionStringTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"function_string" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// len
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 3);
	XCTAssertEqual(interpreter->variables["b"].intValue, 5);
	XCTAssertEqual(interpreter->variables["c"].intValue, 15);
}

/// mid
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "ab");
	XCTAssertEqual(interpreter->variables["b"].strValue, "ef");
}

/// left
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "ab");
	XCTAssertEqual(interpreter->variables["b"].strValue, "abc");
}

/// right
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "bc");
	XCTAssertEqual(interpreter->variables["b"].strValue, "def");
}

/// split
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].listValue.size(), 4);
	XCTAssertEqual(interpreter->variables["c0"].strValue, "a");
	XCTAssertEqual(interpreter->variables["c1"].strValue, "bc");
	XCTAssertEqual(interpreter->variables["c2"].strValue, "def");
	XCTAssertEqual(interpreter->variables["c3"].strValue, "ghij");
}

/// empty
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
	XCTAssertEqual(interpreter->variables["b"].boolValue, false);
}

/// notEmpty
- (void)test6 {
	interpreter = new QBasic(nullptr, [scripts[6] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, false);
	XCTAssertEqual(interpreter->variables["b"].boolValue, true);
}

/// replase
- (void)test7 {
	interpreter = new QBasic(nullptr, [scripts[7] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "abc-def-ghi");
	XCTAssertEqual(interpreter->variables["b"].strValue, "かきくけこさしすせそ");
}

/// prefix
- (void)test8 {
	interpreter = new QBasic(nullptr, [scripts[8] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
	XCTAssertEqual(interpreter->variables["b"].boolValue, true);
	XCTAssertEqual(interpreter->variables["c"].boolValue, false);
}

/// suffix
- (void)test9 {
	interpreter = new QBasic(nullptr, [scripts[9] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
	XCTAssertEqual(interpreter->variables["b"].boolValue, true);
	XCTAssertEqual(interpreter->variables["c"].boolValue, false);
}

/// find
- (void)test10 {
	interpreter = new QBasic(nullptr, [scripts[10] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 2);
	XCTAssertEqual(interpreter->variables["b"].intValue, 6);
	XCTAssertEqual(interpreter->variables["c"].intValue, -1);
}

@end
