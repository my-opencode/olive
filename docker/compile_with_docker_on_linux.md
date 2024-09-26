# Compiling on Linux with Docker

To support most Linux distributions out of the box, we chose to compile Olive and its dependencies as an **AppImage**. \
We provide [a CentOS 7 based Docker image](https://hub.docker.com/r/olivevideoeditor/ci-olive) to build Olive locally.

## Steps:

### 1. Clone Olive locally

- Create a local copy of the source [from GitHub](https://github.com/olive-editor/olive).
- Use the `--recursive` flag to pull all dependencies such as `./ext/core`.

```shell
git clone --recursive https://github.com/olive-editor/olive
```

### 2. [Optional] Manually pull our [ci-olive image from Docker Hub](https://hub.docker.com/r/olivevideoeditor/ci-olive)

```shell
# You will need root privileges. Use 'sudo' on Ubuntu/Debian.
docker pull olivevideoeditor/ci-olive:latest
```

### 3. Build Olive inside a container

- One liner
  `rm -rf build && mkdir build && cd build && cmake .. -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo && cmake --build . && cmake --install app --prefix appdir/usr && /usr/local/linuxdeployqt-x86_64.AppImage appdir/usr/share/applications/org.olivevideoeditor.Olive.desktop -appimage --appimage-extract-and-run`

#### a. Run the container

- Run [ci-olive](https://hub.docker.com/r/olivevideoeditor/ci-olive) as a container.
- Mount your local copy of the source into the container at `/opt/olive/`.
- Connect to the shell inside the container.

```shell
# You will need root privileges. Use 'sudo' on Ubuntu/Debian.
docker run --rm -it -v /path/to/your/local/copy/of/olive:/opt/olive olivevideoeditor/ci-olive:2022.4
```

#### b. Prepare the build directory

- Using the root (#) shell inside the container.

```shell
cd olive
mkdir build
cd build
# Default: Build with GCC (g++)
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo
# Alternative: Build with Clang (clang++)
# cmake .. -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_CXX_COMPILER=clang++
cmake --build .
```

#### c. Prepare for AppImage

- Using the root (#) shell inside the container.
- Collect the files that will be packaged as AppImage

```shell
cmake --install app --prefix appdir/usr
```

#### d. Build the AppImage

- Using the root (#) shell inside the container.
- Creates the AppImage with linuxdeployqt.

```shell
/usr/local/linuxdeployqt-x86_64.AppImage appdir/usr/share/applications/org.olivevideoeditor.Olive.desktop -appimage --appimage-extract-and-run
```

#### e. Exit the container

- Using the root (#) shell inside the container.
- Exits from the container.
- All build artifacts will remain in the `build` sub directory of `/path/to/your/local/copy/of/olive`.

```shell
exit
```

### 4. Done

Your AppImage `Olive-<VERSION>-x86_64.AppImage` is now ready in the `build` sub directory of `/path/to/your/local/copy/of/olive`.
