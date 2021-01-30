//
//  ProfileViewController.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 27.01.2021.
//

import UIKit

final class ProfileViewController: UIViewController, UITextFieldDelegate {
    private var viewModel: ProfileViewModeling
    
    init?(coder: NSCoder, viewModel: ProfileViewModeling) {
        self.viewModel = viewModel
        super.init(coder: coder)
    }
    
    @available(*, unavailable, renamed: "init(coder:viewModel:)")
    required init?(coder: NSCoder) {
        self.viewModel = ProfileViewModel()
        super.init(coder: coder)
        //fatalError("You must create this view controller with a viewModel.")
    }
    
    @IBOutlet weak var usernameLabel: UILabel!
    
    override func loadView() {
        super.loadView()
        usernameLabel.text = viewModel.username
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        viewModel.viewModelDidChange = { [weak self] viewModel in
            self?.usernameLabel.text = viewModel.username
        }
    }
    
    @IBAction func changeUsernameButtonTapped(_ sender: UIButton) {
        let alert = UIAlertController(
            title: "Change username",
            message: "Changing username will sign you in as a different user. (max 20 characters)",
            preferredStyle: .alert
        )
        alert.addTextField { [weak self] textField in
            textField.delegate = self
            textField.text = self?.viewModel.username
            textField.placeholder = "Username"
        }
        alert.addAction(UIAlertAction(title: "Cancel", style: .cancel))
        alert.addAction(UIAlertAction(title: "OK", style: .default) { _ in
            self.viewModel.username = alert.textFields?.first?.text ?? ""
        })
        self.present(alert, animated: true)
    }
    
    public func textField(_ textField: UITextField, shouldChangeCharactersIn range: NSRange, replacementString string: String) -> Bool {
        return range.location < 20
    }
    
}
