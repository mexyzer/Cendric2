#pragma once

// this enum is used for animations and used by all game objects
enum class GameObjectState
{
	Idle, // used by nearly every game object
	Idle_up, // used by map main character
	Idle_down, // used by map main character
	Idle_left, // used by map main character
	Idle_right, // used by map main character
	Walking, // used by mobs and its weapons
	Walking_up, // used by map main character
	Walking_down, // used by map main character
	Walking_right, // used by map main character
	Walking_left, // used by map main character
	Jumping, // used by mobs and its weapons
	Fighting, // used by mobs and its weapons
	Dead, // used by mobs and its weapons
	Frozen, // used by water tile
	Locked, // used by chest tile
	Unlocked, // used by chest tile
	Open, // used by chest tile
	Burning, // used by torch tile
	Crumbling, // used by crumbly block tile
	Pressed // used by buttons
};