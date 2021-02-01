//
//  DetailViewModel.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 27.01.2021.
//

import UIKit

protocol DetailViewModeling: AnyObject {
    var username:String { get }
    var lighthouse:Lighthouse { get set }
    var userData:UserData { get set }
    var viewModelDidChange: (DetailViewModeling) -> Void { get set }
    
    func loadUserData()
}

final class DetailViewModel: DetailViewModeling {
    var username: String {
        get { UserDefaults.standard.string(forKey: "username") ?? "username" }
    }
    var lighthouse: Lighthouse
    var userData: UserData
    var viewModelDidChange: (DetailViewModeling) -> Void = { _ in }
    
    private let networkService: NetworkServicing
    
    init(networkService: NetworkServicing = NetworkService(), lighthouse: Lighthouse, userData: UserData) {
        self.networkService = networkService
        self.lighthouse = lighthouse
        self.userData = userData
    }
    
    func loadUserData() {
        self.userData.visited = "23.8.2019"
        self.userData.photos = [UIImage(named: "612664395a40232133447d33247d38313233393434333331.jpeg")!.toString() ?? "", UIImage(named: "lighthouse-at-darsser-ort-with-museum-called-natureum-on-the-darss-peninsula-western-pomerania-lagoon-area-national-park-germany-R3PD9B.jpg")!.toString() ?? ""]
        self.userData.description = "Very cool lighthouse, 10/10 would recommend"
    }
    
}
