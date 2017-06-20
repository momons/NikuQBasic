//
//  QBasicLetTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/06/21.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBasic.h"
#import "QBasicSymbols.h"
#import "QBasicErrors.h"
#import "QBasicErrorEntity.h"
#import "QBasicVariableEntity.h"

/// スクリプト 定数テスト
@interface QBasicLetTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicLetTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"let" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// 定数定義
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 10);
	XCTAssertEqual(interpreter->variables["a"].isConst, true);
}

/// 初期値指定しないとエラー
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertThrows(interpreter->run());
	XCTAssertGreaterThanOrEqual(interpreter->errors->size(), 1);
	XCTAssertEqual((*interpreter->errors)[0]->symbolIndex, 2);
	XCTAssertEqual((*interpreter->errors)[0]->type, ErrorType::NothingConstValue);
}

/// 値を変更しようとするとエラー
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertThrows(interpreter->run());
	XCTAssertGreaterThanOrEqual(interpreter->errors->size(), 1);
	XCTAssertEqual((*interpreter->errors)[0]->symbolIndex, 5);
	XCTAssertEqual((*interpreter->errors)[0]->type, ErrorType::NoChangeConstValue);
}

/// 配列の要素を変更しようとするとエラー
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertThrows(interpreter->run());
	XCTAssertGreaterThanOrEqual(interpreter->errors->size(), 1);
	XCTAssertEqual((*interpreter->errors)[0]->symbolIndex, 13);
	XCTAssertEqual((*interpreter->errors)[0]->type, ErrorType::NoChangeConstValue);
}

@end
