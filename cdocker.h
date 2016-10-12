/*
 * cdocker.h
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

#ifndef CDOCKER_H_INCLUDED

#define CDOCKER_H_INCLUDED
#include <curl/curl.h>

typedef struct cdocker_client
{
    CURL *curl;
    char *host;

} DOCKER_CLIENT;

DOCKER_CLIENT* cdocker_client_new(CURL *curl, char *host);

typedef struct cdocker_client_response
{
    char *payload;

} DOCKER_CLIENT_RESPONSE;

void cdocker_client_destroy(DOCKER_CLIENT *dc);

DOCKER_CLIENT_RESPONSE* cdocker_client_response_new();

void cdocker_client_response_set_payload(DOCKER_CLIENT_RESPONSE* ccr, char *payload);

void cdocker_client_response_destroy(DOCKER_CLIENT_RESPONSE *dcr);

void cdocker_init();

CURL* cdocker_connect();

void cdocker_close();

DOCKER_CLIENT_RESPONSE* cdocker_images_list(DOCKER_CLIENT *docker_client);

static
char *cdocker_build_endpoint(const DOCKER_CLIENT *cdocker_client, const char *resource);

static
size_t write_callback(char *ptr, size_t size, size_t nmemb, char **payload);

#endif
