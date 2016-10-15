/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 14:36:10 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/15 21:17:34 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <project.hpp>
#include "Shared.hpp"
#include "Core.hpp"

static double  ft_utime()
{
	int             sec;
	double          micro;
	struct timeval  tv;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec;
	micro = tv.tv_usec;
	micro /= 1000000;
	micro += sec;
	return (micro);
}

Core::Core() 						{	this->_val = 0;	}

Core::Core(Shared	*shared) {
	this->shared = shared;
	this->shared->command = eCommand::Right;
	this->shared->lastCommand = eCommand::Right;
	this->headY = 5;
	this->headX = 5;
	this->shared->snake.push_front(Object(this->headX - 4, this->headY, SNAKE));
	this->shared->snake.push_front(Object(this->headX - 3, this->headY, SNAKE));
	this->shared->snake.push_front(Object(this->headX - 2, this->headY, SNAKE));
	this->shared->snake.push_front(Object(this->headX - 1, this->headY, SNAKE));
	this->shared->snake.push_front(Object(this->headX, this->headY, SNAKE));

	this->shared->obj.push_front(Object(10, 10, APPLE));
	this->setOnMap(10, 10, APPLE);

	std::list<Object>::const_iterator it;
	for (it = this->shared->snake.begin(); it != this->shared->snake.end(); ++it) {
		this->setOnMap(it->getY(), it->getX(), SNAKE);
	}

	this->last_time = ft_utime();
	this->secRefresh = .1;
}

Core::~Core() {
}

Core::Core(Core const &src)	{	
	*this = src;	
}

Core	&Core::operator=(Core const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Core &c) {
	o << "Core: " << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		Core::getValue() const	{	return (this->_val);	}
///////////////////////////////////////////////////////////////////////////////

eCommand	Core::getOpositeCommand(eCommand command) {

	if (command == eCommand::Up)
		return (eCommand::Down);
	else if (command == eCommand::Down)
		return (eCommand::Up);
	else if (command == eCommand::Left)
		return (eCommand::Right);
	else if (command == eCommand::Right)
		return (eCommand::Left);
	else
		return (eCommand::None);

}
void	Core::start() {

	////////////////////////////////debug//////
	std::cout << "----------------------" << std::endl;
	int j = -1;
	while (++j < this->shared->mapSizeY)
	{
		int i = -1;
		while (++i < this->shared->mapSizeX)
			std::cout << this->shared->map[j][i] << " ";
		std::cout << std::endl;
	}
	std::cout << "----------------------" << std::endl;
    ////////////////////////////////debug//////

	this->shared->mutex.lock();
	double current = ft_utime();

	if (current > this->last_time + this->secRefresh || 
		(this->shared->command != this->shared->lastCommand && 
			this->shared->lastCommand != this->getOpositeCommand(this->shared->command)))
	{

		this->last_time = ft_utime();
		this->setOnMap(this->shared->snake.back().getY(), this->shared->snake.back().getX(), OFF);
		this->shared->snake.pop_back();

		if (this->shared->lastCommand == this->getOpositeCommand(this->shared->command))
			this->shared->command = this->shared->lastCommand;

		if (this->shared->command == eCommand::Up)
		{
			this->headY--;
			this->setOnMap(this->headY, this->headX, SNAKE);
			this->shared->snake.push_front(Object(this->headX, this->headY, SNAKE));
		}
		else if (this->shared->command == eCommand::Down)
		{
			this->headY++;
			this->setOnMap(this->headY, this->headX, SNAKE);
			this->shared->snake.push_front(Object(this->headX, this->headY, SNAKE));
		}
		else if (this->shared->command == eCommand::Left)
		{
			this->headX--;
			this->setOnMap(this->headY, this->headX, SNAKE);
			this->shared->snake.push_front(Object(this->headX, this->headY, SNAKE));
		}
		else if (this->shared->command == eCommand::Right)
		{
			this->headX++;
			this->setOnMap(this->headY, this->headX, SNAKE);
			this->shared->snake.push_front(Object(this->headX, this->headY, SNAKE));
		}
		else if (this->shared->command == eCommand::Escape)
		{
			exit(0);
		}

		////////////////////////////EAT////////////////////////
		if (this->shared->map[this->headY][this->headX] == APPLE)
		{
			// std::cout << "Eat apple" << std::endl;
			// this->shared->obj.push_front(Object(1, 1, APPLE));
			// this->setOnMap(1, 1, APPLE);
			// this->shared->snake.push_front(Object(this->headX + 5, this->headY + 5, SNAKE));
			// this->shared->obj.pop_back(); 
			// this->shared->map[this->headY][this->headX] = OFF;

		}

		////////////////////////////EAT////////////////////////

		this->shared->lastCommand = this->shared->command;

		// std::list<Object>::const_iterator it;
		// for (it = this->shared->snake.begin(); it != this->shared->snake.end(); ++it) {
		// 	std::cout << "X: " << it->getX() << "	Y: " << it->getY() << std::endl; 

		// }
		// std::cout << "----------------------" << std::endl;

	}

	this->shared->mutex.unlock();
}

void	Core::setOnMap(int y, int x, int value) {

	if (x >= 0 && x < this->shared->mapSizeX && 
		y >= 0 && y < this->shared->mapSizeY)
	{
		if (this->shared->map[y][x] == SNAKE && value == SNAKE)
			throw Error("You are not eatable");
		this->shared->map[y][x] = value;
	}
	else
		throw Error("Error: You are so far");
}
