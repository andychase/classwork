//
//  FirstViewController.swift
//  finalProject
//
//  Created by Andy Chase on 12/5/15.
//  Copyright © 2015 Andy Chase. All rights reserved.
//

import UIKit

class ListViewController: UIViewController {
    var userId:String!
    var listType:Bool!
    var dataSource:ListModel!

    @IBOutlet var table: UITableView!
    @IBOutlet weak var inputField: UITextField!
    
    override func viewDidLoad() {
        self.dataSource = ListModel(table: table, isGlobalListType: self.restorationIdentifier == "globalList")
        
            table.dataSource = self.dataSource
            table.delegate = self.dataSource
    }

    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
    }
    override func viewDidAppear(animated: Bool) {
        table.setEditing(true, animated: true)
    }
    @IBAction func addButtonPress(sender: AnyObject) {
        if let text = inputField.text {
            if text != "" {
                self.dataSource.addItem(text)
                inputField.text = ""
            }
        }

    }
    
    
}

