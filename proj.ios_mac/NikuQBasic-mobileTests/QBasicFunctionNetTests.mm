//
//  QBasicFunctionNetTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/27.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "StringUtil.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"

/// 通信関数テスト
@interface QBasicFunctionNetTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicFunctionNetTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"function_net" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// intをクエリに変換
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "a=1");
}

/// floatをクエリに変換
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "a=1.5");
}

/// strをクエリに変換
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "a=anbcdefg");
}

/// boolをクエリに変換
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "a=true");
}

/// listをクエリに変換
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "a=1&a=2&a=3");
}

/// dictをクエリに変換 変換対象外
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "a=");
}

/// 複数をクエリに変換
- (void)test6 {
	interpreter = new QBasic(nullptr, [scripts[6] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "a=1&b=1.5&c=abc&d=true&e=1&e=2&e=3");
}

/// マルチバイト文字列をクエリに変換
- (void)test7 {
	interpreter = new QBasic(nullptr, [scripts[7] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "a=%E3%81%82%E3%81%84%E3%81%86%E3%81%88%E3%81%8A");
}

/// GET通信
- (void)test8 {
	// TODO:あとで対応する
//	interpreter = new QBasic(nullptr, [scripts[8] UTF8String], "");
//	XCTAssertNoThrow(interpreter->run());
}

@end
