//
//  UserData.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 30.01.2021.
//

import Foundation

struct UserLighthouseData {
    var type:String
    var photos:[String]?
    var description:String?
}

extension UserLighthouseData: Codable {
    enum CodingKeys: String, CodingKey {
        case type
        case photos
        case description
    }
    
    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)
        type = try container.decode(String.self, forKey: .type)
        photos = try container.decode([String].self, forKey: .photos)
        description = try container.decode(String.self, forKey: .description)
    }
}
