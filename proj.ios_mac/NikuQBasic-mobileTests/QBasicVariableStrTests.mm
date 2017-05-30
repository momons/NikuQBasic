//
//  QBasicVariableStrTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/22.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"

/// スクリプト str変数テスト
@interface QBasicVariableStrTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicVariableStrTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"variable_str" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// 型テスト string
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "あいうえお");
}

/// 型テスト stringにintはダメ
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト stringにfloatはダメ
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト stringにboolはダメ
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト 型推論テスト
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "abcdef");
}

/// 型テスト 省略引き算
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト 省略掛け算
- (void)test6 {
	interpreter = new QBasic(nullptr, [scripts[6] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト 省略割り算
- (void)test7 {
	interpreter = new QBasic(nullptr, [scripts[7] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト 省略余り
- (void)test8 {
	interpreter = new QBasic(nullptr, [scripts[8] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト 省略足し算
- (void)test9 {
	interpreter = new QBasic(nullptr, [scripts[9] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "abcdef");
}

/// 初期値nil
- (void)test10 {
	interpreter = new QBasic(nullptr, [scripts[10] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].isNil, true);
}

/// nil + "a" = nil
- (void)test11 {
	interpreter = new QBasic(nullptr, [scripts[11] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].isNil, true);
}

/// nilの代入
- (void)test12 {
	interpreter = new QBasic(nullptr, [scripts[12] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].isNil, true);
}

@end
