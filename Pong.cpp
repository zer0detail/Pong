#include "Bat.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <iostream>
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main() {
	// Create a video mode object
	VideoMode vm(SCREEN_WIDTH, SCREEN_HEIGHT);
	// Create and open a window for the game
	RenderWindow window(vm, "Pong", Style::Resize);
	int score = 0;
	int lives = 3;

	// Create a bat at the bottom center of the screen
	Bat bat(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 20);
	// Create a ball
	Ball ball(SCREEN_WIDTH / 2, 0);
	// We will add a ball in the next chapter
	// Create a Textr object called HUD
	Text hud;
	// A cool retro-style font
	Font font;
	font.loadFromFile("DS-DIGIT.TTF");
	// Set the font to our retro style
	hud.setFont(font);
	// Make it nice and big
	hud.setCharacterSize(75);
	// Choose a color
	hud.setFillColor(Color::White);
	hud.setPosition(20, 20);
	// Here is our clock for timing everything
	Clock clock;
	while (window.isOpen()) {
		/*
		****************************
		*  Handle player input
		****************************
		*/
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				// Quit the game when the window is closed
				window.close();
			}
		}
		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		// Handle the pressing and releasing of the arrow keys
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			bat.moveLeft();
		}
		else {
			bat.stopLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			bat.moveRight();
		}
		else {
			bat.stopRight();
		}

		/*
		****************************
		*  Update the bat, ball and HUD
		****************************
		*/
		// Update the time delta
		Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);
		// Update the HUD text
		std::stringstream ss;
		ss << "Score:" << score << " Lives:" << lives;
		hud.setString(ss.str());
		// Handle ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y) {
			// Reverse the ball direction
			ball.reboundBottom();
			// Remove a life
			lives--;
			// Check for zero lives
			if (lives < 1) {
				// reset the score
				score = 0;
				// reset the lives
				lives = 3;
			}
		}
		// Handle ball hitting the top
		if (ball.getPosition().top < 0) {
			ball.reboundBatOrTop();
			// Add a point to the players score
			score++;
		}
		// Handle the ball hitting the sides
		if (ball.getPosition().left <= 0 || ball.getPosition().left + ball.getPosition().width >= window.getSize().x) {
			ball.reboundSides();
		}
		// Has the ball hit the bat?
		std::cout << "Bat: " << bat.getPosition().top << " Ball: " << ball.getPosition().top << std::endl;
		if (bat.getPosition().intersects(ball.getPosition())) {
			std::cout << "test";
			ball.reboundBatOrTop();
		}
		/*
		****************************
		*  Draw the bat, ball and HUD
		****************************
		*/
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
	}

	return 0;
}