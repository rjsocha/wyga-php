# PoC/alpha stage wyga PHP modular system (binary distribution)

## Base image
 * `wyga/php`
   * `7.4.20-fpm` `7.4-fpm` `7-fpm` `7.4.20-cli` `7.4-cli` `7-cli` `7.4.20` `7.4` `7`

## Availible extenstions
 * `wyga/php-ext-bcmath`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-bz2`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-calendar`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-dba`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-exif`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-gd`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-gearman`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-gettext`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-gmagick`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-gmp`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-igbinary`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-imagick`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-imap`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-intl`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-ldap`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-mailparse`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-mcrypt`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-memcache`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-memcached`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-mongodb`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-mysqli`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-odbc`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-pcntl`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-pdo_mysql`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-pdo_odbc`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-pdo_pgsql`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-pgsql`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-pspell`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-redis`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-shmop`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-snmp`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-soap`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-sockets`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-sysvmsg`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-sysvsem`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-sysvshm`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-uuid`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-xdebug`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-xmlrpc`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-xsl`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-yaml`
   * `7.4.20` `7.4` `7`
 * `wyga/php-ext-zip`
   * `7.4.20` `7.4` `7`

## By example:

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
