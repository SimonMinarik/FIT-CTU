//
//  ProfileViewModel.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 27.01.2021.
//

import UIKit

protocol ProfileViewModeling: AnyObject {
    var username: String { get set }
    var profilePicture: UIImage? { get set }
    var viewModelDidChange: (ProfileViewModeling) -> Void { get set }
    
    func loadProfilePicture()
}

final class ProfileViewModel: ProfileViewModeling {
    var username: String {
        get { UserDefaults.standard.string(forKey: "username") ?? "username" }
        set {
            UserDefaults.standard.setValue(newValue, forKey: "username")
            loadProfilePicture()
            DispatchQueue.main.async { [weak self] in
                guard let self = self else { return }
                self.viewModelDidChange(self)
            }
        }
    }
    var profilePicture: UIImage?
    
    var viewModelDidChange: (ProfileViewModeling) -> Void = { _ in }
    
    private let networkService: NetworkServicing
    
    init(networkService: NetworkServicing = NetworkService()) {
        self.networkService = networkService
    }
    
    func loadProfilePicture() {
        self.profilePicture = UIImage(named: "IMG_6567.PNG")
    }
}
