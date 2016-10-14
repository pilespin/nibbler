/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 18:48:50 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/14 16:36:44 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECT_H
# define PROJECT_H

enum eCommand {Up, Down, Left, Right, Escape, None};

#include <iostream>
#include <SDL2/SDL.h>
#include <map>
#include <dlfcn.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <sys/time.h>
#include <iomanip>

#define SNAKE	1
#define OFF 	0

#endif