//
//  UserData.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 30.01.2021.
//

import UIKit

struct UserData {
    var visited:String
    var photos:[String]
    var description:String
}

extension UserData: Codable {
    enum CodingKeys: String, CodingKey {
        case visited
        case photos
        case description
    }
    
    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)
        visited = try container.decode(String.self, forKey: .visited)
        photos = try container.decode([String].self, forKey: .photos)
        description = try container.decode(String.self, forKey: .description)
    }

    func encode(to encoder: Encoder) throws {
        var container = encoder.container(keyedBy: CodingKeys.self)
        try container.encode(visited, forKey: .visited)
        try container.encode(photos, forKey: .photos)
        try container.encode(description, forKey: .description)
    }
}
