//
//  DiaryViewModel.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 27.01.2021.
//

import UIKit

protocol DiaryViewModeling {
    var username:String { get }
    var visited:[Lighthouse] { get set }
    var visitedDates:[Int: String] { get set }
    var bucketlist:[Lighthouse] { get set }
    var viewModelDidChange: (DiaryViewModeling) -> Void { get set }
    
    func loadData()
}

final class DiaryViewModel: DiaryViewModeling {
    var username: String {
        get { UserDefaults.standard.string(forKey: "username") ?? "username" }
    }
    var visited: [Lighthouse] = []
    var visitedDates: [Int : String] = [:]
    var bucketlist: [Lighthouse] = []
    
    var viewModelDidChange: (DiaryViewModeling) -> Void = { _ in }
    
    private let networkService: NetworkServicing
    
    init(networkService: NetworkServicing = NetworkService()) {
        self.networkService = networkService
    }
    
    func loadData() {
        self.visited = [Lighthouse(id: 1, name: "Lighthouse Arkona", image: UIImage(named: "612664395a40232133447d33247d38313233393434333331.jpeg")!, location: "Puttgarten, Germany", description: "Lorem ipsum..", lat: 54.679564, lon: 13.432574)]
        self.visitedDates = [1: "23.8.2019"]
        self.bucketlist = [Lighthouse(id: 2, name: "Lighthouse Busum", image: UIImage(named: "leuchtturm-busum.jpg")!, location: "Busum, Germany", description: "Lorem ipsum dolor..", lat: 54.126885, lon: 8.858477)]
    }
}
