//
//  TestFileUtils.m
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/25.
//
//

#import "TestFileUtils.h"

@implementation TestFileUtils

/// ファイル読み込み
+ (NSString *)loadFile:(NSString *)fileName clazz:(Class)clazz {
	
	NSBundle *bundle = [NSBundle bundleForClass:clazz];
	NSString *filePath = [bundle pathForResource:[NSString stringWithFormat:@"TestScripts/%@", fileName] ofType:@"txt"];
	
	NSError *error;
	return [NSString stringWithContentsOfFile:filePath
									 encoding:NSUTF8StringEncoding
										error:&error];
}

@end
