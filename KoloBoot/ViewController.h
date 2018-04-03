//
//  ViewController.h
//  KoloBoot
//
//  Created by Abu Muhammad on 31/03/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <vector>

@class Makai;
@class ViewController;
class Makan;

class Makan {
    
public:
    
};

@interface ViewController : UIViewController
@property (nonatomic, assign) std::shared_ptr<Makai> mki;
@end

