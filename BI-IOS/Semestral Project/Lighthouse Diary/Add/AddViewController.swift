//
//  AddViewController.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 08.02.2021.
//

import UIKit

final class AddViewController: UIViewController, UITableViewDataSource, UITableViewDelegate {
    @IBOutlet weak var tableView: UITableView!
    
    private let viewModel: AddViewModeling
    
    var onDoneBlock: () -> Void = {  }
    
    // MARK: - Initialization
    
    init?(coder: NSCoder, viewModel: AddViewModeling) {
        self.viewModel = viewModel
        super.init(coder: coder)
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    // MARK: - Life cycle
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        viewModel.loadLighthouses()
        
        tableView.delegate = self
        tableView.dataSource = self
        
        viewModel.viewModelDidChange = { [weak self] viewModel in
            guard let self = self else { return }
            print("viewModelDidChange")
            self.tableView.reloadData()
        }
    }
    
    // MARK: - Actions
    
    @IBAction func closeButtonTapped(_ sender: UIBarButtonItem) {
        self.dismiss(animated: true)
    }
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return viewModel.lighthouses.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "DiaryCell") as! DiaryCell
        
        let lighthouse = viewModel.lighthouses[indexPath.row]
        cell.nameLabel.text = lighthouse.name
        cell.locationLabel.text = lighthouse.location
        cell.lighthouseImageView.image = lighthouse.image
        cell.lighthouseImageView.layer.cornerRadius = cell.lighthouseImageView.frame.size.width / 2
        
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        viewModel.sendPreferences(lighthouseId: viewModel.lighthouses[indexPath.row].id)
        onDoneBlock()
    }
}
