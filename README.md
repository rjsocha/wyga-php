# PoC/alpha stage `wyga` PHP modular system

Precompiled PHP extensions for Docker image crearation.

## Quick Start

Build image:
```
cat <<EOF | docker build -t wyga-php-test:7.4 -
FROM wyga/php-ext-mysqli:7.4
FROM wyga/php-ext-pdo_mysql:7.4
FROM wyga/php-ext-gd:7.4
FROM wyga/php-ext-mcrypt:7.4
FROM wyga/php-ext-intl:7.4
FROM wyga/merge:5 AS merge

FROM wyga/php-merge:7.4-fpm
EOF
```

With ONBUILD support
```
FROM wyga/php-ext-mysqli:7.4
FROM wyga/php-ext-pdo_mysql:7.4
FROM wyga/php-ext-gd:7.4
FROM wyga/php-ext-mcrypt:7.4
FROM wyga/php-ext-intl:7.4
FROM wyga/merge:5 AS merge

FROM wyga/php-merge:7.4-fpm
```

Other usage example:
```
FROM scratch AS merge
COPY --from=wyga/php-ext-intl:7.4 / /
COPY --from=wyga/php-ext-mysqli:7.4 / /
COPY --from=wyga/php-ext-v8js:7.4 / /
COPY --from=wyga/php-ext-gd:7.4 / /

FROM wyga/php:7.4-fpm
COPY --from=merge / /
RUN wyga-php-setup
```


Verbose example:
```
FROM wyga/php-ext-mysqli:7.4 AS mysqli
FROM wyga/php-ext-pdo_mysql:7.4 AS pdo_mysql
FROM wyga/php-ext-gd:7.4 AS gd
FROM wyga/php-ext-mcrypt:7.4 AS mcrypt
FROM wyga/php-ext-intl:7.4 AS intl

FROM scratch AS merge
COPY --from=mysqli / /
COPY --from=pdo_mysql / /
COPY --from=gd / /
COPY --from=mcrypt / /
COPY --from=intl / /

FROM wyga/php:7.4-fpm
COPY --from=merge / /
RUN wyga-php-setup
```
## Merge mode usage

First import your extensions:

```
FROM wyga/php-ext-intl:7.4
FROM wyga/php-ext-imap:7.4
FROM wyga/php-ext-mcrypt:7.4
FROM wyga/php-ext-memcached:7.4
FROM wyga/php-ext-pgsql:7.4
FROM wyga/php-ext-zip:7.4
```

Count number of FROM's. In this example we have 6.\
Merge previous imports with `wyga / merge`. Put  6  as a tag (number of previous imports) and put `merge` as stage name (**important!**).

```
FROM wyga/merge:6 AS merge
```

Lastly add `wyga/php-merge`

```
FROM wyga/php-merge:7.4
```

And build your image.

## Binary distribution

AMD64 only for the moment, based on buster (Debian 10 images).\
PHP 7.4 only for this moment.\
Works with upstream PHP images.

## Base image

 * `wyga/php`
 * `wyga/php-merge`

### Tags

 * `7.4.20-fpm` `7.4-fpm` `7-fpm` `7.4.20-cli` `7.4-cli` `7-cli` `7.4.20` `7.4` `7`

## Availible extenstions

### Images

 * `wyga/php-ext-bcmath`
 * `wyga/php-ext-bz2`
 * `wyga/php-ext-calendar`
 * `wyga/php-ext-dba`
 * `wyga/php-ext-exif`
 * `wyga/php-ext-gd`
 * `wyga/php-ext-gearman`
 * `wyga/php-ext-gettext`
 * `wyga/php-ext-gmagick`
 * `wyga/php-ext-gmp`
 * `wyga/php-ext-igbinary`
 * `wyga/php-ext-imagick`
 * `wyga/php-ext-imap`
 * `wyga/php-ext-intl`
 * `wyga/php-ext-ldap`
 * `wyga/php-ext-mailparse`
 * `wyga/php-ext-mcrypt`
 * `wyga/php-ext-memcache`
 * `wyga/php-ext-memcached`
 * `wyga/php-ext-mongodb`
 * `wyga/php-ext-mysqli`
 * `wyga/php-ext-odbc`
 * `wyga/php-ext-pcntl`
 * `wyga/php-ext-pdo_mysql`
 * `wyga/php-ext-pdo_odbc`
 * `wyga/php-ext-pdo_pgsql`
 * `wyga/php-ext-pgsql`
 * `wyga/php-ext-pspell`
 * `wyga/php-ext-redis`
 * `wyga/php-ext-shmop`
 * `wyga/php-ext-snmp`
 * `wyga/php-ext-soap`
 * `wyga/php-ext-sockets`
 * `wyga/php-ext-sysvmsg`
 * `wyga/php-ext-sysvsem`
 * `wyga/php-ext-sysvshm`
 * `wyga/php-ext-uuid`
 * `wyga/php-ext-v8js`
 * `wyga/php-ext-xdebug`
 * `wyga/php-ext-xmlrpc`
 * `wyga/php-ext-xsl`
 * `wyga/php-ext-yaml`
 * `wyga/php-ext-zip`

### Tags

 * `7.4.20` `7.4` `7`

## Build comparsion:

### Standard (cold cache / no local images) build:

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

Second run (with local php:7.4.20-fpm-buster image)

Build time: 2m 48s\
Image size: 467MB

### wyga build (without cache / no local images, wyga/php):

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

FROM wyga/php:${V}-fpm-buster
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

Second run (with local wyga images)

Build time: 0m 19s\
Image size: 247MB

### wyga modules + upstream php-fpm (without cache / no local images):

wyga modules are fully compatibile with upstrem images

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

FROM php:${V}-fpm-buster
COPY --from=build / /
RUN wyga-php-setup
```
try:
```
docker build --no-cache -t wyga-php-7.4-fpm:upstream \
 -f Dockerfile.upstream "https://github.com/rjsocha/wyga-php.git#master:examples"
```

Build time: 0m 58s\
Image size: 456MB

Second run (with local wyga images and php upstream image)

Build time: 0m 18s\
Image size: 456MB
