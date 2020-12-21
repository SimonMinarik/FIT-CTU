//
//  ProfileViewController.swift
//  FITstagram
//
//  Created by Lukáš Hromadník on 26/10/2020.
//

import UIKit

final class ProfileViewController: UIViewController {
    private weak var profileImageView: UIImageView!
    private weak var usernameLabel: UILabel!
    private weak var editUsernameButton: UIButton!
    private weak var postsLabel: UILabel!
    private weak var descriptionLabel: UILabel!
    
    private weak var collectionView: UICollectionView!
    
    var descriptionText = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Fusce nibh. Etiam sapien elit, consequat eget, tristique non, venenatis quis, ante. Nunc tincidunt ante vitae massa. Ut in tortor nulla. Sed lobortis ornare porta. Ut dapibus semper nisl, quis imperdiet massa efficitur nec. Donec magna lorem, interdum nec dui in, posuere dapibus ex. Etiam porttitor sem a venenatis ornare. Duis sodales ipsum eget vestibulum auctor. Sed pellentesque sed ipsum ac consequat. Donec quis vehicula nunc."
    
    private var textRegistration: UICollectionView.CellRegistration<UICollectionViewCell, String>!
    private var imageRegistration: UICollectionView.CellRegistration<UICollectionViewCell, UIImage>!
    
    private let viewModel: ProfileViewModeling
    
    // MARK: - Initialization
    
    init(viewModel: ProfileViewModeling) {
        self.viewModel = viewModel
        
        super.init(nibName: nil, bundle: nil)
    }
    
    @available(*, unavailable)
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    // MARK: - Lifecycle
    
    override func loadView() {
        super.loadView()
        
        view.backgroundColor = .white
        
        let profileImageView = UIImageView(image: UIImage(named: "image"))
        profileImageView.backgroundColor = .lightGray
        profileImageView.layer.cornerRadius = 4
        profileImageView.layer.borderWidth = 1
        profileImageView.layer.borderColor = UIColor.darkGray.cgColor
        profileImageView.contentMode = .scaleAspectFill
        profileImageView.clipsToBounds = true
        view.addSubview(profileImageView)
        profileImageView.translatesAutoresizingMaskIntoConstraints = false
        NSLayoutConstraint.activate([
            profileImageView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 20),
            profileImageView.leadingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leadingAnchor, constant: 16),
            profileImageView.heightAnchor.constraint(equalToConstant: 120),
            profileImageView.widthAnchor.constraint(equalToConstant: 120)
        ])
        self.profileImageView = profileImageView
        
        let usernameLabel = UILabel()
        usernameLabel.text = viewModel.username
        usernameLabel.font = .systemFont(ofSize: 36)
        self.usernameLabel = usernameLabel
        
        let editUsernameButton = UIButton(type: .system)
        editUsernameButton.setImage(UIImage(systemName: "pencil"), for: .normal)
        editUsernameButton.setContentCompressionResistancePriority(.required, for: .horizontal)
        self.editUsernameButton = editUsernameButton
        
        let usernameStackView = UIStackView(arrangedSubviews: [usernameLabel, editUsernameButton])
        usernameStackView.spacing = 8
        view.addSubview(usernameStackView)
        usernameStackView.translatesAutoresizingMaskIntoConstraints = false
        NSLayoutConstraint.activate([
            usernameStackView.topAnchor.constraint(equalTo: profileImageView.topAnchor),
            usernameStackView.leadingAnchor.constraint(equalTo: profileImageView.trailingAnchor, constant: 16),
            usernameStackView.trailingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.trailingAnchor, constant: -16),
        ])
        
        let postsLabel = UILabel()
        postsLabel.font = .systemFont(ofSize: 16)
        view.addSubview(postsLabel)
        postsLabel.translatesAutoresizingMaskIntoConstraints = false
        NSLayoutConstraint.activate([
            postsLabel.topAnchor.constraint(equalTo: editUsernameButton.bottomAnchor, constant: 16),
            postsLabel.leadingAnchor.constraint(equalTo: profileImageView.trailingAnchor, constant: 16),
        ])
        self.postsLabel = postsLabel
        
        let layout = UICollectionViewFlowLayout()
        layout.minimumLineSpacing = 0
        layout.minimumInteritemSpacing = 0
        
        let collectionView = UICollectionView(frame: .zero, collectionViewLayout: layout)
        collectionView.backgroundColor = .white
        collectionView.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(collectionView)
        NSLayoutConstraint.activate([
            collectionView.topAnchor.constraint(equalTo: profileImageView.bottomAnchor, constant: 16),
            collectionView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            collectionView.bottomAnchor.constraint(equalTo: view.bottomAnchor),
            collectionView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
        ])
        self.collectionView = collectionView
        
        updateData()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        collectionView.dataSource = self
        collectionView.delegate = self
        
        textRegistration = UICollectionView.CellRegistration<UICollectionViewCell, String> { cell, indexPath, item in
            cell.contentConfiguration = TextConfiguration(text: item)
        }
        imageRegistration = UICollectionView.CellRegistration<UICollectionViewCell, UIImage> { cell, indexPath, item in
            cell.contentConfiguration = ImageConfiguration(image: item)
        }
        
        let editUsernameAction = UIAction { [weak self] _ in
            let alert = UIAlertController(
                title: "Change username",
                message: "Changing username will sign you in as a different user.",
                preferredStyle: .alert
            )
            alert.addTextField { [weak self] textField in
                textField.text = self?.viewModel.username
                textField.placeholder = "Username"
            }
            alert.addAction(UIAlertAction(title: "Cancel", style: .cancel))
            alert.addAction(UIAlertAction(title: "OK", style: .default) { _ in
                self?.viewModel.username = alert.textFields?.first?.text ?? ""
            })
            self?.present(alert, animated: true)
        }
        editUsernameButton.addAction(editUsernameAction, for: .touchUpInside)
        
        viewModel.viewModelDidChange = { [weak self] viewModel in
            self?.usernameLabel.text = viewModel.username
            self?.updateData()
        }
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
        viewModel.fetchPhotos()
    }
    
    // MARK: - Helpers
    
    private func thumbnailImageView(image: UIImage?) -> UIImageView {
        let thumbnailImageView = UIImageView(image: image)
        thumbnailImageView.backgroundColor = .lightGray
        thumbnailImageView.layer.borderWidth = 1
        thumbnailImageView.layer.borderColor = UIColor.darkGray.cgColor
        thumbnailImageView.translatesAutoresizingMaskIntoConstraints = false
        thumbnailImageView.contentMode = .scaleAspectFill
        thumbnailImageView.clipsToBounds = true
        NSLayoutConstraint.activate([
            thumbnailImageView.heightAnchor.constraint(equalTo: thumbnailImageView.widthAnchor)
        ])
        
        return thumbnailImageView
    }
    
    private func updateData() {
        postsLabel.text = "posts: \(viewModel.photos.count)"
        collectionView.reloadData()
    }
}

