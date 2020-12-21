//
//  NetworkService.swift
//  FITstagram
//
//  Created by Lukáš Hromadník on 11/11/2020.
//

import UIKit

protocol NetworkServicing {
    func fetch(url: String, completion: @escaping (Result<Data, Error>) -> Void)
    func fetch(urlRequest: URLRequest, completion: @escaping (Result<Data, Error>) -> Void)
}

struct NetworkService: NetworkServicing {
    func fetch(url: String, completion: @escaping (Result<Data, Error>) -> Void) {
        let urlRequest = URLRequest(url: URL(string: url)!)
        fetch(urlRequest: urlRequest, completion: completion)
    }
    
    func fetch(urlRequest: URLRequest, completion: @escaping (Result<Data, Error>) -> Void) {
        URLSession.shared
            .dataTask(with: urlRequest, completionHandler: { data, response, error in
                if let error = error {
                    print("[ERROR]", error)
                    completion(.failure(error))
                    return
                }
                
                guard let data = data else { assertionFailure(); return }
                
                completion(.success(data))
            })
            .resume()
    }
}
