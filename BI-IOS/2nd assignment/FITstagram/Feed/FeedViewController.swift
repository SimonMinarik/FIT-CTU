//
//  FeedViewController.swift
//  FITstagram
//
//  Created by Jakub Olejník on 01.10.2020.
//

import UIKit
import CoreLocation

class FeedViewController: UIViewController {
    @IBOutlet weak var tableView: UITableView!
    private weak var refreshControl: UIRefreshControl!
    
    private var dataSource: UITableViewDiffableDataSource<Int, Post>!
    private let viewModel: FeedViewModeling
    
    // MARK: - Initialization
    
    init?(coder: NSCoder, viewModel: FeedViewModeling) {
        self.viewModel = viewModel
        super.init(coder: coder)
    }
    
    @available(*, unavailable)
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    // MARK: - Lifecycle
    
    override func loadView() {
        super.loadView()
        
        let refreshAction = UIAction { [weak self] _ in
            self?.viewModel.loadPhotos()
        }
        let refreshControl = UIRefreshControl(frame: .zero, primaryAction: refreshAction)
        tableView.refreshControl = refreshControl
        self.refreshControl = refreshControl
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        tableView.delegate = self
        
        dataSource = UITableViewDiffableDataSource(tableView: tableView) { tableView, indexPath, post in
            let cell = tableView.dequeueReusableCell(withIdentifier: "PostCell", for: indexPath) as! PostCell
            cell.post = post
            cell.personTapped = { [weak self] in self?.personTapped(in: post) }
            cell.photoHeader.locationTapped = { [weak self] in
                self?.locationTapped(in: post)
            }
            return cell
        }
    
        if viewModel.postId == -1 {
            navigationItem.title = "Feed"
            navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .add, target: self, action: #selector(addButtonTapped))
        } else {
            navigationItem.title = "Post"
        }
        
        navigationController?.navigationBar.isTranslucent = false
        
        viewModel.viewModelDidChange = { [weak self] viewModel in
            self?.applySnapshot()
        }
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
        viewModel.loadPhotos()
    }
    
    // MARK: - Actions
    
    private func personTapped(in post: Post) {
        let controller = DummyViewController(color: .red)
        controller.title = post.author

        navigationController?.pushViewController(controller, animated: true)
    }
    
    private func locationTapped(in post: Post) {
        guard
            let latitude = post.lat,
            let longitude = post.lon,
            let location = post.location
        else { return }
        let controller = PostMapViewController(
            viewModel: PostMapViewModel(
                coordinate: CLLocationCoordinate2D(latitude: latitude, longitude: longitude),
                locationTitle: location,
                postImage: post.image
            )
        )
        controller.title = post.location
        
        navigationController?.pushViewController(controller, animated: true)
    }
    
    @objc private func addButtonTapped() {
        let storyboard = UIStoryboard(name: "Main", bundle: nil)
        let controller = storyboard.instantiateViewController(identifier: "CreateViewController") {
            CreateViewController(coder: $0, viewModel: CreateViewModel())
        }
        let navigationController = UINavigationController(rootViewController: controller)
        present(navigationController, animated: true)
    }
    
    // MARK: - Private helpers

    private func applySnapshot() {
        var snapshot = NSDiffableDataSourceSnapshot<Int, Post>()
        snapshot.appendSections([0])
        snapshot.appendItems(viewModel.posts)
        dataSource.apply(snapshot)
        refreshControl.endRefreshing()
    }
}

extension FeedViewController: UITableViewDelegate {
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        print("TableView selected row")
        
        if viewModel.postId == -1 {
            tableView.deselectRow(at: indexPath, animated: true)
            
            guard let post = dataSource.itemIdentifier(for: indexPath) else { return }
            
            print("[POST_SELECTED]", post.author)
        }
    }
}
