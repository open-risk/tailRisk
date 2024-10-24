# This file is part of the tailRisk distribution (https://github.com/open-risk/tailRisk).
# Copyright (c) 2022 - 2024 Open Risk (https://www.openriskmanagement.com)+
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

FROM ubuntu:22.04

LABEL description="tailRisk: A library for computing risk measures"
LABEL maintainer="info@openrisk.eu"
LABEL version="0.2"
LABEL author="Open Risk <www.openriskmanagement.com>"

EXPOSE 8080

ENV PYTHONUNBUFFERED 1
ENV PYTHONDONTWRITEBYTECODE 1
ENV DJANGO_SETTINGS_MODULE controller.settings
ENV DJANGO_ALLOWED_HOSTS localhost 127.0.0.1 [::1]

ENV CC=gcc-12
ENV CXX=gcc-12

# Prepare the environment (gcc, cmake, conan and other Python dependencies)
RUN apt update && apt upgrade -y && apt install python3-pip cmake build-essential -y
RUN apt install g++-12 -y
RUN apt install openssl libssl-dev -y
RUN apt install git -y
RUN apt install gpg wget -y
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 12
ENV CXX=/usr/bin/g++
ENV CC=/usr/bin/gcc

# Install and configure Conan
RUN pip3 install conan
RUN conan profile detect --force
ENV CONAN_SYSREQUIRES_SUDO 0
ENV CONAN_SYSREQUIRES_MODE enabled

# Copy required files, delete local pre-existing builds
RUN mkdir /tailRisk
COPY ./src/CMakeLists.txt /tailRisk/src/CMakeLists.txt
COPY ./src/conanfile.txt /tailRisk/src/conanfile.txt
COPY ./src/*.cpp /tailRisk/src/
COPY ./src/*.h /tailRisk/src/
COPY ./testing/ /tailRisk/testing

# Remove the build dir (just in case)
RUN rm -rf /tailRisk/src/cmake-build-debug
RUN mkdir /tailRisk/src/cmake-build-debug

# Install C++ dependencies
WORKDIR /tailRisk/src
RUN conan install . --output-folder=cmake-build-debug --build missing -s build_type=Debug

# Build tailRisk
WORKDIR /tailRisk/src/cmake-build-debug
RUN cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
#RUN cmake --build .


# If all went well you now have a running instance of tailRisk in a Docker container
