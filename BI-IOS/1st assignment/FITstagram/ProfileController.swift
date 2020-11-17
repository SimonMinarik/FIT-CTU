//
//  ProfileController.swift
//  FITstagram
//
//  Created by Šimon Minárik on 27/10/2020.
//

import UIKit

class ProfileController: UIViewController {
    
    @IBOutlet weak var usernameLabel: UILabel!
    
    @IBAction func editUsernameButtonTapped(_ sender: UIButton) {
        let ac = UIAlertController(title: "Change username", message: "Changing username will sign you in as a different user.", preferredStyle: .alert)
        ac.addTextField()
        
        let cancelAction = UIAlertAction(title: "Cancel", style: .cancel)
        ac.addAction(cancelAction)
        
        let submitAction = UIAlertAction(title: "OK", style: .default) { [unowned ac] _ in
                let answer = ac.textFields![0]
            self.usernameLabel.text = answer.text!
            }

        ac.addAction(submitAction)
        ac.preferredAction = submitAction

        present(ac, animated: true)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }
}
