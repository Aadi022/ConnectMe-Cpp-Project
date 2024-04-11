# C++ Implementation of a Social Media Network

## Project Overview

This project is a C++ implementation of a basic social media network. It encapsulates the core functionalities typically associated with social media platforms, such as user interactions, group management, and community engagement. The implementation is structured around three main classes: `User`, `Group`, and `Community`, each offering a unique set of functionalities.

## Features

### User Functionalities

- **Authentication**: Log in with correct user credentials.
- **Friend Management**: Send and accept friend requests, view sent and received friend requests, and recommend friends.
- **Communication**: Send messages, view sent messages and inbox.
- **Group Management**: Create and manage groups.

### Group Functionalities

- **Administration**: View group admin and members.
- **Communication**: Send messages in a common chat, view messages from the common chat.
- **Membership Management**: Add or remove members (admin functionality), and leave the group.

### Community Functionalities

- **Administration**: View community admin and members.
- **Communication**: Send messages in a common chat, view messages from the common chat.
- **Membership Management**: Remove members (admin functionality), and leave the community.
- **Community Recommendation**: Get recommended communities to join if not already a member.

## Class Descriptions

- `User`: Represents a user of the social media network with functionalities for friend and message management.
- `Group`: Represents a group within the network, allowing users to interact and manage group membership.
- `Community`: Similar to a group but with distinct rules for formation-Only Recommended by the Software. Users in a Graphical Cycle will get recommended a Community. A User can't form a Community by itself.

## Technical Details

- **Graphical Representation**: The network uses an undirected graph for representing connections between users, with non-weighted edges indicating friendships.
- **Graph Algorithms**: Implements Depth First Search (DFS) for friend recommendations and cycle detection for community recommendations.
- **Data Structures**: Utilizes stacks, unordered maps, lists, and vectors for efficient data management.
- **Object-Oriented Programming (OOP)**: The project is structured using OOP principles for better organization and modularity.

## Test Cases

The implementation includes test cases in the `main()` function, showcasing the creation and interaction of users within the network.

---

For developers and contributors, this project offers a comprehensive example of applying advanced C++ features and algorithms to simulate a social media network's core functionalities.