extension ProfileViewController: UICollectionViewDataSource {
    func numberOfSections(in collectionView: UICollectionView) -> Int {
        2
    }
    
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        section == 0 ? 1 : viewModel.photos.count
    }
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        if indexPath.section == 0 {
            return collectionView.dequeueConfiguredReusableCell(using: textRegistration, for: indexPath, item: descriptionText)
        } else {
            return collectionView.dequeueConfiguredReusableCell(using: imageRegistration, for: indexPath, item: viewModel.photos[indexPath.item].image)
        }
    }
}

extension ProfileViewController: UICollectionViewDelegateFlowLayout {
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, sizeForItemAt indexPath: IndexPath) -> CGSize {
        if indexPath.section == 0 && indexPath.item == 0 {
            let contentView = TextContentView(configuration: TextConfiguration(text: descriptionText))
            return contentView.systemLayoutSizeFitting(
                CGSize(width: collectionView.frame.width, height: 0),
                withHorizontalFittingPriority: .required,
                verticalFittingPriority: .defaultLow
            )
        } else {
            let numberOfCols = CGFloat(3)
            let itemSize = floor(collectionView.frame.width / numberOfCols)
            
            /// Last column will be a bit wider on some devices, so we fill the whole screen
            if indexPath.item % Int(numberOfCols) == 0 {
                return CGSize(width: collectionView.frame.width - numberOfCols * itemSize + itemSize, height: itemSize)
            }
            
            return CGSize(width: itemSize, height: itemSize)
        }
    }
    
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, insetForSectionAt section: Int) -> UIEdgeInsets {
        if section == 0 {
            return UIEdgeInsets(top: 0, left: 16, bottom: 16, right: 16)
        }
        
        return .zero
    }
}
