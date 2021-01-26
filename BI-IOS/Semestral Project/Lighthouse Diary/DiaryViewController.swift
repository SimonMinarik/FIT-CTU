//
//  DiaryViewController.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 16.11.2020.
//

import UIKit

class DiaryViewController: UIViewController, UITableViewDataSource, UITableViewDelegate {
    @IBOutlet weak var tableView: UITableView!
    
    private let lighthouses:[(name: String, image: String, visited: String)] = [
        (name: "Lighthouse Arkona", image: "612664395a40232133447d33247d38313233393434333331.jpeg", visited: "23.8.2019"),
        (name: "Lighthouse Darsser", image: "lighthouse-at-darsser-ort-with-museum-called-natureum-on-the-darss-peninsula-western-pomerania-lagoon-area-national-park-germany-R3PD9B.jpg", visited: "23.8.2019"),
        (name: "Lighthouse Busum", image: "leuchtturm-busum.jpg", visited: "28.8.2019"),
        (name: "Lighthouse Arkona", image: "612664395a40232133447d33247d38313233393434333331.jpeg", visited: "23.8.2019"),
        (name: "Lighthouse Darsser", image: "lighthouse-at-darsser-ort-with-museum-called-natureum-on-the-darss-peninsula-western-pomerania-lagoon-area-national-park-germany-R3PD9B.jpg", visited: "23.8.2019"),
        (name: "Lighthouse Busum", image: "leuchtturm-busum.jpg", visited: "28.8.2019")]
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return lighthouses.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "DiaryCell") as! DiaryCell
        cell.nameLabel.text = lighthouses[indexPath.row].name
        cell.lighthouseImageView.image = UIImage(named: lighthouses[indexPath.row].image)
        cell.lighthouseImageView.layer.cornerRadius = cell.lighthouseImageView.frame.size.width / 2
        cell.visitedLabel.text = lighthouses[indexPath.row].visited
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let vc = self.storyboard?.instantiateViewController(withIdentifier: "detailViewController")
        self.show(vc!, sender: self)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationController!.navigationBar.setBackgroundImage(UIImage(), for: .default)
        self.navigationController!.navigationBar.shadowImage = UIImage()
        self.navigationController!.navigationBar.isTranslucent = true
        
        tableView.dataSource = self
        tableView.delegate = self
    }
}
