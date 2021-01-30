//
//  DiaryViewController.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 16.11.2020.
//

import UIKit

final class DiaryViewController: UIViewController, UITableViewDataSource, UITableViewDelegate {
    @IBOutlet weak var tableView: UITableView!
    @IBOutlet weak var segmentedControl: UISegmentedControl!
        
    private let viewModel: DiaryViewModeling
    
    init?(coder: NSCoder, viewModel: DiaryViewModeling) {
        self.viewModel = viewModel
        super.init(coder: coder)
    }
    
    @available(*, unavailable, renamed: "init(coder:viewModel:)")
    required init?(coder: NSCoder) {
        self.viewModel = DiaryViewModel()
        super.init(coder: coder)
        //fatalError("You must create this view controller with a viewModel.")
    }
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if (segmentedControl.selectedSegmentIndex == 0) {
            return viewModel.visited.count
        } else {
            return viewModel.bucketlist.count
        }
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        var lighthouse:Lighthouse
        let cell = tableView.dequeueReusableCell(withIdentifier: "DiaryCell") as! DiaryCell
        
        if (segmentedControl.selectedSegmentIndex == 0) {
            lighthouse = viewModel.visited[indexPath.row]
            cell.visitedLabel.text = viewModel.visitedDates[lighthouse.id]
        } else {
            lighthouse = viewModel.bucketlist[indexPath.row]
            cell.visitedLabel.text = ""
        }
        
        cell.nameLabel.text = lighthouse.name
        cell.locationLabel.text = lighthouse.location
        cell.lighthouseImageView.image = lighthouse.image
        cell.lighthouseImageView.layer.cornerRadius = cell.lighthouseImageView.frame.size.width / 2
        
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let vc = self.storyboard?.instantiateViewController(identifier: "detailVC") {
            if self.segmentedControl.selectedSegmentIndex == 0 {
                return DetailViewController(coder: $0, viewModel: DetailViewModel(lighthouse: self.viewModel.visited[indexPath.row]))
            } else {
                return DetailViewController(coder: $0, viewModel: DetailViewModel(lighthouse: self.viewModel.bucketlist[indexPath.row]))
            }
        }
        self.show(vc!, sender: self)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationController!.navigationBar.setBackgroundImage(UIImage(), for: .default)
        self.navigationController!.navigationBar.shadowImage = UIImage()
        self.navigationController!.navigationBar.isTranslucent = true
        
        tableView.dataSource = self
        tableView.delegate = self
        viewModel.loadData()
    }
    
    @IBAction func segmentedControlChanged(_ sender: UISegmentedControl) {
        self.tableView.reloadData()
    }
}
