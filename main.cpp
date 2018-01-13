/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 23:10:41 by sjones            #+#    #+#             */
/*   Updated: 2018/01/12 23:42:50 by sjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.hpp"
#include "player.hpp"
#include <unistd.h>
#define FRAME_RATE 60
#define CLOCKS_PER_FRAME (CLOCKS_PER_SEC / FRAME_RATE)

int	gameLoop(Game *game, Player *player) {
	int ch;
	static clock_t lastSec = 0;
	static int FPS = 0;
	static int frames = 0;
	clock_t now = clock();

	frames++;
	if (lastSec / CLOCKS_PER_SEC != now / CLOCKS_PER_SEC)
	{
		clear();
		lastSec = now;
		FPS = frames;
		frames = 0;
	}
	game->drawBorder();
	ch = getch();
	game->move(player, ch);
	game->score(player, FPS);
	refresh();
	game->checkEnd(player);
	if (ch == 27 || game->isEnd())
		return (0);
	while(clock() / CLOCKS_PER_FRAME == now / CLOCKS_PER_FRAME) {}
	return (1);
}

int main() {
	Game *game = new Game;
	Player *player = new Player;
	bool playing = true;

	game->loadScreen();
	while (playing) {
		playing = game->menu();
		clear();
		if (playing)
			while (gameLoop(game, player)) {} 
		game->resetGame(player);
	}
	game->loadScreen();
	delete(game);
	delete(player);
	return (0);
}