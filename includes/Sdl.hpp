/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sdl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 20:42:26 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/14 16:27:36 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Shared.hpp"
#include "IGraphic.hpp"
#include <project.hpp>

class Sdl : public IGraphic{

public:
	Sdl();
	~Sdl();
	Sdl(Sdl const &src);
	Sdl &operator=(Sdl const &rhs);

	int				getValue() const;
	SDL_Window		*getWindow() const;
	SDL_Renderer 	*getRenderer() const;
	SDL_Surface		*getImage(std::string name);

	void			setWindowSize(int y, int x); //
	void			setWindowName(std::string name);//----->le constructeur sert a quoi?-
	void			setShared(Shared *shared);//

	void			createWindow();
	void			createRenderer();
	SDL_Surface		*loadImage(std::string path, std::string newname);
	void			DrawImageInRenderer(SDL_Surface *img, int x, int y);
	void			init();
	void			getKey();
	void			quit();
	void			draw();
	void			empty();

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
	double			last_time;
};

std::ostream &operator<<(std::ostream &o, Sdl &c);
