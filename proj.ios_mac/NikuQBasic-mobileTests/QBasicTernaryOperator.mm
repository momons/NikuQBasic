//
//  QBasicTernaryOperator.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/09/14.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"
#import "QBasicErrors.h"
#import "QBasicErrorEntity.h"
#import "QBasicSymbols.h"
#import "QBasicSymbolEntity.h"

/// スクリプト 三項演算子テスト
@interface QBasicTernaryOperator : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicTernaryOperator

- (void)setUp {
    [super setUp];

	NSString *script = [TestFileUtils loadFile:@"ternary_operator" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
    [super tearDown];
}

/// true
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 1);
}

/// false
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertNoThrow(interpreter->run());
	XCTAssertEqual(interpreter->variables["a"].intValue, 2);
}

/// 演算結果が型違い
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertThrows(interpreter->run());
	XCTAssertGreaterThanOrEqual(interpreter->errors->size(), 1);
	XCTAssertEqual((*interpreter->errors)[0]->symbolIndex, 6);
	XCTAssertEqual((*interpreter->errors)[0]->type, ErrorType::BadVariableType);
}

/// 演算子がboolではない
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertThrows(interpreter->run());
	XCTAssertGreaterThanOrEqual(interpreter->errors->size(), 1);
	XCTAssertEqual((*interpreter->errors)[0]->symbolIndex, 4);
	XCTAssertEqual((*interpreter->errors)[0]->type, ErrorType::BadVariableType);
}

/// 代入変数と演算結果の型違い
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertThrows(interpreter->run());
	XCTAssertGreaterThanOrEqual(interpreter->errors->size(), 1);
	XCTAssertEqual((*interpreter->errors)[0]->symbolIndex, 6);
	XCTAssertEqual((*interpreter->errors)[0]->type, ErrorType::BadVariableType);
}

@end
