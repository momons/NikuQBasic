//
//  QBasicCompileErrorTests.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/05/23.
//
//

#import <XCTest/XCTest.h>

#import "TestFileUtils.h"
#import "StringUtil.h"
#import "QBasic.h"
#import "QBasicVariableEntity.h"
#import "QBasicErrors.h"
#import "QBasicErrorEntity.h"
#import "QBasicSymbols.h"
#import "QBasicSymbolEntity.h"

/// コンパイルエラーテスト
@interface QBasicCompileErrorTests : XCTestCase {
@private
	/// テストするスクリプト群
	NSArray<NSString *> *scripts;
	/// インタプリタ
	QBasic *interpreter;
}
@end

@implementation QBasicCompileErrorTests

- (void)setUp {
	[super setUp];
	
	NSString *script = [TestFileUtils loadFile:@"compile_error" clazz:[self class]];
	// 内容を分割
	scripts = [script componentsSeparatedByString:@"========================"];
}

- (void)tearDown {
	
	delete interpreter;
	
	[super tearDown];
}

/// symbols[4]でBadVariableType
- (void)test0 {
	interpreter = new QBasic(nullptr, [scripts[0] UTF8String], "");
	XCTAssertThrows(interpreter->run());
	XCTAssertGreaterThanOrEqual(interpreter->errors->size(), 1);
	XCTAssertEqual((*interpreter->errors)[0]->symbolIndex, 4);
	XCTAssertEqual((*interpreter->errors)[0]->type, ErrorType::UnknownSymbol);
}

/// symbols[6]でBadVariableName
- (void)test1 {
	interpreter = new QBasic(nullptr, [scripts[1] UTF8String], "");
	XCTAssertThrows(interpreter->run());
	XCTAssertGreaterThanOrEqual(interpreter->errors->size(), 1);
	XCTAssertEqual((*interpreter->errors)[0]->symbolIndex, 6);
	XCTAssertEqual((*interpreter->errors)[0]->type, ErrorType::BadVariableName);
}

/// symbols[10]でMissingFound
- (void)test2 {
	interpreter = new QBasic(nullptr, [scripts[2] UTF8String], "");
	XCTAssertThrows(interpreter->run());
	XCTAssertGreaterThanOrEqual(interpreter->errors->size(), 1);
	XCTAssertEqual((*interpreter->errors)[0]->symbolIndex, 10);
	XCTAssertEqual((*interpreter->errors)[0]->type, ErrorType::MissingFound);
}

/// symbols[6]でBadVariableType
- (void)test3 {
	interpreter = new QBasic(nullptr, [scripts[3] UTF8String], "");
	XCTAssertThrows(interpreter->run());
	XCTAssertGreaterThanOrEqual(interpreter->errors->size(), 1);
	XCTAssertEqual((*interpreter->errors)[0]->symbolIndex, 6);
	XCTAssertEqual((*interpreter->errors)[0]->type, ErrorType::BadVariableType);
}

/// symbols[4]でReturnTypeVoid
- (void)test4 {
	interpreter = new QBasic(nullptr, [scripts[4] UTF8String], "");
	XCTAssertThrows(interpreter->run());
	XCTAssertGreaterThanOrEqual(interpreter->errors->size(), 1);
	XCTAssertEqual((*interpreter->errors)[0]->symbolIndex, 4);
	XCTAssertEqual((*interpreter->errors)[0]->type, ErrorType::ReturnTypeVoid);
}

/// symbols[5]でUnknownVariable
- (void)test5 {
	interpreter = new QBasic(nullptr, [scripts[5] UTF8String], "");
	XCTAssertThrows(interpreter->run());
	XCTAssertGreaterThanOrEqual(interpreter->errors->size(), 1);
	XCTAssertEqual((*interpreter->errors)[0]->symbolIndex, 5);
	XCTAssertEqual((*interpreter->errors)[0]->type, ErrorType::UnknownVariable);
}

@end
