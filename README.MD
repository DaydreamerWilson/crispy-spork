### Project Topic: ###
# Turn-based tactic combat simulator #  
# Group No: 90 #
### Project Members: ###
  - DaydreamerWilson (Wilson) : Wong Wing Sing (3035788534)
  - CircleLight (Tang) : Tang Kai Chi (3035806520)
### Project Description: ###
  - A simple game where a player can engage in turn-based tactic combat with a computer opponent.
  - Player gain new characters by playing the game and winning battles.
  - New characters can be used in battle.
  - Characters will be lost if killed in action during combat.
  - Easy and accessible modding of the game.
### Gamerule: ###
  - Follow instructions.
  - Avoid invalid input to prevent unexpected behaviour.
  - You're free to modify any .txt files while complying to the format (in Instructions).
### Features Implementation: ###
  - Resizable renderer and window
    - Resizable dyanmic 2-dimensional char array for containing the screen to be printed.
    - A 2-dimensional char array and several functions within same class to allows convenient usage of the renderer.
    - A unique header for storing renderer and renderer-related functions
  - Fully and accessible customizable maps and characters.
    - Loading of over 80 unique characters file and map.
    - Easy to modify parameters with only text editors.
  - Turn-based tactic battle
    - Base on default or customly built map.
      - Map of any arbitary size uiltized by dynamic memory management and class.
    - Randomized enemy characters each combat.
    - AI opponent with unpredictable tactic (powered by random number generator).
    - Randomized and weighted damage base on character stats.
    - Gain new characters by winning battles!
      - Abandon old characters by sending them to death!
  - Inventory
    - To showcase and inspect your characters.
    - Allow inspecting of stats.
    - Saving of your precious characters.
      - Autosave is frequent and loading is automatic at the start of the game.
### Game Instructions: ###
  - Use make main in terminal to compile the game.
  - Use ./main to run the game.
  - Upon starting the game, enter S to select the smallest resolution.
  - Afterward, type OKAY to confirm the resolution.
  - In main menu, enter I to inspect inventory, or enter C to enter combat.
    - Inventory
      - Enter corresponding ID to view character information.
      - Enter . to leave character information screen.
      - Enter M to return to main menu.
    - Combat
      - Enter ./res/map/8_8_symmetric.txt or D to enter combat with the default map.
      - Enter 1 2 5 to select character with ID 1, 2 and 5.
      - List on the left is the user's character information.
      - List on the right is the enemy's character information.
      - The list is listed in the following format:
        Icon on map
        Health Point
        Attack Point
        Defense Point
      - The center is the Battlefield.
        The character currently selected is denoted by a >  < on the map
      - Enter A to enter attack mode.
        - . will appear on empty grids around the selected character, this denotes the range of the attack.
        - [  ] will appear around enemy characters that can be attacked by the selected character.
      - Enter 7 7 to attack the character at X, Y position 7, 7.
        - A message will be shown near the bottom of the screen to show the attacker, attackee and attack damage.
      - Enter . to continue onto the next character.
      - Enter M to enter movement mode.
      - Enter 2 3 to move NU to X, Y position 2, 3.
        - A message will be shown near the bottom of the screen to show the mover and the target coordinate.
      - Enter . to continue onto the next character.
      - Finish the round by choosing to attack or move of the last character.
        - If you choose to attack, the enemy might be out of range, and no valid target is available.
        - If no valid target is available, enter 0 0, the attack will be automatically cancelled.
        - If you choose to move, you cannot move into enemy or friendly units.
      - After all of your characters had performed a move, the enemy will begin their turns.
        - Enemy turn will appear faster.
        - You can only see the aftermath of the enemy action.
        - A message will appear near the bottom of the screen, indicating what action enemy took, the target, and damage done (if enemy chose to attack).
        - Enemy actioner is denoted by <  >, actionee (such as attackee during an enemy attack) is denoted by [  ], no actionee will appear if the enemy chose to move.
      - Enter . three times to skip all enemy action.
      - Finish the battle by eliminating all enemies by moving into range and attack them to deduct their health points.
      - After winning the battle, the game will notify you of a new character.
      - Enter . to view the new character's information.
      - Enter . to return to main menu afterward.
      - The game will be auto-saved at this point
  - After the battle, enter I to enter the inventory to view the new character.
### File Instructions: ###
  - You can find instructions to modify the game files here.
  - Characters:
    - Navigate to crispy-sporky-main/res/characters.
    - Adding new character
      - Create new txt file with with the format, character_name.txt without any space in the name.
      - Follow template in _character-template-instruction.txt, do not include words after //
      - Add new line at end in character_list.txt, the line should be as following:
        81 character_name
        - An ID followed by the text file name without the prefix .txt.
      - IDs in character_list.txt must be in consecutive and in numeric order.
      - Change the number in the first line in character_list.txt to the number of characters in total.
    - Editing existing character
      - Open the corresponding .txt file.
      - Edit with regards to the format stated in _character-template.txt.
      - Avoid changing the ID, as player data loads character according to ID, changing the ID might result in loading failure.
    - Replacing existing character
      - The replacing character's ID must be the same as the one you want to replace.
      - Delete the character's .txt file.
      - Replace with the new character's .txt file.
      - Replace the corresponding line of the old character in character_list.txt with same ID.
      - All player save that has the existing character will be affected!
    - Removing existing character
      - Remove the character's .txt file.
      - Remove the corresponding line in character_list.txt
      - Change ALL ID in consecutive after the removed character, as ID in character_list.txt must be in consecutive and in numeric order.
      - Change the number in the first line in character_list.txt to the number of characters in total.
  - Map:
    - Navigate to crispy-sporky-main/res/map.
    - Adding new map
      - Create new txt file with the format, map_name.txt without any space in the name.
      - Follow template in _map-template-instruction.txt, do not include words after //
    - Editing existing map
      - Open corresponding .txt file.
      - Edit with regards to the format stated in _map-template-instruction.txt.
    - Removing existing map
      - Do not remove default map
      - Otherwise, simply delete the corresponding .txt file
    - Map that are too large might not be able to fit in the terminal.
  - Player Data:
    - Navigate to crispy-sporky-main/res.
    - Open playerdata.txt.
    - The text file is in format:
      dummy_varible character_counts
      characterid characterid characterid characterid characterid characterid characterid...
    - Add or remove new character id in any order.
    - Change character_counts to match the new character's count.
    - Open the game and save in the main menu.
    - The text file will be automatically sorted after saving in the game.
