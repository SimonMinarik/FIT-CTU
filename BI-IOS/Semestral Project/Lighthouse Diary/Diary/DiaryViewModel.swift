//
//  DiaryViewModel.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 27.01.2021.
//

import UIKit
import FirebaseFirestore

protocol DiaryViewModeling: AnyObject {
    var username:String { get }
    var visited:[Lighthouse] { get set }
    var userPreferences:Preferences { get set }
    var bucketlist:[Lighthouse] { get set }
    var viewModelDidChange: (DiaryViewModeling) -> Void { get set }
    
    func loadData()
}

final class DiaryViewModel: DiaryViewModeling {
    var username: String {
        get { UserDefaults.standard.string(forKey: "username") ?? "username" }
    }
    
    var userPreferences: Preferences = Preferences(bucketlist: [], visited: [], visited_dates: [:]) {
        didSet {
            DispatchQueue.main.async { [weak self] in
                guard let self = self else { return }
                self.loadLighthouses()
            }
        }
    }
    
    var visited: [Lighthouse] = [] {
        didSet {
            DispatchQueue.main.async { [weak self] in
                guard let self = self else { return }
                self.viewModelDidChange(self)
            }
        }
    }
    var bucketlist: [Lighthouse] = [] {
        didSet {
            DispatchQueue.main.async { [weak self] in
                guard let self = self else { return }
                self.viewModelDidChange(self)
            }
        }
    }
    
    var viewModelDidChange: (DiaryViewModeling) -> Void = { _ in }
    
    private let db = Firestore.firestore()
    
    // MARK: - Public methods
    
    func loadData() {
        let docRef = db.collection("user_preferences").document(username)
        docRef.getDocument { (document, err) in
            if let err = err {
                print("Error getting documents: \(err)")
            } else {
                let result = Result {
                    try document?.data(as: Preferences.self)
                }
                switch result {
                case .success(let preferences):
                    if let preferences = preferences {
                        self.userPreferences = preferences
                    } else {
                        print("Document does not exist")
                    }
                case .failure(let error):
                    print("Error decoding preferences: \(error)")
                }
            }
        }
    }
    
    func loadLighthouses() {
        visited = []
        bucketlist = []
        if self.userPreferences.visited.count > 0 {
            let docRef = db.collection("lighthouses").whereField("id", in: self.userPreferences.visited)
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
                                self.visited.append(lighthouse)
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
        
        if self.userPreferences.bucketlist.count > 0 {
            let docRef2 = db.collection("lighthouses").whereField("id", in: self.userPreferences.bucketlist)
            docRef2.getDocuments() { (querySnapshot, err) in
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
                                self.bucketlist.append(lighthouse)
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
    }
}
