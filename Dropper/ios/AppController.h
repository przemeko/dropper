//
//  DropperAppController.h
//  Dropper
//
//  Created by Przemek on 08.10.2012.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController	*viewController;
}

@end

