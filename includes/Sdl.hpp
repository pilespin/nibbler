/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sdl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:42:26 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/11 14:52:08 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Shared.hpp"
#include <project.hpp>

class Sdl {

public:
	Sdl();
	~Sdl();
	Sdl(Sdl const &src);
	Sdl &operator=(Sdl const &rhs);

	virtual int				getValue() const;
	virtual SDL_Window		*getWindow() const;
	virtual SDL_Renderer 	*getRenderer() const;
	virtual SDL_Surface		*getImage(std::string name);

	virtual void			setWindowSize(int x, int y);
	virtual void			setWindowName(std::string name);
	virtual void			setShared(Shared *shared);

	virtual void			createWindow();
	virtual void			createRenderer();
	virtual SDL_Surface		*loadImage(std::string path, std::string newname);
	virtual void			DrawImageInRenderer(SDL_Surface *img, int x, int y);
	virtual void			start();
	virtual void			empty();

	class Error : public std::exception {
	public:
		Error(std::string str) { 
			this->line += str; 
		}
		virtual const char *what() const throw() {
			return (this->line.c_str());
		}
	private:
		std::string line;
	};

private:
	std::map< std::string, SDL_Surface * > 	img;

	Shared 			*shared;
	int 			_val;
	std::string		windowName;
	int 			squareSize;
	int 			windowSizeX;
	int 			windowSizeY;
	SDL_Window 		*window;
	SDL_Renderer	*renderer;
};

std::ostream &operator<<(std::ostream &o, Sdl &c);
