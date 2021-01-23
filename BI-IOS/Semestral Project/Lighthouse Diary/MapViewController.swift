//
//  MapViewController.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 16.11.2020.
//

import UIKit

class MapViewController: UIViewController {
    @IBOutlet weak var searchButton: UIButton!
    @IBOutlet weak var layersButton: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationController!.navigationBar.setBackgroundImage(UIImage(), for: .default)
        self.navigationController!.navigationBar.shadowImage = UIImage()
        self.navigationController!.navigationBar.isTranslucent = true
        
        self.layersButton.layer.cornerRadius = 4.0
        self.layersButton.layer.masksToBounds = true
        
        self.searchButton.layer.cornerRadius = 4.0
        self.searchButton.layer.masksToBounds = true
    }
    @IBAction func layersButtonTapped(_ sender: UIButton) {
        print("layers button tapped")
    }
    
    @IBAction func searchButtonTapped(_ sender: UIButton) {
        print("search button tapped")
    }
}
