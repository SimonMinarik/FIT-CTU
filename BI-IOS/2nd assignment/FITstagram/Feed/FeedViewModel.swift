//
//  FeedViewModel.swift
//  FITstagram
//
//  Created by Lukáš Hromadník on 11/11/2020.
//

import Foundation

protocol FeedViewModeling: AnyObject {
    var posts: [Post] { get set }
    var postId: Int { get }
    var viewModelDidChange: (FeedViewModeling) -> Void { get set }
    
    func loadPhotos()
}

final class FeedViewModel: FeedViewModeling {
    var posts: [Post] = [] {
        didSet {
            DispatchQueue.main.async { [weak self] in
                guard let self = self else { return }
                self.viewModelDidChange(self)
            }
        }
    }
    var postId: Int
    var viewModelDidChange: (FeedViewModeling) -> Void = { _ in }
    
    private let networkService: NetworkServicing
    
    // MARK: - Initialization
    
    init(networkService: NetworkServicing = NetworkService(), postId: Int = -1) {
        self.networkService = networkService
        self.postId = postId
    }
    
    // MARK: - Public methods
    
    func loadPhotos() {
        let url: String
        if postId == -1 {
            url = "https://ackeeedu.000webhostapp.com/api.php/records/posts?order=id,desc"
        } else {
            url = "https://ackeeedu.000webhostapp.com/api.php/records/posts/\(self.postId)"
        }
        
        networkService.fetch(url: url) { [weak self] result in
            switch result {
            case let .success(data):
                if self?.postId == -1 {
                    let decoded = try! JSONDecoder().decode(PostResponse.self, from: data)
                    self?.posts = decoded.posts
                } else {
                    let decoded = try! JSONDecoder().decode(Post.self, from: data)
                    self?.posts = [decoded]
                }
            
            case .failure:
                break
            }
        }
    }
}
