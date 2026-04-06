FROM gcc:latest AS base

RUN apt-get update && \
    apt-get install -y cmake libgtest-dev build-essential && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
    
COPY . .

RUN rm -rf build && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make


CMD ["./build/testproj"]