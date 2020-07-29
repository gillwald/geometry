# Requirements
```
Docker version 19.03
```
tacos

# Set up docker permissions
This allows you to not type sudo on the host when starting docker.
```
sudo groupadd docker
sudo usermod -aG docker $USER
newgrp docker
```


# Build the repository image
```
docker build -t gillwald-geometry .
```

# Build the container and login
```
docker run -it                                \
  --hostname="gillwald-geometry"              \
  --user=$(id -u $USER):$(id -g $USER)        \
  --env="DISPLAY"                             \
  --workdir="/home/$USER/geometry"            \
  --volume="$PWD:/home/$USER/geometry"        \
  --volume="/etc/group:/etc/group:ro"         \
  --volume="/etc/passwd:/etc/passwd:ro"       \
  --volume="/etc/shadow:/etc/shadow:ro"       \
  --volume="/etc/sudoers.d:/etc/sudoers.d:ro" \
  --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
  gillwald-geometry:latest                    \
  bash
```

# Build the code
```
user@gillwald-geometry:~/geometry$ cmake CMakeLists.txt
user@gillwald-geometry:~/geometry$ make
```

# Test the code
```
user@gillwald-geometry:~/geometry$ ./geometry_tests
```
