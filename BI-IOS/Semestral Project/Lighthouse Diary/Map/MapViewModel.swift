//
//  MapViewModel.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 27.01.2021.
//

import UIKit

protocol MapViewModeling: AnyObject {
    var username: String { get }
    var lighthouses: [Lighthouse] { get }
    var preferences: Preferences { get }
    var viewModelDidChange: (MapViewModeling) -> Void { get set }
    
    func loadLighthouses()
    func loadPreferences()
}

final class MapViewModel: MapViewModeling {
    var username: String {
        get { UserDefaults.standard.string(forKey: "username") ?? "username" }
    }
    var lighthouses: [Lighthouse] = []
    var preferences: Preferences = Preferences(bucketlist: [], visited: [])
    
    var viewModelDidChange: (MapViewModeling) -> Void = { _ in }
    
    private let networkService: NetworkServicing
    
    init(networkService: NetworkServicing = NetworkService()) {
        self.networkService = networkService
    }
    
    func loadLighthouses() {
        self.lighthouses.append(Lighthouse(id: 1, name: "Lighthouse Arkona", image: UIImage(named: "612664395a40232133447d33247d38313233393434333331.jpeg")!, location: "Puttgarten, Germany", description: "Lorem ipsum..", lat: 54.679564, lon: 13.432574))
        self.lighthouses.append(Lighthouse(id: 2, name: "Lighthouse Busum", image: UIImage(named: "leuchtturm-busum.jpg")!, location: "Busum, Germany", description: "Lorem ipsum dolor..", lat: 54.126885, lon: 8.858477))
        self.lighthouses.append(Lighthouse(id: 3, name: "Lighthouse Darsser", image: UIImage(named: "lighthouse-at-darsser-ort-with-museum-called-natureum-on-the-darss-peninsula-western-pomerania-lagoon-area-national-park-germany-R3PD9B.jpg")!, location: "Born auf dem Darß, Germany", description: "Lorem ipsum dolor sit..", lat: 54.472806, lon: 12.502328))
    }
    
    func loadPreferences() {
        self.preferences = Preferences(bucketlist: [2], visited: [1])
    }
}
