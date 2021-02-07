//
//  ProfileViewModel.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 27.01.2021.
//

import UIKit
import FirebaseFirestore

protocol ProfileViewModeling: AnyObject {
    var username: String { get set }
    var profilePicture: String? { get set }
    var viewModelDidChange: (ProfileViewModeling) -> Void { get set }
    
    func loadProfilePicture()
    func addNewUser()
    func changeProfilePicture()
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
    var profilePicture: String? {
        didSet {
            DispatchQueue.main.async { [weak self] in
                guard let self = self else { return }
                self.viewModelDidChange(self)
                if self.profilePicture != "" {
                    self.changeProfilePicture()
                }
            }
        }
    }
    
    var viewModelDidChange: (ProfileViewModeling) -> Void = { _ in }
    
    private let db = Firestore.firestore()
    
    func loadProfilePicture() {
        let docRef = db.collection("users").document(self.username)

        docRef.getDocument { (document, error) in
            if let document = document, document.exists {
                let data = document.data()?["profileImage"] as! String
                if data != "" {
                    self.profilePicture = data
                }
            } else {
                self.addNewUser()
                self.profilePicture = ""
            }
        }
    }
    
    func addNewUser() {
        db.collection("users").document(self.username).setData([
            "profileImage": ""
        ]) { err in
            if let err = err {
                print("Error writing document: \(err)")
            } else {
                print("New user document successfully written!")
            }
        }
        
        db.collection("user_preferences").document(self.username).setData([
            "bucketlist": [],
            "visited": [],
            "visited_dates": [:]
        ]) { err in
            if let err = err {
                print("Error writing document: \(err)")
            } else {
                print("New user's preferences document successfully written!")
            }
        }
    }
    
    func changeProfilePicture() {
        db.collection("users").document(self.username).setData([
            "profileImage": profilePicture!
        ]) { err in
            if let err = err {
                print("Error writing document: \(err)")
            } else {
                print("User's profile picture successfully changed!")
            }
        }
    }
}
