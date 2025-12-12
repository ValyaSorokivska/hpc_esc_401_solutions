FROM ubuntu:24.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    g++ make \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . /app

RUN make
CMD ["./main"]
