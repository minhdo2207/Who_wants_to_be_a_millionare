# Who Wants to Be a Millionaire

"Who Wants to Be a Millionaire" is an interactive quiz game developed in C and Qt, featuring single-player and Player vs. Player (PvP) modes. The game structure involves answering progressively difficult multiple-choice questions, with increasing prize levels. Additionally, the project supports rankings, tracking players' history, and employs a client-server architecture.

## Features

### Single Player Mode

- **Game Structure:**
  - Multiple-choice questions with increasing difficulty.
  - Prize levels increase with each correct answer.
  - Goal: Answer the one-million-unit question.

### PvP Mode

- **User Invitations:**
  - Players can invite others by entering their usernames.
  - If the invitee accepts, both users engage in a simultaneous game.
  - The winner is determined based on who has a higher score.

### Rankings

- **Ranking System:**
  - Players are ranked based on the number of winning/losing games.
  - Each winning game awards 1 rank point, while each losing game deducts 1 rank point.
  - Players rank up after accumulating every 10 rank points.
  - Ranking Tiers:
    - 0: Bronze Medal
    - 10: Silver
    - 20: Gold
    - 30: Platinum
    - 40+: Master

### Player's History

- **Game History:**
  - Keeps track of players' game history, including wins and losses.

### Client-Server Architecture

- **Multiplayer Support:**
  - Utilizes a client-server architecture to facilitate multiplayer interactions.
  - Supports simultaneous gameplay for multiple users.

## Requirements

- C programming knowledge
- Qt framework installed
- Git
## Usecase
![usecase](https://github.com/minhdo2207/Who_wants_to_be_a_millionare/blob/main/diagram/usecase_diagram.png)
## Class Diagram
![classdiagram](https://github.com/minhdo2207/Who_wants_to_be_a_millionare/blob/main/diagram/ClassDiagram.png)
## Finite state machine
![classdiagram](https://github.com/minhdo2207/Who_wants_to_be_a_millionare/blob/main/diagram/Finite_state_machine.drawio.png)
## Flow chart
![flowchart](https://github.com/minhdo2207/Who_wants_to_be_a_millionare/blob/main/diagram/Flow-Chart.drawio.png)


## Getting Started

1. **Clone the repository:**
   ```bash
   https://github.com/minhdo2207/Who_wants_to_be_a_millionare
   ```

## Contributing

Contributions are welcome! If you'd like to contribute to the project, please follow the outlined steps in the README.

## License

This project is licensed under HUST license.
Special thanks to Dr. Tran Nguyen Ngoc for tutoring us to have this project.

