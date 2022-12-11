# The Necromancer game

In this game, you play as a Necromancer, and you have to beat enemies, resurrect them as your servants, and collect Essence.

## Controls

- `W A S D` turn to specified direction, tap again to move
- `E` apply Curse - AoE damage in player's sight direction
- `Q` apply Ultimate - massive AoE damage around player

- Turn the dead body (`Necromancy`) or Undead (`Morphism`) in your sight into:
  - `Z` Zombie
  - `X` Skeleton
  - `C` Vampire
  - `V` Ghoul

- `T` open player's *Talents* menu
- `P` open *Save* menu to save your progress
- `R` restart current level
- `~` quit

## Game mechanics

- Move into ally **=** exchange places with them
- Move into enemy **=** apply normal attack
- Collect *Essence* **=** acquire some Mana and 1 Talent point
- Player's skills usually cost Mana, so you have to manage it properly; it can be gained from *Essence* and by killing mobs (`Withering` passive talent)
- The Player and each mob have a *Fraction*; Mobs see ones from different fractions as enemies
- Each mob has *Attack range* (in which they can deal damage) and *Vision range* (in which they spot enemies and can move towards them)
- Some mobs can be *Summoners* - they spawn other mobs periodically
- You can upgrade your *Talents* (and should do so!) in the *Talents* menu; each upgrade costs 1 *Talent point*, which you can acquire from *Essence* and with leveling up
- When your *EXP* hits the threshold, your Player level increases, giving you 1 *Talent point*; your level affects your *Max HP*, *Mana*, and *ATK*
- To beat a level, you have to eliminate all enemies and then approach the exit ladder 

## Mobs

- **Mortal**
  - upon death, body doesn't disappear, instead it can be used for Necromancy
  - killing one gives the player EXP
 
- **Undead**
  - killing one gives the player some HP and Mana (Withering passive talent)
  - there are 4 types of them: **Zombie, Skeleton, Vampire, Ghoul**
  
- **Golem**
  - killing one causes an effect according to the *Golem elemental type*:
      - **Stone**: creates a wall
      - **Fire**: creates a block of lava
      - **Ether**: transforms into essence
      - **Explosive**: causes an explosion, dealing AoE damage to all mobs within range and destroying walls nearby

## Talents
 * `Withering` (passive talent) - regains some HP and Mana upon killing an opponent
 * `Curse` - deals medium AoE damage in player's sight direction
 * `Necromancy` - resurrects dead body of any Mortal into Undead of choice, making them your servant
 * `Morphism` - transforms any Undead (either ally or enemy) into another Undead type of choice; can be used to strengthen your servants and weaken your opponents
 * `Ultimate` - deals massive AoE damage around player
 
## Talent config

Parameters of player's Talents are defined in Talent config, a part of `config.ini` file in each World directory.

It's useful to see `config.ini` of your World to know your powers in this World.

## Level files, loading, layout

Each level has two files defining it (X counts from 0):
- `levelX.ini` - level config file, contains general parameters and definitions of mobs
- `levelX_map.txt` - level layout drawn with symbols:
     * `.` *floor*
     * `#` *wall*, can be broken by explosions
     * `$` *bedrock*, cannot be broken
     * `@` *essence*, gives player 1 *Talent point* and some mana
     * `~` *lava*, deals damage upon stepping
     * `+` *closed door*
     * `/` *open door*
     * `<` *entry ladder* from above, spawnpoint
     * `>` *exit ladder* down, finish point
     * any other symbol is interpreted as *floor*
     
## More detailed info
Please refer to documentation.


