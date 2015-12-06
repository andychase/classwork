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
    
    @IBAction func signInButtonPress(sender: UIButton) {
//        let parameters = ["username": usernameField.text!, "password": passwordField.text!]
//        Alamofire.request(.POST, "https://requestbin.herokuapp.com/1atd5h51", parameters: parameters)
//            .responseJSON { response in
//                print(response.request)  // original URL request
//                print(response.response) // URL response
//                print(response.data)     // server data
//                print(response.result)   // result of response serialization
//                
//                if let JSON = response.result.value {
//                    print("JSON: \(JSON)")
//                }
//        }
        notificationLabel.hidden = false;
        notificationLabel.text = "Sign in Success!"
        notificationLabel.textColor = UIColor.greenColor()
    }
}
