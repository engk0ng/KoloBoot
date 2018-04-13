//
//  InputParamController.m
//  KoloBoot
//
//  Created by Abu Muhammad on 12/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "InputParamController.h"
#import "UITextField+Extended.h"

@interface InputParamController ()
@property (nonatomic, weak) UITextField *currentField;
@end

@implementation InputParamController

- (void)viewDidLoad {
    [super viewDidLoad];
    _keyField.delegate = self;
    _valueField.delegate = self;
    _keyField.nextTextField = _valueField;
    
    _keyField.clearButtonMode = UITextFieldViewModeWhileEditing;
    _valueField.clearButtonMode = UITextFieldViewModeWhileEditing;
    
    _keyField.inputAccessoryView = [self toolbarKeyboard];
    _valueField.inputAccessoryView = [self toolbarKeyboard];
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
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

@end
