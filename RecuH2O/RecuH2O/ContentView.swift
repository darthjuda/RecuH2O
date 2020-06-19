//
//  ContentView.swift
//  RecuH2O
//
//  Created by mehdi jung on 28/05/2020.
//  Copyright © 2020 mehdi jung. All rights reserved.
//

import SwiftUI

struct ContentView: View {
    @State private var selection = 0
 
    var body: some View {
        TabView(selection: $selection){
            Text("RecuH2O")
                .font(.title)
                .tabItem {
                    VStack {
                        Image(systemName: "gamecontroller")
                        Text("Control")
                    }
                }
                .tag(0)
            Text("Vue 2: réglages")
                .font(.title)
                .tabItem {
                    VStack {
                        Image(systemName: "slider.horizontal.3")
                        Text("Réglages")
                    }
                }
                .tag(1)
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
