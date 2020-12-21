//
//  ProfileViewModel.swift
//  FITstagram
//
//  Created by Lukáš Hromadník on 11/11/2020.
//

import Foundation

protocol ProfileViewModeling: AnyObject {
    var username: String { get set }
    var photos: [Post] { get set }
    var viewModelDidChange: (ProfileViewModeling) -> Void { get set }
    
    func fetchPhotos()
}

final class ProfileViewModel: ProfileViewModeling {
    var username: String {
        get { UserDefaults.standard.string(forKey: "username") ?? "username" }
        set {
            UserDefaults.standard.setValue(newValue, forKey: "username")
            fetchPhotos()
            DispatchQueue.main.async { [weak self] in
                guard let self = self else { return }
                self.viewModelDidChange(self)
            }
        }
    }
    
    var photos: [Post] = [] {
        didSet {
            DispatchQueue.main.async { [weak self] in
                guard let self = self else { return }
                self.viewModelDidChange(self)
            }
        }
    }
    
    var viewModelDidChange: (ProfileViewModeling) -> Void = { _ in }
    
    private let networkService: NetworkServicing
    
    // MARK: - Initialization
    
    init(networkService: NetworkServicing = NetworkService()) {
        self.networkService = networkService
    }
    
    // MARK: - Public methods
    
    func fetchPhotos() {
        let url = "https://ackeeedu.000webhostapp.com/api.php/records/posts?filter=username,eq,\(username)"
        networkService.fetch(url: url) { [weak self] result in
            switch result {
            case let .success(data):
                let decoded = try! JSONDecoder().decode(PostResponse.self, from: data)
                self?.photos = decoded.posts
                
            case .failure:
                break
            }
        }
    }
}
