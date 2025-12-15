
# Fitness Recommendation System

 Object Oriented Programming Project

---

## Problem Statement

Design an application that provides personalized fitness recommendations based on user activity and health metrics.

---

## Objective

The main objective of the **Fitness Recommendation System** is to help users receive personalized workout and diet plans based on their height, weight, and activity level.

The system leverages Object-Oriented Programming principles including:

* Strategy Design Pattern
* Observer Design Pattern
* Singleton Design Pattern

These patterns enable dynamic recommendations and persistent user profiles across sessions.

---

## Project Functionalities / Features

### User Registration and Login

* New users can register with a username and password.
* Registered users can log in using their credentials.
* On successful login, health metrics and previous user data are loaded.

---

### Health Profile Setup

* Upon registration, users input:

  * Height
  * Weight
  * Activity level (Beginner / Intermediate / Advanced)
* Inputs are validated against predefined ranges to ensure correctness.

---

### BMI Calculation and Categorization

* BMI is calculated using height and weight.
* BMI categories:

  * Underweight
  * Normal
  * Overweight
  * Obese

---

### Fitness Recommendation

* Fitness routines are generated based on BMI and activity level.
* Implemented using the **Strategy Design Pattern**.
* Separate strategies for:

  * Beginner
  * Intermediate
  * Advanced

---

### Diet Recommendation

* Personalized diet suggestions are provided according to BMI:

  * Weight gain
  * Fat loss
  * Maintenance

---

### Profile Management

* Users can:

  * View health metrics
  * Update height, weight, and activity level
* BMI and recommendations update in real time when metrics change.

---

### Data Persistence

* User data is stored in `fitness.txt`.
* Serialization and deserialization are used to maintain persistence across sessions.

---

### Modular Design

* Implements:

  * Encapsulation
  * Inheritance
  * Polymorphism

---

## Employed Pillars of Object-Oriented Programming

### 1. Encapsulation

**Definition:**
Bundling data and the methods that operate on that data into a single unit, while restricting direct access.

**Application in the Project:**

* `User` class encapsulates:

  * **Data:** username, password, height, weight, BMI
  * **Methods:** `updateMetrics()`, `calculateBMI()`
* `UserHealthMetrics` ensures health data is updated and accessed only through defined interfaces.
* Private and protected access specifiers enforce controlled access.

---

### 2. Abstraction

**Definition:**
Hiding complex implementation details and exposing only essential functionality.

**Application in the Project:**

* Interfaces such as:

  * `FitnessRecommendationStrategy`
  * `FitnessRecommendationObserver`
* Users interact with high-level menu options like:

  * View Diet Plan
  * Update Profile
* `FitnessRecommendationStrategy` defines a common `recommend()` interface.
* Abstract base classes provide contracts without exposing internal logic.

---

### 3. Inheritance

**Definition:**
A mechanism where a child class inherits properties and behaviors from a parent class.

**Application in the Project:**

* `FitnessRecommendationStrategy` is inherited by:

  * `BeginnerFriendly`
  * `Intermediate`
  * `Advanced`

---

### 4. Polymorphism

**Definition:**
The ability to treat objects of different derived classes as instances of the same base class.

**Application in the Project:**

* Runtime polymorphism using virtual functions.
* `recommend()` is invoked via a base class pointer, executing derived behavior dynamically.

---

## Header Files Description

```cpp
#include <iostream>   // Standard input/output
#include <fstream>    // File handling (fitness.txt)
#include <string>     // String operations
#include <vector>     // Dynamic lists (users, observers)
#include <algorithm>  // Utility functions like remove()
```

---

## Data Type Description

### 1. UserHealthMetrics

* Stores height, weight, BMI, activity level
* Validates metrics
* Notifies observers on update

### 2. User

* Stores username and password
* Contains a `UserHealthMetrics` object

### 3. FitnessRecommendationEngine & DietRecommendationEngine

* Singleton observers
* Use Strategy pattern to generate recommendations

---

## Functions Description

1. `getUsername()`
   Returns the username of the current user.

2. `Authenticate()`
   Verifies username and password against stored data.

