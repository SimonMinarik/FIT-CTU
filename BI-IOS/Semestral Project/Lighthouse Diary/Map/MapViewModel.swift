//
//  MapViewModel.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 27.01.2021.
//

import UIKit
import Firebase
import FirebaseFirestoreSwift

protocol MapViewModeling: AnyObject {
    var username: String { get }
    var lighthouses: [Lighthouse] { get }
    var preferences: Preferences { get }
    var viewModelDidChange: (MapViewModeling) -> Void { get set }
    
    func loadLighthouses()
    func loadPreferences()
}

final class MapViewModel: MapViewModeling {
    var username: String {
        get {
            UserDefaults.standard.string(forKey: "username") ?? "username"
        }
    }
    var lighthouses: [Lighthouse] = []
    
    var preferences: Preferences = Preferences(bucketlist: [], visited: [], visited_dates: [:]) {
        didSet {
            DispatchQueue.main.async { [weak self] in
                guard let self = self else { return }
                self.viewModelDidChange(self)
            }
        }
    }
    
    var viewModelDidChange: (MapViewModeling) -> Void = { _ in }
    
    private let db = Firestore.firestore()
    
    // MARK: - Public methods
    
    func loadLighthouses() {
        db.collection("lighthouses").getDocuments() { (querySnapshot, err) in
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
    
    func loadPreferences() {
        let docRef = db.collection("user_preferences").document(self.username)
        docRef.getDocument { (document, error) in
            if let document = document, document.exists {
                let result = Result {
                    try document.data(as: Preferences.self)
                }
                switch result {
                case .success(let preferences):
                    if let preferences = preferences {
                        self.preferences = preferences
                    } else {
                        print("Document does not exist")
                    }
                case .failure(let error):
                    print("Error decoding preferences: \(error)")
                }
            } else {
                print("Document does not exist")
                self.preferences = Preferences(bucketlist: [], visited: [], visited_dates: [:])
            }
        }
    }
}
