# MVCProjectQT
Model View Controller (MVC) Pattern


Separation of Model from View components makes it possible to implement several user interfaces that reuse the common core business logic.
Duplication of low-level Model code is eliminated across multiple UI implementations.
Decoupling of Model and View code results in an improved ability to write unit tests for the core business logic code.
Modularity of components allows core logic developers and UI developers to work simultaneously without affecting the other.
Basically, it says that there are three distinct responsibilities for our application. 

Model

Manages the app data and state
Not concerned with UI or presentation
Often persists somewhere
Same model should be reusable, unchanged in different interfaces

View

Present the Model to the user in an appropriate interface
Allows user to manipulate data
Does not store any data except to cache state
Easily reusable & configurable to display different data

Controller

Intermediary between Model & View
Updates the view when the model changes
Updates the model when the user manipulates the view
Typically, where the app logic lives
