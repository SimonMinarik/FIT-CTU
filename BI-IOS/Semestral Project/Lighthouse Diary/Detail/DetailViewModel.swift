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
    func userPreferencesChanged(to: Int)
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
                self.viewModelDidChange(self)
            }
        }
    }
    
    var userPreferences: Preferences
        
    var viewModelDidChange: (DetailViewModeling) -> Void = { _ in }
    
    private let db = Firestore.firestore()
    
    // MARK: - Initialization
        
    init(lighthouse: Lighthouse, userPreferences: Preferences, userLighthouseData: UserLighthouseData) {
        self.lighthouse = lighthouse
        self.userPreferences = userPreferences
        self.userLighthouseData = userLighthouseData
    }
    
    // MARK: - Public methods
    
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
            print("Error writing userPreference to Firestore: \(error)")
        }
    }
    
    func changeUserPreference(from: Int, to: Int) {
        userPreferencesChanged(to: to)
        
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
    
    func userPreferencesChanged(to: Int) {
        switch to {
        case -1:
            userLighthouseData = UserLighthouseData(type: "")
            break
        case 0:
            let date = Date()
            let dateFormatter = DateFormatter()
            dateFormatter.dateFormat = "dd.MM.YYYY"
            let visited_date = dateFormatter.string(from: date)
            userLighthouseData = UserLighthouseData(type: "visited", photos: [], description: "")
            userPreferences.visited_dates["\(lighthouse.id)"] = visited_date
            break
        case 1:
            userLighthouseData = UserLighthouseData(type: "bucketlist")
            break
        default:
            break
        }
    }
}
