#!/bin/bash 
set -e
echo "Build php-ext-entrypoint.c"
_image=$(docker build -q -f Dockerfile.build .)
echo "Transfering binaries from image to host filesystem..."
docker run --rm -v $(pwd):/copy "${_image}" cp /output/wyga-php-ext-entrypoint /copy/
echo "Cleaning up..."
docker image rm "${_image}"
docker build -t wyga/wyga-php-ext-base-image:latest -f Dockerfile .
docker push wyga/wyga-php-ext-base-image:latest