3. `loginSuccess()`
   Initializes or loads user data upon successful login.

4. `inputHealthMetrics()`
   Takes user input for height, weight, and activity level.

5. `viewMetrics()`
   Displays height, weight, BMI, and activity level.

6. `viewRecommendation()`
   Shows fitness and diet recommendations.

7. `updateHealthMetrics()`
   Updates height, weight, or activity level.

8. `logout()`
   Logs out the user and saves data.

9. `serialize(ofstream& out)`
   Saves user data to file.

10. `deserialize(ifstream& in)`
    Loads user data from file.

11. `attach()`
    Registers an observer.

12. `detach()`
    Removes an observer.

13. `getHeight()`
    Returns current height.

14. `getWeight()`
    Returns current weight.

15. `getActivityLevel()`
    Returns activity level.

16. `notify()`
    Notifies all observers of metric changes.

17. `validateAndSetActivityLevel()`
    Validates and sets activity level.

18. `validateAndSetHeight()`
    Validates and sets height.

19. `validateAndSetWeight()`
    Validates and sets weight.

20. `getBMI()`
    Returns BMI value with category.

21. `calculateBMI()`
    Calculates BMI using the formula
    `weight / (height * height)`

22. `updateBMI()`
    Updates stored BMI.

23. `getInstance()`
    Returns singleton instance with metrics reference.

24. `getInstance1()`
    Returns existing singleton instance.

25. `update()`
    Called when observed subject changes.

26. `recommend()`
    Generates fitness and diet recommendations.

27. `saveAllUsers()` / `loadAllUsers()`
    Handles persistent storage.

28. `isValidUsername()`
    Validates username format and length.

29. `isValidPassword()`
    Validates password constraints.

30. `isNumber()`
    Checks if string is a valid number.

---

## Steps of Solution

### 1. Program Launch

* Displays welcome banner
* Shows menu:

  ```
  1. Register
  2. Login
  3. Exit
  ```

---

### 2. User Registration

* Username validation:

  * ≤ 10 characters
  * Must include letters
  * Only letters, digits, max 2 spaces
* Password validation:

  * ≥ 4 characters
  * No spaces
* Inputs height, weight, activity level
* Data saved to `fitness.txt`

---

### 3. User Login

* Credentials verified
* Observers attached:

  * FitnessRecommendationEngine
  * DietRecommendationEngine

---

### 4. User Dashboard

#### Menu Options

1. View Metrics
2. View Recommendation
3. Update Metrics
4. Logout

#### View Metrics

* Displays height, weight, BMI, activity level

#### View Recommendation

* Strategy selected based on BMI and activity level

#### Update Metrics

* Updates trigger BMI recalculation
* Observers notified automatically

#### Logout

* Saves data
* Deletes singleton instances

---

### 5. File Handling

* Uses `fitness.txt`
* Serialization and deserialization ensure persistence

---

### 6. Exit

* Saves all data
* Terminates program

---

## Project Demonstration

1. Program starts
2. User registers
3. Inputs validated
4. Data saved
5. User logs in
6. Dashboard accessed
7. Metrics viewed
8. Recommendations generated
9. Metrics updated
10. Observers notified
11. Logout saves data
12. Restart reloads data

---

## Limitations of the Adopted Approach

### 1. BMI as the Sole Health Metric

**Limitation:**
The system relies only on BMI.

**Why it’s a problem:**

* BMI ignores muscle mass and fat distribution
* Athletes may be misclassified

---

### 2. No Real-time Data Integration

**Limitation:**
System operates without real-time data.

**Why it’s a problem:**

* No wearable device integration
* Recommendations are less dynamic

---

### 3. Limited User Interaction and UI

**Limitation:**
Text-based console interface only.

**Why it’s a problem:**

* No graphical interface
* Reduced user engagement

---

### 4. No Persistent User Sessions or History

**Limitation:**
No tracking of historical progress.

**Why it’s a problem:**

* Users cannot review past data
* No improvement tracking

---

### 5. No Feedback Mechanism

**Limitation:**
Users cannot rate recommendations.

**Why it’s a problem:**

* System cannot learn from user satisfaction
* No adaptive improvement

