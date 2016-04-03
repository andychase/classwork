//
//  ListWebModel.swift
//  finalProject
//
//  Created by Andy Chase on 12/6/15.
//  Copyright © 2015 Andy Chase. All rights reserved.
//

import Alamofire

class ListWebModel: NSObject {
    static func getListItems(userList:String, userId:String, callback: (list:[String]) -> Void) {
        
        let parameters = ["get_user_list": userList, "user": userId]
        Alamofire.request(.GET, "http://127.0.0.1:5000/get", parameters: parameters)
            .responseJSON { response in
                if let JSON = response.result.value {
                    if let list = JSON["list"] as? [String] {
                        callback(list: list)
                    }
                }
        }
    }
    
    static func setListItems(userList:String, userId:String, data:[String]) {
        let parameters:[String:AnyObject] = ["get_user_list": userList, "user": userId, "data": data]
        Alamofire.request(.POST, "http://127.0.0.1:5000/set", parameters: parameters, encoding: .JSON)
            .responseJSON { response in
        }
    }

}