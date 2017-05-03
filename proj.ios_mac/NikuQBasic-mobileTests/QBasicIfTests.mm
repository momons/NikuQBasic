//
//  QBasicIfTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/25.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"

@interface QBasicIfTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicIfTests

- (void)setUp {
    [super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"if" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
    [super tearDown];
}

/// イコール
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// ノットイコール
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 小なり
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 小なりイコール
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 大なり
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 大なりイコール
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// and
- (void)test6 {
	interpreter = new QBasic(nullptr, [scripts[6] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// or
- (void)test7 {
	interpreter = new QBasic(nullptr, [scripts[7] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// xor
- (void)test8 {
	interpreter = new QBasic(nullptr, [scripts[8] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
}

/// not
- (void)test9 {
	interpreter = new QBasic(nullptr, [scripts[9] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// else
- (void)test10 {
	interpreter = new QBasic(nullptr, [scripts[10] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// elseif
- (void)test11 {
	interpreter = new QBasic(nullptr, [scripts[11] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// elseifその２
- (void)test12 {
	interpreter = new QBasic(nullptr, [scripts[12] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 文字比較イコール
- (void)test13 {
	interpreter = new QBasic(nullptr, [scripts[13] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 文字比較ノットイコール
- (void)test14 {
	interpreter = new QBasic(nullptr, [scripts[14] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 文字比較小なり
- (void)test15 {
	interpreter = new QBasic(nullptr, [scripts[15] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 文字比較小なりイコール
- (void)test16 {
	interpreter = new QBasic(nullptr, [scripts[16] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 文字比較大なり
- (void)test17 {
	interpreter = new QBasic(nullptr, [scripts[17] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// 文字比較大なりイコール
- (void)test18 {
	interpreter = new QBasic(nullptr, [scripts[18] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// if文の中にif文
- (void)test19 {
	interpreter = new QBasic(nullptr, [scripts[19] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// else２個でコンパイルエラー
- (void)test20 {
	interpreter = new QBasic(nullptr, [scripts[20] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// elseの後にelseifでコンパイルエラー
- (void)test21 {
	interpreter = new QBasic(nullptr, [scripts[21] UTF8String], "");
	XCTAssertThrows(interpreter->run());
}

/// str判定
- (void)test22 {
	interpreter = new QBasic(nullptr, [scripts[22] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}

/// str判定 小なり
- (void)test23 {
	interpreter = new QBasic(nullptr, [scripts[23] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}

/// str判定 小なりイコール
- (void)test24 {
	interpreter = new QBasic(nullptr, [scripts[24] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}

/// str判定 大なり
- (void)test25 {
	interpreter = new QBasic(nullptr, [scripts[25] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}

/// str判定 大なりイコール
- (void)test26 {
	interpreter = new QBasic(nullptr, [scripts[26] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}

/// float判定
- (void)test27 {
	interpreter = new QBasic(nullptr, [scripts[27] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}

/// float判定 小なり
- (void)test28 {
	interpreter = new QBasic(nullptr, [scripts[28] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}

/// float判定 小なりイコール
- (void)test29 {
	interpreter = new QBasic(nullptr, [scripts[29] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}

/// float判定 大なり
- (void)test30 {
	interpreter = new QBasic(nullptr, [scripts[30] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}

/// float判定 大なりイコール
- (void)test31 {
	interpreter = new QBasic(nullptr, [scripts[31] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}

/// bool判定
- (void)test32 {
	interpreter = new QBasic(nullptr, [scripts[32] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}

/// bool判定 小なり
- (void)test33 {
	interpreter = new QBasic(nullptr, [scripts[33] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}

/// bool判定 小なりイコール
- (void)test34 {
	interpreter = new QBasic(nullptr, [scripts[34] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}

/// bool判定 大なり
- (void)test35 {
	interpreter = new QBasic(nullptr, [scripts[35] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}

/// bool判定 大なりイコール
- (void)test36 {
	interpreter = new QBasic(nullptr, [scripts[36] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].boolValue, true);
}
@end
