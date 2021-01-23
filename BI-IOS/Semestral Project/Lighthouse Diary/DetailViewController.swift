//
//  DetailViewController.swift
//  Lighthouse Diary
//
//  Created by Šimon Minárik on 22.01.2021.
//

import UIKit

final class DetailViewController: UIViewController {
    private weak var lighthouseImageView: UIImageView!
    private weak var lighthouseNameLabel: UILabel!
    private weak var lighthouseDescriptionLabel: UILabel!
    
    private let descriptionText = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Etiam commodo accumsan tellus sed dapibus. Morbi sed sodales elit. Sed ut ultricies augue. Donec vel congue risus, a mollis nisl. Ut eu posuere est. Quisque ultricies justo massa, at iaculis arcu lacinia eu. Proin aliquet iaculis posuere. Quisque porttitor, enim vitae ultricies rhoncus, erat ligula faucibus augue, nec hendrerit augue tortor sit amet augue. Etiam viverra sem eget pulvinar feugiat. Proin vehicula condimentum tortor, sed posuere mauris tempor mattis. Interdum et malesuada fames ac ante ipsum primis in faucibus. Suspendisse in ante nibh.\nDuis sed ligula tincidunt, rutrum sem et, dapibus odio. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Duis sit amet vulputate turpis, et imperdiet sapien. Proin et elit non mauris porta ultrices. Nullam sagittis tempus vulputate. Sed nunc elit, aliquet quis dolor id, dignissim rutrum massa. Morbi semper neque eu lacus aliquet, sed tempus leo bibendum. Phasellus quam felis, volutpat ac lacinia vel, porttitor ultricies metus.\nPraesent varius lacus vitae sapien tincidunt, nec condimentum enim ornare. Quisque imperdiet nunc ac blandit egestas. Ut justo velit, auctor pharetra imperdiet et, bibendum vel odio. Nunc nec sapien enim. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Proin sed odio in lectus dignissim faucibus eu ac erat. Nulla eget lorem sagittis, pellentesque mauris nec, tempus urna. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Sed tincidunt dui sit amet leo fermentum vulputate. Quisque suscipit, ligula ut posuere tempor, lectus massa posuere orci, a porttitor nunc magna at lacus. Integer magna eros, varius non ipsum id, pharetra dapibus justo. Ut ante urna, porta in finibus nec, facilisis vitae elit. Integer ac lacus faucibus, pharetra enim vitae, fermentum est. Fusce facilisis orci non aliquam dignissim. Nam sagittis malesuada tortor quis pharetra. Donec nibh orci, cursus nec vehicula in, finibus et enim.\nSed et porttitor nibh. Integer et felis malesuada, facilisis erat ac, finibus nibh. Phasellus augue lacus, porttitor ut mauris vel, congue auctor dui. Maecenas in egestas sem. Nunc vestibulum sed elit eu commodo. Aliquam nibh mi, tincidunt non rutrum nec, volutpat eu est. Maecenas sed sapien mauris. Ut mattis justo sit amet justo sagittis, quis varius nibh commodo. Nullam iaculis finibus nisi sed sagittis. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin efficitur fermentum nunc ut tincidunt. Mauris at faucibus leo, sit amet cursus sapien. Cras varius arcu vel imperdiet ultrices. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Cras feugiat porta enim sed tempor."
    
    override func loadView() {
        super.loadView()
        
        let scrollView = UIScrollView()
        scrollView.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(scrollView)
        NSLayoutConstraint.activate([
            scrollView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            scrollView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            scrollView.topAnchor.constraint(equalTo: view.topAnchor),
            scrollView.bottomAnchor.constraint(equalTo: view.bottomAnchor),
            scrollView.contentLayoutGuide.widthAnchor.constraint(equalTo: scrollView.frameLayoutGuide.widthAnchor)
        ])
        
        let contentView = UIView()
        contentView.translatesAutoresizingMaskIntoConstraints = false
        scrollView.addSubview(contentView)
        NSLayoutConstraint.activate([
            contentView.leadingAnchor.constraint(equalTo: scrollView.contentLayoutGuide.leadingAnchor),
            contentView.trailingAnchor.constraint(equalTo: scrollView.contentLayoutGuide.trailingAnchor),
            contentView.topAnchor.constraint(equalTo: scrollView.contentLayoutGuide.topAnchor),
            contentView.bottomAnchor.constraint(equalTo: scrollView.contentLayoutGuide.bottomAnchor)
        ])
        
        let lighthouseImageView = UIImageView(image: UIImage(named: "612664395a40232133447d33247d38313233393434333331.jpeg"))
        lighthouseImageView.translatesAutoresizingMaskIntoConstraints = false
        contentView.addSubview(lighthouseImageView)
        NSLayoutConstraint.activate([
            lighthouseImageView.topAnchor.constraint(equalTo: contentView.topAnchor, constant: 8),
            lighthouseImageView.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 8),
            lighthouseImageView.widthAnchor.constraint(equalToConstant: 150),
            lighthouseImageView.heightAnchor.constraint(equalTo: lighthouseImageView.widthAnchor)
        ])
        self.lighthouseImageView = lighthouseImageView
        
        let lighthouseNameLabel = UILabel()
        lighthouseNameLabel.text = "Lighthouse Arkona"
        lighthouseNameLabel.translatesAutoresizingMaskIntoConstraints = false
        contentView.addSubview(lighthouseNameLabel)
        NSLayoutConstraint.activate([
            lighthouseNameLabel.topAnchor.constraint(equalTo: contentView.topAnchor, constant: 8),
            lighthouseNameLabel.trailingAnchor.constraint(equalTo: contentView.trailingAnchor, constant: 8),
            lighthouseNameLabel.leadingAnchor.constraint(lessThanOrEqualTo: lighthouseImageView.trailingAnchor)
        ])
        self.lighthouseNameLabel = lighthouseNameLabel
        
        let lighthouseDescriptionLabel = UILabel()
        lighthouseDescriptionLabel.text = self.descriptionText
        lighthouseDescriptionLabel.numberOfLines = 0
        lighthouseDescriptionLabel.translatesAutoresizingMaskIntoConstraints = false
        contentView.addSubview(lighthouseDescriptionLabel)
        NSLayoutConstraint.activate([
            lighthouseDescriptionLabel.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 8),
            lighthouseDescriptionLabel.trailingAnchor.constraint(equalTo: contentView.trailingAnchor, constant: 8),
            lighthouseDescriptionLabel.topAnchor.constraint(equalTo: lighthouseImageView.bottomAnchor, constant: 16),
            lighthouseDescriptionLabel.bottomAnchor.constraint(equalTo: contentView.bottomAnchor)
        ])
    }
}
