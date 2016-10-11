# cdocker

_cdocker_ is a docker client written in C.

# Features

Right now, as this project is in an early stage of development, _cdocker_ is able to :

* Query the docker daemon in http, on this routes :
   - /containers/json
* Return native JSON response only

# Exemple of use

```c

#include <stdio.h>
#include <curl/curl.h>
#include "cdocker.h"

int main(int argc, char **argv)
{
    cdocker_init();

    CURL *curl = cdocker_connect();
    char *host = "127.0.0.1:2376";

    DOCKER_CLIENT *docker_client = cdocker_client_new(curl, host);

    DOCKER_CLIENT_RESPONSE *res = cdocker_images_list(docker_client);

    printf("%s", res->payload);

    cdocker_client_response_destroy(res);
    cdocker_client_destroy(docker_client);

    cdocker_close();

    return 0;
}
```


