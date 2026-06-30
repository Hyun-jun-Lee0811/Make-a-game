# CS230 Final Project

A custom C++ game engine and three playable game modes built from scratch for DigiPen Institute of Technology's **CS230** course, using the **Doodle** rendering/input library as the low-level graphics/input backend.

<div align="center">

[![C++](https://img.shields.io/badge/C%2B%2B-Engine-00599C?logo=cplusplus&logoColor=white)](#)
[![DigiPen](https://img.shields.io/badge/DigiPen-CS230-orange)](#)
[![Doodle](https://img.shields.io/badge/Framework-Doodle-blueviolet)](#)

</div>

> **Authors:** Hyunjun Lee, Geumbi Yeo
> **Course:** CS230 (DigiPen Institute of Technology)
> **Language:** C++
> **Rendering/Input library:** [doodle](https://github.com/DigiPen-Faculty/Doodle) (provided course framework)

---

## Table of Contents

- [Overview](#overview)
- [Engine Architecture](#engine-architecture)
- [Common Controls](#common-controls)
- [Game Modes](#game-modes)
  - [1. Side Scroller (Mode 1)](#1-side-scroller-mode-1)
  - [2. Space Shooter (Mode 2)](#2-space-shooter-mode-2)
  - [3. Watch Your Step (Mode 3)](#3-watch-your-step-mode-3)
- [Win / Game Over Conditions Summary](#win--game-over-conditions-summary)
- [Credits](#credits)

---

## Overview

This project is a small multi-game suite built on top of a custom, component-based 2D game engine written for the CS230 course. The engine handles windowing, input, sprite/animation playback, collision detection, camera control, particle systems, and game-state management. On top of this engine, three distinct game modes were implemented, each selectable from the main menu:

| Mode | In-Game Name | Genre | Implemented From | Authorship |
|---|---|---|---|---|
| Mode 1 | **Side Scroller** | 2D platformer | Course-provided functional spec | Individual assignment — this build uses **Hyunjun Lee's** implementation |
| Mode 2 | **Space Shooter** | Top-down asteroids-style shooter | Course-provided functional spec | Individual assignment — this build uses **Hyunjun Lee's** implementation |
| Mode 3 | **Watch Your Step** | Vertical platformer / "climber" | Original design, fully self-created | Built **together** by Hyunjun Lee & Geumbi Yeo |

>  Mode 1 (Side Scroller) and Mode 2 (Space Shooter) were originally **individual assignments** — each of us implemented our own separate version from the same English-language functional specification provided by the course instructor. This repository uses **Hyunjun Lee's** individually-built versions of Mode 1 and Mode 2 as the foundation. **Mode 3 (Watch Your Step)** had no provided spec and was conceived, designed, and implemented **together** by both of us as a team.

---

## Engine Architecture

The engine (`CS230` namespace) follows a component-based architecture:

- **`Engine`** — Singleton service locator providing access to all engine subsystems (Input, Window, Logger, GameStateManager, TextureManager, SpriteFonts). Runs the main fixed-timestep update loop (target 30 FPS).
- **`GameStateManager` / `GameState`** — Manages high-level screens (Splash, Main Menu, Mode 1, Mode 2, Mode 3, Win) via a load/update/unload state machine.
- **`GameObject` / `GameObjectManager`** — Base class for all in-game entities. Supports position/velocity/rotation/scale, a simple finite-state-machine (`State`) per object, and pairwise collision testing/resolution every frame.
- **`Component` / `ComponentManager`** — Generic component system attachable to either a `GameObject` or a `GameState` (e.g. `Sprite`, `Collision`, `Camera`, `Gravity`, `Score`, `Timer`, `Background`, `ParticleEmitter`).
- **`Sprite` / `Animation`** — Loads `.spt` (sprite info) and `.anm` (animation sequence) text-based asset files, and drives frame playback.
- **`Collision`** — `RectCollision` and `CircleCollision` components implementing AABB and circle-circle collision tests, with optional debug-draw outlines.
- **`Camera` / `Camera2`** — Side-scrolling and vertical-scrolling camera variants that follow a target object within a clamped extent.
- **`ParticleEmitter`** — Object-pooled particle system used for smoke, hit-impact, debris, and crush effects.
- **`Input` / `InputKey`** — Keyboard state wrapper (`IsKeyDown`, `IsKeyReleased`) built over Doodle's keyboard callbacks.
- **`SpriteFont` / `Texture` / `TextureManager`** — Bitmap font rendering and texture loading/caching.

---

## Common Controls

These controls apply across the Main Menu and all game modes unless noted otherwise per-mode below.

| Key | Action |
|---|---|
| **↑ / ↓ (Up/Down Arrow)** | Navigate menu options |
| **Enter** | Confirm menu selection |
| **Escape** | Return to Main Menu (in-game) |
| **R** | Reload / restart the current stage |
| **~ (Tilde)** | *(Debug builds only)* Toggle collision-box visualization |

### Main Menu Options

| Option | Destination |
|---|---|
| Side Scroller | Mode 1 |
| Space Shooter | Mode 2 |
| Watch Your Step | Mode 3 |
| Quit | Exits the application |

---

## Game Modes

### 1. Side Scroller (Mode 1)

> **Source:** Originally an individual assignment, implemented from the instructor-provided functional specification. This build uses **Hyunjun Lee's** version.

<div align="center">
<table>
<tr>
<td align="center" width="50%"><img src="https://github.com/user-attachments/assets/a4d38be8-d4fe-440b-bcef-3b05d910f027" width="100%"/><br/><sub><b>Gameplay Overview</b></sub></td>
<td align="center" width="50%"><img src="https://github.com/user-attachments/assets/35d45ddc-9d41-408d-a83b-63f70e172953" width="100%"/><br/><sub><b>Jump Action</b></sub></td>
</tr>
<tr>
<td align="center" width="50%"><img src="https://github.com/user-attachments/assets/ee70b4fd-5349-4025-88f4-02d1dd2726a8" width="100%"/><br/><sub><b>Enemy Encounter</b></sub></td>
<td align="center" width="50%"><img src="https://github.com/user-attachments/assets/12180d65-fd2e-45c3-ae1a-487aa3c68a6b" width="100%"/><br/><sub><b>Level Clear</b></sub></td>
</tr>
</table>
</div>

#### Description
A horizontally-scrolling 2D platformer. The player controls **Hero**, who must run, jump, and bounce across a level filled with hazards (bouncing **Balls**, patrolling **Bunny** enemies, and **TreeStump** obstacles) to reach the level's **Exit** before time runs out.

The camera follows Hero horizontally and is clamped to the bounds of the parallax-scrolling background (clouds, mountains, foreground layers scroll at different speeds for a depth effect).

#### Controls

| Key | Action |
|---|---|
| **← / →** | Move Hero left / right |
| **↑** | Jump |
| **Escape** | Return to Main Menu |
| **R** | Reload the stage |

#### Hero States
- **Idle** — Standing still
- **Running** — Moving left/right on the ground
- **Skidding** — Decelerating after reversing direction at speed
- **Jumping** — Rising after a jump input
- **Falling** — Descending, no ground contact

#### Hazards & Interactables

| Object | Behavior |
|---|---|
| **Ball** | Bounces continuously on the floor under gravity. Colliding with Hero from the side knocks him back and triggers a brief invincibility/blink ("hurt") period. |
| **Bunny** | Patrols between two fixed X-coordinates ("patrol nodes"). When it detects Hero in its patrol path, it charges/attacks at double speed. Landing on top of a Bunny from above defeats it (+100 score) and emits a smoke particle puff; colliding with it from the side knocks Hero back and triggers the hurt state. |
| **TreeStump** | Static obstacle/platform of varying size that Hero can stand on or collide with from the side. |
| **Floor** | Static ground collision segments that make up the level's walkable terrain. |
| **Exit** | Trigger zone at the end of the level. Reaching it as Hero sends the player back to the Main Menu (in this build); reaching it as the Mode 3 Player character instead leads to the Win screen. |

#### HUD
- **Score** (top-left) — increases when enemies are defeated
- **Lives** (top-center) — starts at 3
- **Timer** (top-right) — starts at 60 seconds, counting down

#### Clear / Loss Conditions

| Condition | Result |
|---|---|
| Hero touches the level **Exit** | Returns to the Main Menu |
| **Timer reaches 0** | Lose 1 life; stage reloads if lives remain |
| **Hero falls off the bottom of the level** (`y < -300`) | Counted as "dead"; lose 1 life; stage reloads if lives remain |
| **Lives reach 0** | Lives reset to 3; returns to the Main Menu |

---

### 2. Space Shooter (Mode 2)

> **Source:** Originally an individual assignment, implemented from the instructor-provided functional specification. This build uses **Hyunjun Lee's** version.

<div align="center">
<table>
<tr>
<td align="center" width="33.3%"><img src="https://github.com/user-attachments/assets/42136651-ed95-4f51-98c8-2ad944cc4620" width="100%"/><br/><sub><b>Flight & Thrust</b></sub></td>
<td align="center" width="33.3%"><img src="https://github.com/user-attachments/assets/b4031e77-2b7a-4759-8c8a-2cdc779164bf" width="100%"/><br/><sub><b>Combat</b></sub></td>
<td align="center" width="33.3%"><img src="https://github.com/user-attachments/assets/21993425-6604-4eb4-a191-3552adc460b9" width="100%"/><br/><sub><b>Meteor Field</b></sub></td>
</tr>
</table>
</div>

#### Description
A top-down, *Asteroids*-style shooter. The player pilots a rotation-and-thrust controlled **Ship** through a screen-wrapping arena, shooting down fragmenting **Meteors** and an AI-controlled **EnemyShip** that actively hunts the player.

#### Controls

| Key | Action |
|---|---|
| **A** | Rotate counter-clockwise |
| **D** | Rotate clockwise |
| **W** | Thrust forward (in facing direction) |
| **Space** | Fire twin lasers |
| **R** | Restart the stage (after Ship is destroyed) |
| **Escape** | *(Debug builds only)* Return to Main Menu |

#### Flight Model
- The Ship rotates freely and accelerates only along its current facing direction (inertial/drift movement with drag).
- Velocity is capped to a maximum speed.
- All objects (Ship, Meteors) **wrap around the screen edges** — flying off one side reappears on the opposite side.

#### Enemies & Hazards

| Object | Behavior |
|---|---|
| **Meteor** | Spawns at a random position, velocity, and scale. On being hit by a laser, it loses health and emits hit-spark and rock-debris particles. Larger meteors **split into two smaller meteors** flying outward at an angle when destroyed (if not already at minimum size); the smallest size is destroyed outright for score. |
| **EnemyShip** | Continuously rotates to face and thrust toward the player Ship, with twin flame-trail sprites. Colliding with the player Ship destroys it. Destroying it with a laser awards score and plays an explosion animation. |
| **Laser** | Fired from the Ship's twin gun hardpoints in the direction the Ship is currently facing. Automatically self-destructs when it leaves the screen bounds. Destroys Meteors and the EnemyShip on contact. |

#### HUD
- **Score** (bottom-left) — increases as Meteors and the EnemyShip are destroyed
- **"Game Over" / "Press R to restart"** banners appear centered on screen once the Ship is destroyed

#### Clear / Loss Conditions

| Condition | Result |
|---|---|
| Ship collides with a **Meteor** or the **EnemyShip** | Ship is destroyed; "Game Over" is displayed |
| Player presses **R** after Game Over | Stage restarts |

> Note: This mode is primarily score-attack/survival in nature — there is no explicit "win" trigger; the objective is to survive and maximize score for as long as possible.

---

### 3. Watch Your Step (Mode 3)

> **Source:** No instructor specification was provided — fully designed and implemented **together** by Hyunjun Lee & Geumbi Yeo as a team.

<div align="center">
<table>
<tr>
<td align="center" width="50%"><img src="https://github.com/user-attachments/assets/a1fd819b-bd03-47c1-b9a6-140eed0aa612" width="100%"/><br/><sub><b>Cloud-Hopping Jump</b></sub></td>
<td align="center" width="50%"><img src="https://github.com/user-attachments/assets/99b04def-7af9-424e-818f-a173db6ee10c" width="100%"/><br/><sub><b>Climbing the Sky</b></sub></td>
</tr>
</table>
</div>

#### Description
A vertically-scrolling platformer/"climber" in the spirit of *Doodle Jump* / *Icy Tower*. The player controls **Player**, who must climb upward by jumping across a long, hand-placed vertical sequence of floating **Clouds**, avoiding (or bouncing off) hazardous **LightningClouds** and patrolling **Birds**, to reach the **Exit** at the top of the level before the timer runs out — all without falling.

The camera (`Camera2`) tracks the player vertically and is clamped within the level's height bounds.

#### Controls

| Key | Action |
|---|---|
| **← / →** | Move Player left / right |
| **↑** | Jump |
| **Escape** | Return to Main Menu (when not dead) |
| **R** | Reload the stage (when not dead) |

#### Player States
- **Idle** — Standing still on a cloud
- **Running** — Moving left/right
- **Skidding** — Decelerating after reversing direction at speed
- **Jumping** — Rising after a jump input
- **Falling** — Descending, no ground contact

#### Hazards & Interactables

| Object | Behavior |
|---|---|
| **Cloud** | Comes in 4 visual size/types. Acts as a solid platform — landing on top from above while falling triggers a "crush" particle puff and lets the Player stand on it; colliding from below or the side blocks horizontal movement instead. |
| **LightningCloud** | A hazardous variant of cloud. Landing on top from above does **not** let the player stand — instead it **launches the Player upward** with extra force (a "boost" jump) and awards a small score bonus. Colliding from the side still blocks movement and applies a brief hurt/knockback, same as a Bird collision. |
| **Bird** | Patrols back and forth between two fixed Y-anchored patrol nodes and "attacks" (charges at double speed) when it detects the Player approaching along its patrol line. Landing on top of a Bird from above defeats it (awards score) and gives the Player a launch similar to a regular jump; colliding with it from the side knocks the Player back and triggers a hurt/blink period. |
| **Exit** | Trigger zone placed at the top of the climb. Reaching it as the **Player** character sends you to the **Win screen**. |

#### HUD
- **Score** (bottom-left) — increases from defeating Birds and bouncing off LightningClouds
- **Lives** (bottom-center) — starts at 5
- **Timer** (bottom-right) — starts at 120 seconds, counting down
- HUD elements are hidden once the Player is dead or all lives are lost

#### Clear / Loss Conditions

| Condition | Result |
|---|---|
| Player reaches the **Exit** at the top of the climb | Proceeds to the **Win screen** |
| **Timer reaches 0** | Lose 1 life; stage reloads if lives remain |
| **Player falls off the bottom of the level** (`y < -280`) | Counted as "dead"; lose 1 life; stage reloads if lives remain |
| **Lives reach 0** | "Game Over" banner is shown; pressing **Escape** returns to the Main Menu (lives reset to 5) |

---

## Win / Game Over Conditions Summary

| Screen | Triggered By |
|---|---|
| **Win Screen** | Reaching the Exit as the Mode 3 **Player** character (e.g., completing Watch Your Step) |
| **Main Menu (via Exit)** | Reaching the Exit as the Mode 1 **Hero** character |
| **Main Menu (via Game Over)** | Running out of lives in Mode 1 or Mode 3 |
| **Restart (R key)** | Available in all modes to reload/retry the current stage |

The **Win** screen itself offers its own sub-menu:

| Option | Destination |
|---|---|
| Main Menu | Returns to the Main Menu |
| Side Scroller | Mode 1 |
| Space Shooter | Mode 2 |
| Quit | Exits the application |

---

## Credits

- **Engine:** Hyunjun Lee, Geumbi Yeo
- **Mode 1 (Side Scroller) & Mode 2 (Space Shooter):** Originally separate individual assignments, each implemented from a course-provided functional specification. This repository's build uses **Hyunjun Lee's** individually-implemented versions of both modes.
- **Mode 3 (Watch Your Step):** Original concept and implementation, built **together** by Hyunjun Lee & Geumbi Yeo
- **Framework:** Built on the [Doodle](https://github.com/DigiPen-Faculty/Doodle) graphics/input library provided as part of DigiPen's CS230 coursework
- **Course:** CS230, DigiPen Institute of Technology
