//
//  Post.swift
//  FITstagram
//
//  Created by Lukáš Hromadník on 04/11/2020.
//

import UIKit

struct PostResponse: Codable {
    let posts: [Post]
}

extension PostResponse {
    enum CodingKeys: String, CodingKey {
        case posts = "records"
    }
}

struct Post: Hashable {
    let id: Int
    let image: UIImage?
    let author: String
    let caption: String
    let lat: Double?
    let lon: Double?
    let location: String?
}

extension Post: Codable {
    enum CodingKeys: String, CodingKey {
        case id
        case image
        case author = "username"
        case caption
        case lat
        case lon
        case location
    }
    
    init(from decoder: Decoder) throws {
        let container = try decoder.container(keyedBy: CodingKeys.self)
        id = try container.decode(Int.self, forKey: .id)
        
        let imageString = try container.decode(String.self, forKey: .image)
        let imageData = Data(base64Encoded: imageString) ?? Data()
        image = UIImage(data: imageData)
        
        author = try container.decode(String.self, forKey: .author)
        caption = try container.decode(String.self, forKey: .caption)
        lat = try container.decodeIfPresent(Double.self, forKey: .lat)
        lon = try container.decodeIfPresent(Double.self, forKey: .lon)
        location = try container.decodeIfPresent(String.self, forKey: .location)
    }

    func encode(to encoder: Encoder) throws {
        var container = encoder.container(keyedBy: CodingKeys.self)
        try container.encode(id, forKey: .id)
        try container.encode(image?.jpegData(compressionQuality: 0.5)?.base64EncodedString(), forKey: .image)
        try container.encode(author, forKey: .author)
        try container.encode(caption, forKey: .caption)
        try container.encode(lat, forKey: .lat)
        try container.encode(lon, forKey: .lon)
        try container.encode(location, forKey: .location)
    }
}
