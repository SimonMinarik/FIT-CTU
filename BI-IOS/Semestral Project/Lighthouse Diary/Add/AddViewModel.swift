//
//  AddViewModel.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 08.02.2021.
//

import Foundation
import FirebaseFirestore

protocol AddViewModeling: AnyObject {
    var username: String { get }
    var type: Int { get set }
    var userPreferences: Preferences { get }
    var lighthouses: [Lighthouse] { get set }
    var viewModelDidChange: (AddViewModeling) -> Void { get set }
    
    func loadLighthouses()
    func sendPreferences(lighthouseId: Int)
}

final class AddViewModel: AddViewModeling {
    var username: String {
        get { UserDefaults.standard.string(forKey: "username") ?? "username" }
    }
    var type: Int
    var userPreferences: Preferences
    var lighthouses: [Lighthouse] = [] {
        didSet {
            DispatchQueue.main.async { [weak self] in
                guard let self = self else { return }
                self.viewModelDidChange(self)
            }
        }
    }
    var viewModelDidChange: (AddViewModeling) -> Void = { _ in }
    
    private let db = Firestore.firestore()
    
    // MARK: - Initialization
    
    init(userPreferences: Preferences, type: Int) {
        self.userPreferences = userPreferences
        self.type = type
    }
    
    // MARK: - Public methods
    
    func loadLighthouses() {
        var docRef: AnyObject
        if userPreferences.visited.isEmpty && userPreferences.bucketlist.isEmpty {
            docRef = db.collection("lighthouses")
        } else {
            docRef = db.collection("lighthouses").whereField("id", notIn: self.userPreferences.visited + self.userPreferences.bucketlist)
        }
        
        docRef.getDocuments() { (querySnapshot, err) in
            if let err = err {
                print("Error getting documents: \(err)")
            } else {
                for document in querySnapshot!.documents {
                    let result = Result {
                        try document.data(as: Lighthouse.self)
                    }
                    switch result {
                    case .success(let lighthouse):
                        if let lighthouse = lighthouse {
                            self.lighthouses.append(lighthouse)
                        } else {
                            print("Document does not exist")
                        }
                    case .failure(let error):
                        print("Error decoding lighthouse: \(error)")
                    }
                }
            }
        }
    }
    
    func sendPreferences(lighthouseId: Int) {
        if type == 0 {
            userPreferences.visited.append(lighthouseId)
            let dateFormatter = DateFormatter()
            dateFormatter.dateFormat = "dd.MM.YYYY"
            let visited_date = dateFormatter.string(from: Date())
            userPreferences.visited_dates["\(lighthouseId)"] = visited_date
            let userLighthouseData = UserLighthouseData(type: "visited", photos: [], description: "")
            
            saveUserPreferences()
            saveUserLighthouseData(lighthouseId: lighthouseId, userLighthouseData: userLighthouseData)
        } else {
            userPreferences.bucketlist.append(lighthouseId)
            saveUserPreferences()
        }
    }
    
    func saveUserLighthouseData(lighthouseId: Int, userLighthouseData: UserLighthouseData) {
        do {
            try db.collection("users").document(self.username).collection("lighthouses").document("\(lighthouseId)").setData(from: userLighthouseData)
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
}
