//
//  MapViewModel.swift
//  FITstagram
//
//  Created by Šimon Minárik on 12.12.2020.
//

import Foundation

protocol MapViewModeling: AnyObject {
    var posts: [Post] { get set }
    var viewModelDidChange: (MapViewModeling) -> Void { get set }
    
    func loadPhotos()
}

final class MapViewModel: MapViewModeling {
    var posts: [Post] = [] {
        didSet {
            DispatchQueue.main.async { [weak self] in
                guard let self = self else { return }
                self.viewModelDidChange(self)
            }
        }
    }
    
    var viewModelDidChange: (MapViewModeling) -> Void = { _ in }
    
    private let networkService: NetworkServicing
    
    // MARK: - Initialization
    
    init(networkService: NetworkServicing = NetworkService()) {
        self.networkService = networkService
    }
    
    // MARK: - Public methods
    
    func loadPhotos() {
        let url = "https://ackeeedu.000webhostapp.com/api.php/records/posts?filter=lat,gt,0&filter=lon,gt,0"
        networkService.fetch(url: url) { [weak self] result in
            switch result {
            case let .success(data):
                let decoded = try! JSONDecoder().decode(PostResponse.self, from: data)
                self?.posts = decoded.posts

            case .failure:
                break
            }
        }
    }
}
