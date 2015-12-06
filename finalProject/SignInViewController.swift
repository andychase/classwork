//
//  FirstViewController.swift
//  finalProject
//
//  Created by Andy Chase on 12/5/15.
//  Copyright © 2015 Andy Chase. All rights reserved.
//

import UIKit
import Alamofire

class SignInViewController: UIViewController {
    
    @IBOutlet weak var usernameField: UITextField!
    @IBOutlet weak var passwordField: UITextField!
    @IBOutlet weak var notificationLabel: UILabel!
    
    override func viewWillAppear(animated: Bool) {
        self.notificationLabel.hidden = true
    }
    
    @IBAction func signInButtonPress(sender: UIButton) {
        let parameters = ["username": self.usernameField.text!, "password": self.passwordField.text!]
        Alamofire.request(.POST, "http://127.0.0.1:5000/login", parameters: parameters)
            .responseJSON { response in
                self.notificationLabel.hidden = false;
                if let JSON = response.result.value {
                    if let id = JSON["id"] as? String {
                        if id != "" {
                            self.notificationLabel.text = "Sign in Success!"
                            self.notificationLabel.textColor = UIColor.greenColor()
                            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, Int64(NSEC_PER_SEC)), dispatch_get_main_queue()) {
                                self.performSegueWithIdentifier("gotoLists", sender: id)
                            }
                        }
                        return
                    }
                
                }
                self.notificationLabel.text = "Sign in Failure!"
                self.notificationLabel.textColor = UIColor.redColor()
                
        }

    }
    
    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        if (segue.identifier == "gotoLists") {
            let dest:TabBarController = segue.destinationViewController as! TabBarController
            let userId = sender as! String
            dest.userId = userId
        }
    }
}
