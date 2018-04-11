//
//  Utils.m
//  KoloBoot
//
//  Created by Abu Muhammad on 11/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "Utils.h"
#import "helper_oncpp.h"

using namespace Koloboot::Helper;

@implementation Utils
+ (NSString *)toNSString:(std::string)str {
    return CFBridgingRelease(toCFString(str));
}
@end
