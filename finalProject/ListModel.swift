//
//  ListModel.swift
//  finalProject
//
//  Created by Andy Chase on 12/6/15.
//  Copyright © 2015 Andy Chase. All rights reserved.
//

import UIKit

class ListModel: NSObject, UITableViewDataSource {
    var isGlobalListType:Bool!
    var rows = [
        UITableViewCell(),
        UITableViewCell(),
        UITableViewCell(),
        UITableViewCell()
    ]
    
    init(isGlobalListType:Bool) {
        self.isGlobalListType = isGlobalListType
        rows[3].textLabel!.text = "Text"
    }
    
    func tableView(tableView: UITableView,
        cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
            return rows[indexPath.row]
            
    }
    
    func tableView(tableView: UITableView,
        numberOfRowsInSection section: Int) -> Int {
            if (section == 0) {
                return rows.count
            }  else {
                return 0
            }
    }
    
}