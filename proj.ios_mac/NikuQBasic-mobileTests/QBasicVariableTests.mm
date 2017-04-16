//
//  QBasicVariableTests.mm
//  QBasicVariableTests
//
//  Created by HaraKazunari on 2017/03/24.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"

/// スクリプト 変数テスト
@interface QBasicVariableTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicVariableTests

- (void)setUp {
    [super setUp];

	NSString *script = [TestFileUtils loadFile:@"variable" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
    [super tearDown];
}

/// 英字のみ宣言
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 英数字で宣言
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// 記号を混ぜるとコンパイルエラー
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 頭が数字はコンパイルエラー
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 基本ステートメント名と被っているとコンパイルエラー
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// ステートメント名と被っているとコンパイルエラー
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 数値を入れて取り出せるか 1
- (void)test6 {
	interpreter = new QBasic(nullptr, [scripts[6] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 計算式を入れて取り出せるか 15
- (void)test7 {
	interpreter = new QBasic(nullptr, [scripts[7] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 15);
}

/// 違う変数から値を設定できる
- (void)test8 {
	interpreter = new QBasic(nullptr, [scripts[8] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 変数を判定できるか
- (void)test9 {
	interpreter = new QBasic(nullptr, [scripts[9] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 変数同士の判定ができるか
- (void)test10 {
	interpreter = new QBasic(nullptr, [scripts[10] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 変数の２重定義はコンパイルエラー
- (void)test11 {
	interpreter = new QBasic(nullptr, [scripts[11] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト int
- (void)test12 {
	interpreter = new QBasic(nullptr, [scripts[12] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 9999);
}

/// 型テスト intにfloatはダメ
- (void)test13 {
	interpreter = new QBasic(nullptr, [scripts[13] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト intにstringはダメ
- (void)test14 {
	interpreter = new QBasic(nullptr, [scripts[14] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト intにboolはダメ
- (void)test15 {
	interpreter = new QBasic(nullptr, [scripts[15] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト float
- (void)test16 {
	interpreter = new QBasic(nullptr, [scripts[16] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].floatValue, 9999.888);
}

/// 型テスト floatにintはダメ
- (void)test17 {
	interpreter = new QBasic(nullptr, [scripts[17] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト floatにstringはダメ
- (void)test18 {
	interpreter = new QBasic(nullptr, [scripts[18] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト floatにboolはダメ
- (void)test19 {
	interpreter = new QBasic(nullptr, [scripts[19] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト string
- (void)test20 {
	interpreter = new QBasic(nullptr, [scripts[20] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].strValue, "あいうえお");
}

/// 型テスト stringにintはダメ
- (void)test21 {
	interpreter = new QBasic(nullptr, [scripts[21] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト stringにfloatはダメ
- (void)test22 {
	interpreter = new QBasic(nullptr, [scripts[22] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト stringにboolはダメ
- (void)test23 {
	interpreter = new QBasic(nullptr, [scripts[23] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト bool
- (void)test24 {
	interpreter = new QBasic(nullptr, [scripts[24] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}

/// 型テスト boolにintはダメ
- (void)test25 {
	interpreter = new QBasic(nullptr, [scripts[25] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト boolにfloatはダメ
- (void)test26 {
	interpreter = new QBasic(nullptr, [scripts[26] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// 型テスト boolにstringはダメ
- (void)test27 {
	interpreter = new QBasic(nullptr, [scripts[27] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

@end
