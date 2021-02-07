//
//  DetailViewModel.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 27.01.2021.
//

import UIKit
import FirebaseFirestore

protocol DetailViewModeling: AnyObject {
    var username: String { get }
    var lighthouse: Lighthouse { get set }
    var userLighthouseData: UserLighthouseData { get set }
    var userPreferences: Preferences { get set }
    var viewModelDidChange: (DetailViewModeling) -> Void { get set }
    
    func loadUserData()
    func saveUserLighthouseData()
    func saveUserPreferences()
    func changeUserPreference(from: Int, to: Int)
}

final class DetailViewModel: DetailViewModeling {
    var username: String {
        get { UserDefaults.standard.string(forKey: "username") ?? "username" }
    }
    var lighthouse: Lighthouse
    var userLighthouseData: UserLighthouseData {
        didSet {
            DispatchQueue.main.async { [weak self] in
                guard let self = self else { return }
                print("userlighthouseData didSet")
                self.viewModelDidChange(self)
            }
        }
    }
    
    var userPreferences: Preferences
        
    var viewModelDidChange: (DetailViewModeling) -> Void = { _ in }
    
    private let db = Firestore.firestore()
        
    init(lighthouse: Lighthouse, userPreferences: Preferences, userLighthouseData: UserLighthouseData) {
        self.lighthouse = lighthouse
        self.userPreferences = userPreferences
        self.userLighthouseData = userLighthouseData
    }
    
    func loadUserData() {
        if self.userLighthouseData.type == "visited" {
            let docRef = db.collection("users").document(self.username).collection("lighthouses").document("\(self.lighthouse.id)")
            docRef.getDocument { (document, error) in
                if let document = document, document.exists {
                    let result = Result {
                        try document.data(as: UserLighthouseData.self)
                    }
                    switch result {
                    case .success(let userLighthouseData):
                        if let userLighthouseData = userLighthouseData {
                            self.userLighthouseData = userLighthouseData
                        } else {
                            print("Document does not exist")
                        }
                    case .failure(let error):
                        print("Error decoding preferences: \(error)")
                    }
                } else {
                    print("Document does not exist")
                    self.userLighthouseData = UserLighthouseData(type: "")
                }
            }
        }
    }
    
    func saveUserLighthouseData() {
        do {
            try db.collection("users").document(self.username).collection("lighthouses").document("\(self.lighthouse.id)").setData(from: userLighthouseData)
        } catch let error {
            print("Error writing userLighthouseData to Firestore: \(error)")
        }
    }
    
    func saveUserPreferences() {
        do {
            try db.collection("user_preferences").document(self.username).setData(from: userPreferences)
        } catch let error {
            print("Error writing userPrefference to Firestore: \(error)")
        }
    }
    
    func changeUserPreference(from: Int, to: Int) {
        print("from: \(from) to: \(to)")
        switch from {
        case 0:
            db.collection("users").document(self.username).collection("lighthouses").document("\(self.lighthouse.id)").delete() { err in
                if let err = err {
                    print("Error removing document: \(err)")
                } else {
                    print("Document successfully removed!")
                }
            }
            if let index = userPreferences.visited.firstIndex(of: lighthouse.id) {
                userPreferences.visited.remove(at: index)
            }
            break
        case 1:
            print("trying delete bucketlist item with id: \(lighthouse.id)")
            if let index = userPreferences.bucketlist.firstIndex(of: lighthouse.id) {
                userPreferences.bucketlist.remove(at: index)
            }
            break
        default:
            break
        }
        
        switch to {
        case 0:
            saveUserLighthouseData()
            userPreferences.visited.append(lighthouse.id)
            break
        case 1:
            userPreferences.bucketlist.append(lighthouse.id)
            break
        default:
            break
        }
        saveUserPreferences()
    }
}
