/*
 * cdocker_model.h
 *
 * Copyright 2016 Laurent Callarec <l.callarec@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifndef CDOCKER_MODEL_H_INCLUDED
#define CDOCKER_MODEL_H_INCLUDED

#include "cdocker.h"
#include <json/json.h>

typedef struct
{
    char *id;

} DOCKER_MODEL_CONTAINER;

typedef struct
{
    int count;
    DOCKER_MODEL_CONTAINER containers[];

} DOCKER_MODEL_CONTAINERS;

DOCKER_MODEL_CONTAINER* cdocker_model_container_new();

void cdocker_model_container_set_id(DOCKER_MODEL_CONTAINER *container, const char *id);

DOCKER_MODEL_CONTAINERS* cdocker_model_containers_new_from_json(DOCKER_CLIENT_RESPONSE *ccr);

#endif
