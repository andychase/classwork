//
//  TabController.swift
//  finalProject
//
//  Created by Andy Chase on 12/5/15.
//  Copyright © 2015 Andy Chase. All rights reserved.
//

import UIKit

class TabBarController: UITabBarController {
    var userId:String!

    override func viewDidLoad() {
        self.viewControllers!.forEach({ (v:UIViewController) -> () in
            if let c = v as? ListViewController {
                c.userId = self.userId;
            }
        })
    }
}