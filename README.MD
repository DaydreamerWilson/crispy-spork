### Project Topic: ###
# Role-Playing Game #  
### Project Members: ###
  - DaydreamerWilson (Wilson) : Wong Wing Sing (3035788534)
  - CircleLight (Tang) : Tang Kai Chi (3035806520)
### Project Description: ###
  - To create a simple role-playing game with elements of dialogues, cutscenes, turn-based battle and random encounters.
  - The objective of the game is to level up through battling enemies, finding hints and solving puzzles in the map, and eventually complete the storyline.
  - The player would start in a large-scale map, where he/she can move around in the large-scale map and approach towns/establishments, when he approaches a town/establishment, the player would enter a small-scale map, where he/she can then interact with the objects or characters to initiate the story.
  - The player is also prompted to face random generated or preset encounters, where the player would engage in turn-based combat with procedurally generated or preset enemies.
### Planned Implementation: ###
  - Text-based user interface.
  - A large-scale (World/Continent) and several small-scale (Cities/Towns) map.
  - A turn-based battle mechanism.
    - Turn-based tactic:
      - Player and Enemy take turns to move their piece of pieces on a map, where the pieces can attack each others with specific range and damage, the ultimate goal is to reach a target destination or to defeat the opposite.
    - Turn-based combat:
      - Player and Enemy take turns to decide their action, the action can include Attack, Defense, Using items, or Performing acts, the damage dealt will be procedurally calculated.
  - Saving/Loading mechanism, allowing the player to save or load their progress.
  - Player-Objects interaction, allowing player to engage in dialogues with non-player characters or action with objects in the small-scale map.
### Complying to code requirements ###
  - Random encountering of procedurally generated enemies in the large-scale map.
  - Using structs to store player, enemies, objects, non-player characters information.
  - Freeing up memories as player leaves or enter different regions, by unloading previous region.
  - Saving and loading game status. Inputting of player, enemies, objects, non-player characters initial data and information from external files, allowing fewer data to be stored in the executable file.
  - Employing the use of custom libraries, by classifying, categorizing functions, we can distribute codes to different files to allow a smoother cooperation of different individuals when working in the same project.
