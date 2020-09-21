//
//  ContentView.swift
//  RecuH2O
//
//  Created by mehdi jung on 28/05/2020.
//  Copyright © 2020 mehdi jung. All rights reserved.
//

import SwiftUI

public var arduinoIP: String = "192.168.18.91"

struct ContentView: View {
    @State private var selection = 0
    @State var results = [Data]()
    @State var lvl: Double = 2
    @State var isOpen: Bool = true
    
 
    var body: some View {
        TabView(selection: $selection){
            /// Control view
            List(results, id: \.uuid) { item in
                VStack {
                    Text("RecuH2O")
                    Spacer()
                    HStack {
                        Text("Niveau: \(item.lvl)")
                        Slider(value: self.$lvl, in: 0...10, step: 1)
                    }
                    Spacer()
                    HStack {
                        Toggle("", isOn: self.$isOpen)
                        Text("Control clapet: \(String(item.isOpen))")
                    }
                    Spacer()
                }
            }
            .onAppear(perform: loadData)
            .tabItem {
                    VStack {
                        Image(systemName: "gamecontroller")
                        Text("Control")
                    }
                }
                .tag(0)
    
            /// Setting View
            SettingView()
                .tabItem {
                    VStack {
                        Image(systemName: "slider.horizontal.3")
                        Text("Réglages")
                    }
                }
                .tag(1)
        }
    }
    
    func loadData() {
        
        //    Creating the URL we want to read.
        guard var url = URL(string: "http://\(arduinoIP)") else {
            print("Invalid URL")
            return
        }
        //    Wrapping that in a URLRequest, which allows us to configure how the URL should be accessed.
        let request = URLRequest(url: url)
        //    Create and start a networking task from that URL request.
        URLSession.shared.dataTask(with: request) { data, response, error in
            //    Handle the result of that networking task.
            if let data = data {
                if let decodedResponse = try? JSONDecoder().decode(Response.self, from: data) {
                    // we have good data – go back to the main thread
                    DispatchQueue.main.async {
                        // update our UI
                        self.results = decodedResponse.results
                        
                    }
                    return
                }
            }
            
            // if we're still here it means there was a problem
            print("Fetch failed: \(error?.localizedDescription ?? "Unknown error")")
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}


struct SettingView: View {
    var body: some View {
        Color.blue
    }
}


struct Response: Codable {
    var results: [Data]
}

struct Data: Codable {
    var uuid: Int
    var name: String
    var lvl: Int
    var isOpen: Bool
}

extension Int {
    var double: Double {
        get { Double(self) }
        set { self = Int(newValue)}
    }
}



        

