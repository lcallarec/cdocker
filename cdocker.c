/*
 * cdocker.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cdocker.h"

void cdocker_init()
{
    curl_global_init(CURL_GLOBAL_ALL);
}

CURL* cdocker_connect()
{
  return curl_easy_init();
}

void cdocker_close()
{
    curl_global_cleanup();
}

static size_t write_callback(char *ptr, size_t size, size_t nmemb, char **payload)
{
    size_t buffer_size = size * nmemb;
    size_t payload_size = strlen(*payload);

    *payload = realloc(*payload, buffer_size + payload_size + 1);
    memcpy(*payload + payload_size, ptr, buffer_size);

    return buffer_size;
}

DOCKER_CLIENT_RESPONSE* cdocker_images_list(DOCKER_CLIENT *cdocker_client)
{
    CURL *curl;
    curl = cdocker_client->curl;
    char *response_body;

    if(curl)
    {
        DOCKER_CLIENT_RESPONSE* response = cdocker_client_response_new();

        response_body = malloc(sizeof(char));
        response_body[0] = '\0';

        char **presponse_body = &response_body;

        char *resource = "/containers/json?all=1";

        CURLcode res;

        char *endpoint = cdocker_build_endpoint(cdocker_client, resource);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, presponse_body);
        curl_easy_setopt(curl, CURLOPT_URL, endpoint);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else
        {
            cdocker_client_response_set_payload(response, response_body);
        }

        free(*presponse_body);
        free(endpoint);

        curl_easy_cleanup(curl);

        return response;
    }

    return NULL;
}

DOCKER_CLIENT* cdocker_client_new(CURL *curl, char *host)
{
    DOCKER_CLIENT* docker_client = malloc(sizeof(DOCKER_CLIENT));
    docker_client->curl = curl;
    docker_client->host = malloc(sizeof(char) * strlen(host));
    strcpy(docker_client->host, host);

    return docker_client;
}

void cdocker_client_destroy(DOCKER_CLIENT *docker_client)
{
    free(docker_client->host);
    free(docker_client);
}

DOCKER_CLIENT_RESPONSE* cdocker_client_response_new()
{
    DOCKER_CLIENT_RESPONSE* ccr = malloc(sizeof(DOCKER_CLIENT_RESPONSE));
    ccr->payload = NULL;

    return ccr;
}

void cdocker_client_response_destroy(DOCKER_CLIENT_RESPONSE *dcr)
{
    free(dcr->payload);
    free(dcr);
}

void cdocker_client_response_set_payload(DOCKER_CLIENT_RESPONSE* ccr, char *payload)
{
    ccr->payload = malloc(sizeof(char) * strlen(payload));
    strcpy(ccr->payload, payload);
}

static
char* cdocker_build_endpoint(const DOCKER_CLIENT *cdocker_client, const char *resource)
{
    size_t len1 = strlen(cdocker_client->host);
    size_t len2 = strlen(resource);

    char *endpoint = malloc(len1 + len2);
    memcpy(endpoint, cdocker_client->host, len1);
    memcpy(endpoint + len1, resource, len2);

    return endpoint;
}