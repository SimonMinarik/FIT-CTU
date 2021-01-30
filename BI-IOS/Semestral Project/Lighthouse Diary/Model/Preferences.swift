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
}

extension Preferences: Codable {
    enum CodingKeys: String, CodingKey {
        case bucketlist
        case visited
    }
    
    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)
        bucketlist = try container.decode([Int].self, forKey: .bucketlist)
        visited = try container.decode([Int].self, forKey: .visited)
    }

    func encode(to encoder: Encoder) throws {
        var container = encoder.container(keyedBy: CodingKeys.self)
        try container.encode(bucketlist, forKey: .bucketlist)
        try container.encode(visited, forKey: .visited)
    }
}
