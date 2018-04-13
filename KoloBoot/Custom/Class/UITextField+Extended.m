//
//  UITextField+Extended.m
//  KoloBoot
//
//  Created by Abu Muhammad on 12/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "UITextField+Extended.h"
#import <objc/runtime.h>

static char defaultHashKey;

@implementation UITextField (Extended)

/* https://stackoverflow.com/questions/1347779/how-to-navigate-through-textfields-next-done-buttons?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa */

- (UITextField *)nextTextField {
    return objc_getAssociatedObject(self, &defaultHashKey);
}

- (void)setNextTextField:(UITextField *)nextTextField{
    objc_setAssociatedObject(self, &defaultHashKey, nextTextField, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}
@end
