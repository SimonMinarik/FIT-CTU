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
    
    // MARK: - Initialization
    
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
    
    // MARK: - Life cycle
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        viewModel.loadData()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationController!.navigationBar.setBackgroundImage(UIImage(), for: .default)
        self.navigationController!.navigationBar.shadowImage = UIImage()
        self.navigationController!.navigationBar.isTranslucent = true
        
        self.tableView.delegate = self
        self.tableView.dataSource = self
                
        viewModel.viewModelDidChange = { [weak self] viewModel in
            guard let self = self else { return }
            self.tableView.reloadData()
        }
    }
    
    // MARK: - Actions
    
    @IBAction func segmentedControlChanged(_ sender: UISegmentedControl) {
        self.tableView.reloadData()
    }
    
    @IBAction func addButtonTapped(_ sender: UIButton) {
        let vc = self.storyboard?.instantiateViewController(identifier: "AddVC") {
            AddViewController(coder: $0, viewModel: AddViewModel(userPreferences: self.viewModel.userPreferences, type: self.segmentedControl.selectedSegmentIndex))
        }
        vc?.onDoneBlock = {
            vc?.dismiss(animated: true)
            self.viewModel.loadData()
        }
        present(vc!, animated: true)
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
            cell.visitedLabel.text = "Visited " +  viewModel.userPreferences.visited_dates[String(lighthouse.id)]!
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
        let vc = self.storyboard?.instantiateViewController(identifier: "DetailVC") {
            if self.segmentedControl.selectedSegmentIndex == 0 {
                return DetailViewController(coder: $0, viewModel: DetailViewModel(lighthouse: self.viewModel.visited[indexPath.row], userPreferences: self.viewModel.userPreferences, userLighthouseData: UserLighthouseData(type: "visited")))
            } else {
                return DetailViewController(coder: $0, viewModel: DetailViewModel(lighthouse: self.viewModel.bucketlist[indexPath.row], userPreferences: self.viewModel.userPreferences, userLighthouseData: UserLighthouseData(type: "bucketlist")))
            }
        }
        self.show(vc!, sender: self)
    }
}
