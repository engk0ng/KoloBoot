//
//  InputParamController.m
//  KoloBoot
//
//  Created by Abu Muhammad on 12/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "InputParamController.h"
#import "UITextField+Extended.h"
#import "helper_oncpp.h"
#import "helper_onc.h"
#import <array>
#import "IGAutoCompletionToolbar.h"
#import "IGAutoCompletionToolbarCell.h"

@interface InputParamController () <IGAutoCompletionToolbarDelegate>
@property (nonatomic, weak) UITextField *currentField;
@property (strong, nonatomic) IGAutoCompletionToolbar *toolbar;
@end

@implementation InputParamController

- (void)viewDidLoad {
    [super viewDidLoad];
    _keyField.delegate = self;
    _valueField.delegate = self;
    _keyField.nextTextField = _valueField;
    
    _keyField.clearButtonMode = UITextFieldViewModeWhileEditing;
    _valueField.clearButtonMode = UITextFieldViewModeWhileEditing;
    if (_param.getType<int>() == Model::TYPE_QUERY) {
        _keyField.inputAccessoryView = [self toolbarKeyboard];
        _valueField.inputAccessoryView = [self toolbarKeyboard];
    }
    else {
        NSArray *arr = @[@"Accept", @"Accept-Charset", @"Accept-Encoding", @"Accept-Language", @"Accept-Datetime" ,@"Authorization", @"Cache-Control", @"Connection", @"Content-Length", @"Content-MD5", @"Content-Type", @"Cookie",
            @"Date", @"Expect", @"From", @"Forwarded", @"Host", @"If-Match", @"If-Modified-Since", @"If-None-Match", @"If-Range", @"If-Unmodified-Since", @"Max-Forwards", @"Origin", @"Pragma", @"Proxy-Authorization", @"Range", @"Referer", @"TE", @"User-Agent", @"Upgrade", @"Via", @"Warning"];
        [[IGAutoCompletionToolbarCell appearance] setTextColor:[UIColor darkGrayColor]];
        [[IGAutoCompletionToolbarCell appearance] setHighlightedTextColor:self.view.tintColor];
        [[IGAutoCompletionToolbarCell appearance] setBackgroundColor:NAV_DEFAULT_COLOR];
        [[IGAutoCompletionToolbarCell appearance] setHighlightedBackgroundColor:[UIColor clearColor]];
        [[IGAutoCompletionToolbarCell appearance] setTextFont:[UIFont systemFontOfSize:13]];
        [[IGAutoCompletionToolbarCell appearance] setCornerRadius:0];
        
        self.toolbar = [[IGAutoCompletionToolbar alloc] initWithFrame:CGRectMake(0,0,320,44)];
        self.toolbar.items = arr;
        self.toolbar.toolbarDelegate = self;
        _keyField.inputAccessoryView = self.toolbar;
        self.toolbar.textField = _keyField;
        _valueField.inputAccessoryView = [self toolbarKeyboard];
    }
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleKeyboardDidShowNotification:)
                                                 name:UIKeyboardDidShowNotification
                                               object:nil];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    if (_textFieldBecomeFirstResponder) {
        [_keyField becomeFirstResponder];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 3;
}

#pragma mark - UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    UITextField *next = textField.nextTextField;
    if (next) {
        [next becomeFirstResponder];
    } else {
        [textField resignFirstResponder];
    }
    return NO;
}
- (void)textFieldDidBeginEditing:(UITextField *)textField {
    _currentField = textField;
}

#pragma mark - Helper

- (UIToolbar *)toolbarKeyboard {
    UIToolbar* keyboardToolbar = [[UIToolbar alloc] init];
    [keyboardToolbar sizeToFit];
    UIBarButtonItem *flexBarButton = [[UIBarButtonItem alloc]
                                      initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace
                                      target:nil action:nil];
    UIBarButtonItem *doneBarButton = [[UIBarButtonItem alloc]
                                      initWithBarButtonSystemItem:UIBarButtonSystemItemDone
                                      target:self action:@selector(fieldDoneButtonPressed)];
    keyboardToolbar.items = @[flexBarButton, doneBarButton];
    return keyboardToolbar;
}

- (void)fieldDoneButtonPressed {
    if ([_currentField isEqual:_keyField]) {
        [_keyField resignFirstResponder];
    }
    else {
        [_valueField resignFirstResponder];
    }
}

- (IBAction)cancelAction:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)saveAction:(id)sender {
    
}

- (void)handleKeyboardDidShowNotification:(NSNotification *)notification
{
    NSDictionary* info = [notification userInfo];
    CGSize keyboardSize = [[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size;
    NSLog(@"Size: %@", NSStringFromCGSize(keyboardSize));
    // Move your textview into view here
}

#pragma mark - IGAutoCompletionToolbarDelegate

- (void)autoCompletionToolbar:(IGAutoCompletionToolbar *)toolbar didSelectItemWithObject:(id)object {
    _keyField.text = @"";
    _keyField.text = (NSString *)object;
}

@end
