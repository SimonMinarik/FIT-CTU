//
//  Lighthouse.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 27.01.2021.
//

import UIKit
import CoreLocation

struct Lighthouse: Hashable {
    let id: Int
    let name: String
    let image: UIImage?
    let location: String?
    let description: String?
    let lat: Double
    let lon: Double
}

extension Lighthouse: Decodable {
    enum CodingKeys: String, CodingKey {
        case id
        case name
        case image
        case location
        case description
        case lat
        case lon
    }
    
    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)
        id = try container.decode(Int.self, forKey: .id)
        
        let imageString = try container.decode(String.self, forKey: .image)
        image = imageString.toImage()
        
        name = try container.decode(String.self, forKey: .name)
        location = try container.decodeIfPresent(String.self, forKey: .location)
        description = try container.decode(String.self, forKey: .description)
        lat = try container.decode(Double.self, forKey: .lat)
        lon = try container.decode(Double.self, forKey: .lon)
    }
}

