//
//  Preferences.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 30.01.2021.
//

import Foundation

struct Preferences {
    var bucketlist:[Int]
    var visited:[Int]
    var visited_dates:[String: String]
}

extension Preferences: Codable {
    enum CodingKeys: String, CodingKey {
        case bucketlist
        case visited
        case visited_dates
    }
    
    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)
        bucketlist = try container.decode([Int].self, forKey: .bucketlist)
        visited = try container.decode([Int].self, forKey: .visited)
        visited_dates = try container.decode([String: String].self, forKey: .visited_dates)
    }
}
