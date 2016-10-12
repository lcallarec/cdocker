/*
 * cdocker_model.c
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

#include "cdocker_model.h"
#include <string.h>

DOCKER_MODEL_CONTAINERS* cdocker_model_containers_new_from_json(DOCKER_CLIENT_RESPONSE *ccr)
{
    json_object *jobj = json_tokener_parse(ccr->payload);

    int containers_count = json_object_array_length(jobj);

    DOCKER_MODEL_CONTAINERS *containers = malloc(sizeof(DOCKER_MODEL_CONTAINERS));
    containers->count = 0;

    int i;
    json_object *json_container;
    json_object *json_value_id;
    for (i = 0; i < containers_count; i++)
    {

        json_container = json_object_array_get_idx(jobj, i);
        json_object_object_get_ex(json_container, "Id", &json_value_id);

        const char *id = json_object_get_string(json_value_id);

        DOCKER_MODEL_CONTAINER *container = cdocker_model_container_new();
        cdocker_model_container_set_id(container, id);

        containers->containers[i] = *container;
        containers->count = i + 1;
    }

    //Free the root
    json_object_put(jobj);

    return containers;

}

DOCKER_MODEL_CONTAINER* cdocker_model_container_new()
{
    DOCKER_MODEL_CONTAINER *container = malloc(sizeof(DOCKER_MODEL_CONTAINER));
    container->id = NULL;

    return container;
}

void cdocker_model_container_set_id(DOCKER_MODEL_CONTAINER *container, const char *id)
{
    container->id = malloc(sizeof(char) * strlen(id));
    strcpy(container->id, id);
}