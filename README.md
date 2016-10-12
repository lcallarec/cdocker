# cdocker

_cdocker_ is a docker client written in C.

# Features

Right now, as this project is in an early stage of development, _cdocker_ is able to :

* Allow callers to deal with raw JSON response payload or with modem structures
* Query the docker daemon in http, on theses routes :
   - /containers/json&all=1

# Create the shared library

```bash
git clone git@github.com:lcallarec/cdocker.git
cd cdocker
cmake .
#make .
#-- Configuring done
#-- Generating done
#-- Build files have been written to: /my/project/path/cdocker
cmake --build . --target cdocker -- -j 4
#Scanning dependencies of target cdocker
#[100%] [100%] Building C object CMakeFiles/cdocker.dir/cdocker.c.o
#Building C object CMakeFiles/cdocker.dir/cdocker_model.c.o
#Linking C shared library libcdocker.so
#[100%] Built target cdocker
```

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

    //From json to model structs
    DOCKER_MODEL_CONTAINERS *c = cdocker_model_containers_new_from_json(res);

    int i;
    for (i = 0; i < c->count; i++)
    {
        printf("id : %s\n", c->containers[i].id);

    }

    cdocker_client_response_destroy(res);
    cdocker_client_destroy(docker_client);

    cdocker_close();

    return 0;
}
```


