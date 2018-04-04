//
//  CreateProjectController.m
//  KoloBoot
//
//  Created by Abu Muhammad on 03/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "CreateProjectController.h"

@interface CreateProjectController ()

@end

@implementation CreateProjectController

- (void)viewDidLoad {
    [super viewDidLoad];
    _nameField.delegate = self;
    _baseUrlField.delegate = self;
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardChangingFrame:) name:UIKeyboardWillChangeFrameNotification object:nil];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return YES;
}

#pragma mark - Helper

- (void)keyboardChangingFrame:(NSNotification *)notif {
    NSDictionary *info = [notif userInfo];
    CGRect keyboardEndFram = [info[UIKeyboardFrameEndUserInfoKey] CGRectValue];
    CGFloat offset = [[UIScreen mainScreen] bounds].size.height - CGRectGetMinY(keyboardEndFram) - 60;
    UIEdgeInsets inset = _scrollView.contentInset;
    inset.bottom = offset;
    _scrollView.contentInset = inset;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillChangeFrameNotification object:nil];
}
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
