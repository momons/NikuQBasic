//
//  QBasicVariableListTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/04/22.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"

/// スクリプト list変数テスト
@interface QBasicVariableListTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicVariableListTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"variable_list" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// 配列型宣言 list<int>
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 list<float>
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 list<str>
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 list<bool>
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 list<list<bool>>
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 list<dict<bool>>
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 初期値設定 list<int>
- (void)test6 {
	interpreter = new QBasic(nullptr, [scripts[6] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 初期値設定 list<float>
- (void)test7 {
	interpreter = new QBasic(nullptr, [scripts[7] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 初期値設定 list<str>
- (void)test8 {
	interpreter = new QBasic(nullptr, [scripts[8] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 初期値設定 list<bool>
- (void)test9 {
	interpreter = new QBasic(nullptr, [scripts[9] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 配列型宣言 初期値設定 list<list<bool>>
- (void)test10 {
	interpreter = new QBasic(nullptr, [scripts[10] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 配列型宣言 初期値設定 list<dict<bool>>
- (void)test11 {
	interpreter = new QBasic(nullptr, [scripts[11] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 配列型宣言 型推論 list<int>
- (void)test12 {
	interpreter = new QBasic(nullptr, [scripts[12] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 配列型宣言 型推論 list<float>
- (void)test13 {
	interpreter = new QBasic(nullptr, [scripts[13] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 配列型宣言 型推論 list<str>
- (void)test14 {
	interpreter = new QBasic(nullptr, [scripts[14] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 配列型宣言 型推論 list<bool>
- (void)test15 {
	interpreter = new QBasic(nullptr, [scripts[15] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 配列型宣言 型推論 list<list<bool>>
- (void)test16 {
	interpreter = new QBasic(nullptr, [scripts[16] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 配列型宣言 型推論 list<dict<bool>>
- (void)test17 {
	interpreter = new QBasic(nullptr, [scripts[17] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 初期値設定 宣言と異なる
- (void)test18 {
	interpreter = new QBasic(nullptr, [scripts[18] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 配列型宣言 型推論 いろいろな型がまざる
- (void)test19 {
	interpreter = new QBasic(nullptr, [scripts[19] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 初期値以外で値を設定
- (void)test20 {
	interpreter = new QBasic(nullptr, [scripts[20] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 配列型宣言 各要素取り出し list<int>
- (void)test21 {
	interpreter = new QBasic(nullptr, [scripts[21] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["b"].intValue, 1);
	XCTAssertEqual(interpreter->variables["c"].intValue, 5);
}

/// 配列型宣言 各要素取り出し list<list<str>>
- (void)test22 {
	interpreter = new QBasic(nullptr, [scripts[22] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["b"].strValue, "b");
	XCTAssertEqual(interpreter->variables["c"].strValue, "c");
	XCTAssertEqual(interpreter->variables["e"].strValue, "e");
}

/// 配列型宣言 各要素取り出し list<list<float>>
- (void)test23 {
	interpreter = new QBasic(nullptr, [scripts[23] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["b"].floatValue, 2.0);
	XCTAssertEqual(interpreter->variables["c"].floatValue, 3.0);
	XCTAssertEqual(interpreter->variables["e"].floatValue, 5.0);
}

/// 配列型宣言 各要素取り出し list<int>
- (void)test24 {
	interpreter = new QBasic(nullptr, [scripts[24] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["b"].intValue, 5);
	XCTAssertEqual(interpreter->variables["c"].intValue, 1);
}

/// 配列型宣言 各要素取り出し list<int>
- (void)test25 {
	interpreter = new QBasic(nullptr, [scripts[25] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["b"].strValue, "bb");
	XCTAssertEqual(interpreter->variables["c"].strValue, "cc");
	XCTAssertEqual(interpreter->variables["e"].strValue, "ee");
}

/// 配列型宣言 各要素取り出し list<dict<float>>
- (void)test26 {
	interpreter = new QBasic(nullptr, [scripts[26] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["b"].floatValue, 4.0);
	XCTAssertEqual(interpreter->variables["c"].floatValue, 6.0);
	XCTAssertEqual(interpreter->variables["e"].floatValue, 10.0);
}

/// 初期値nil
- (void)test27 {
	interpreter = new QBasic(nullptr, [scripts[27] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].isNil, true);
}

/// nilの代入
- (void)test28 {
	interpreter = new QBasic(nullptr, [scripts[28] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].isNil, true);
}

@end
