//
//  ProfileViewController.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 27.01.2021.
//

import UIKit

final class ProfileViewController: UIViewController, UITextFieldDelegate {
    @IBOutlet weak var usernameLabel: UILabel!
    @IBOutlet weak var profilePictureImageView: UIImageView!
    
    private let viewModel: ProfileViewModeling
    
    // MARK: - Initialization
    
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
    
    // MARK: - Life cycle
    
    override func loadView() {
        super.loadView()
        usernameLabel.text = viewModel.username
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        viewModel.loadProfilePicture()
        
        viewModel.viewModelDidChange = { [weak self] viewModel in
            guard let self = self else { return }
            self.usernameLabel.text = viewModel.username
            if self.viewModel.profilePicture != "" {
                self.profilePictureImageView.image = viewModel.profilePicture?.toImage()
            } else {
                self.profilePictureImageView.image = UIImage(named: "blank-profile-picture-973460_640.png")
            }
        }
    }
    
    // MARK: - Actions
    
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
    
    @IBAction func changeProfilePictureButtonTapped(_ sender: UIButton) {
        let imagePicker = UIImagePickerController()
        imagePicker.delegate = self
        present(imagePicker, animated: true)
    }
    
    public func textField(_ textField: UITextField, shouldChangeCharactersIn range: NSRange, replacementString string: String) -> Bool {
        return range.location < 20
    }
}

extension ProfileViewController: UIImagePickerControllerDelegate, UINavigationControllerDelegate {
    func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        picker.dismiss(animated: true)
    }
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        let image = info[.originalImage] as? UIImage
        if let resizedImage = resizeImage(with: image, scaledToFill: CGSize(width: profilePictureImageView.frame.width, height: profilePictureImageView.frame.height))?.jpegData(compressionQuality: 0) {
            viewModel.profilePicture = resizedImage.base64EncodedString()
        }
        
        picker.dismiss(animated: true)
    }
}
