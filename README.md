# PoC wyga PHP modular system (binary distribution)

## By example:

### Standard (without cache) build:

```
FROM php:7.4.20-fpm-buster
ADD https://github.com/mlocati/docker-php-extension-installer/releases/latest/download/install-php-extensions \
 /usr/local/bin/
RUN chmod +x /usr/local/bin/install-php-extensions && sync && \
  install-php-extensions \
        igbinary \
        yaml \
        imagick \
        exif \
        pdo_mysql \
        mysqli \
        gd \
        mcrypt \
        intl 
```

try:
```
docker build --no-cache -t wyga-php-7.4-fpm:build \
 -f Dockerfile.build "https://github.com/rjsocha/wyga-php.git#master:examples"
```

Build time: 3m 4s\
Image size: 467MB

### wyga build (without cache, wyga/php):

```
ARG V=7.4.20
FROM wyga/php-ext-igbinary:${V} AS igbinary
FROM wyga/php-ext-yaml:${V} AS yaml
FROM wyga/php-ext-imagick:${V} AS imagick
FROM wyga/php-ext-exif:${V} AS exif
FROM wyga/php-ext-pdo_mysql:${V} AS pdo_mysql
FROM wyga/php-ext-mysqli:${V} AS mysqli
FROM wyga/php-ext-gd:${V} AS gd
FROM wyga/php-ext-mcrypt:${V} AS mcrypt
FROM wyga/php-ext-intl:${V} AS intl

FROM scratch AS build
COPY --from=igbinary / /
COPY --from=yaml / /
COPY --from=imagick / /
COPY --from=exif / /
COPY --from=pdo_mysql / /
COPY --from=mysqli / /
COPY --from=gd / /
COPY --from=mcrypt / /
COPY --from=intl / /

FROM wyga/php:${V}-fpm
COPY --from=build / /
RUN wyga-php-setup
```

try:
```
docker build --no-cache -t wyga-php-7.4-fpm:wyga \
 -f Dockerfile.wyga "https://github.com/rjsocha/wyga-php.git#master:examples"
```

Build time: 0m 50s\
Image size: 247MB
